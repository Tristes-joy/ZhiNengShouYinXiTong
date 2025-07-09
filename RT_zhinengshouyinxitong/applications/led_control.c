/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-08     32927       使用 rt_device_control API 的 PWM LED 控制器
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
// 包含旧版PWM驱动框架的头文件
#include <drivers/rt_drv_pwm.h>
#include "led_control.h" // 假设此文件存在且命名正确
#include <stm32f4xx_hal.h>

#define DBG_TAG "led_ctrl"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* --- 硬件和设备定义 --- */
// 按键
#define KEY_ON_OFF_PIN     GET_PIN(E, 6)
#define KEY_BRIGHT_UP_PIN  GET_PIN(B, 1)
#define KEY_BRIGHT_DN_PIN  GET_PIN(E, 5)

// LED (由PWM控制)
#define LED_PWM_DEVICE_NAME  "pwm3"
#define LED_PWM_CHANNEL      1
#define PWM_PERIOD           1000000 // 周期, 单位纳秒

/* --- 模块内部变量 --- */
static rt_device_t pwm_dev;          // PWM设备句柄 (通用的 rt_device_t)
static rt_mq_t key_mq;               // 用于按键事件的消息队列
static rt_uint32_t brightness_pulse; // 当前亮度脉宽
static rt_bool_t led_is_on;          // LED的逻辑状态

#define BRIGHTNESS_STEP (PWM_PERIOD / 4)

static void key_irq_callback(void *args)
{
    rt_base_t pin = (rt_base_t)args;
    rt_mq_send(key_mq, &pin, sizeof(pin));
}

/**
 * @brief  更新物理PWM硬件输出 (使用旧版API)
 */
static void update_led_pwm(void)
{
    struct rt_pwm_configuration cfg = {
            .channel = LED_PWM_CHANNEL,
            .period = PWM_PERIOD,
            .pulse = led_is_on ? brightness_pulse : 0
        };

        // 1. 总是先设置占空比
        rt_device_control(pwm_dev, PWM_CMD_SET, &cfg);

        // 2. 如果灯是开的，就确保它是使能状态
        if (led_is_on && cfg.pulse > 0) // 增加pulse > 0的判断，避免0亮度还开着
        {
            rt_device_control(pwm_dev, PWM_CMD_ENABLE, &cfg);
        }
        else // 如果灯是关的，或者亮度为0，就确保它是关闭状态
        {
            rt_device_control(pwm_dev, PWM_CMD_DISABLE, &cfg);
        }

        LOG_D("LED State: %s, Pulse Width: %d", led_is_on ? "ON" : "OFF", cfg.pulse);
}

/**
 * @brief  LED控制线程的入口函数 (最终版本)
 */
static void led_control_thread_entry(void *parameter)
{
    rt_base_t key_pin_received;

    // 初始化LED状态
    led_is_on = RT_FALSE;
    brightness_pulse = PWM_PERIOD / 2; // 默认亮度，在开灯时生效

    // 查找PWM设备
    pwm_dev = rt_device_find(LED_PWM_DEVICE_NAME);
    if (pwm_dev == RT_NULL)
    {
        LOG_E("Failed to find PWM device: %s. Thread exiting.", LED_PWM_DEVICE_NAME);
        return;
    }
    LOG_I("LED control thread started.");

    // 确保启动时灯是熄灭的
    update_led_pwm();

    while (1)
    {
        if (rt_mq_recv(key_mq, &key_pin_received, sizeof(key_pin_received), RT_WAITING_FOREVER) == RT_EOK)
        {
            // 简单的软件消抖延时
            rt_thread_mdelay(20);
            if (rt_pin_read(key_pin_received) != PIN_LOW)
            {
                // 这是个抖动，忽略它
                continue;
            }

            switch (key_pin_received)
            {
                case KEY_ON_OFF_PIN:
                    led_is_on = !led_is_on;
                    // 如果是“开灯”动作，并且当前目标亮度为0，
                    // 就把亮度恢复到一个默认值，避免开灯了但还是不亮。
                    if (led_is_on && brightness_pulse == 0)
                    {
                        // 恢复到100%的默认亮度
                        brightness_pulse = PWM_PERIOD / 1;
                        LOG_I("Brightness restored to default 50%% on power-on.");
                    }
                    LOG_I("Toggle key pressed. LED state is now: %s", led_is_on ? "ON" : "OFF");
                    break;

                case KEY_BRIGHT_UP_PIN:
                    // --- 核心逻辑修改 ---
                    // 如果灯是关的，我们先计算出它的当前亮度其实是0
                    if (!led_is_on) {
                        brightness_pulse = 0;
                        led_is_on = RT_TRUE; // 按下亮度键意味着要开灯
                    }

                    // 在当前亮度基础上增加
                    if (brightness_pulse <= (PWM_PERIOD - BRIGHTNESS_STEP))
                    {
                        brightness_pulse += BRIGHTNESS_STEP;
                    }
                    else
                    {
                        brightness_pulse = PWM_PERIOD;
                    }
                    LOG_I("Brightness UP. New Level: %d%%", (brightness_pulse * 100) / PWM_PERIOD);
                    break;

                case KEY_BRIGHT_DN_PIN:
                    // --- 核心逻辑修改 ---
                    // 如果灯是关的，它的当前亮度就是0
                    if (!led_is_on) {
                        brightness_pulse = 0;
                        // 按下亮度-时，如果灯是关的，可以保持关闭状态，因为从0再减没有意义。
                        // 或者，也可以让它亮起来，然后亮度为0。为了体验统一，我们也把它"打开"。
                        led_is_on = RT_TRUE;
                    }

                    // 在当前亮度基础上减小
                    if (brightness_pulse >= BRIGHTNESS_STEP)
                    {
                        brightness_pulse -= BRIGHTNESS_STEP;
                    }
                    else
                    {
                        brightness_pulse = 0;
                    }
                    LOG_I("Brightness DOWN. New Level: %d%%", (brightness_pulse * 100) / PWM_PERIOD);
                    break;

                default:
                    break;
            }
            // 每次按键后都调用更新函数，来应用最新的状态
            update_led_pwm();
        }
    }
}
/**
 * @brief  初始化并启动LED控制线程
 * @return 0 表示成功, -1 表示失败
 */
int led_control_init(void)
{
    // 强制开启按键引脚所在GPIO端口的时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 为按键事件创建一个消息队列
    key_mq = rt_mq_create("key_mq", sizeof(rt_base_t), 8, RT_IPC_FLAG_FIFO);
    if (key_mq == RT_NULL) {
        LOG_E("Failed to create message queue.");
        return -1;
    }

    // 配置按键引脚为上拉输入模式
    rt_pin_mode(KEY_ON_OFF_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_BRIGHT_UP_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_BRIGHT_DN_PIN, PIN_MODE_INPUT_PULLUP);

    // 绑定中断服务函数到下降沿
    rt_pin_attach_irq(KEY_ON_OFF_PIN, PIN_IRQ_MODE_FALLING, key_irq_callback, (void *)KEY_ON_OFF_PIN);
    rt_pin_attach_irq(KEY_BRIGHT_UP_PIN, PIN_IRQ_MODE_FALLING, key_irq_callback, (void *)KEY_BRIGHT_UP_PIN);
    rt_pin_attach_irq(KEY_BRIGHT_DN_PIN, PIN_IRQ_MODE_FALLING, key_irq_callback, (void *)KEY_BRIGHT_DN_PIN);

    // 使能全部三个引脚的中断
    rt_pin_irq_enable(KEY_ON_OFF_PIN, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(KEY_BRIGHT_UP_PIN, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(KEY_BRIGHT_DN_PIN, PIN_IRQ_ENABLE);

    // 创建并启动控制线程
    rt_thread_t tid = rt_thread_create("led_ctrl",
                                       led_control_thread_entry, RT_NULL,
                                       1024,
                                       25,
                                       10);
    if (tid != RT_NULL) {
        rt_thread_startup(tid);
        LOG_I("LED control task initialized successfully.");
    } else {
        LOG_E("Failed to create LED control thread.");
        rt_mq_delete(key_mq); // 清理资源
        return -1;
    }
    return 0;
}
// 导出到MSH命令行，方便测试
MSH_CMD_EXPORT(led_control_init, 初始化LED灯控制线程);
