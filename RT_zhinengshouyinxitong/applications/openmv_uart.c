/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-06     32927       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "openmv_uart.h"

#define DBG_TAG "openmv_uart"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

//(PC10/PC11), OpenMV 连接到 uart3
#define UART_DEVICE_NAME "uart3"

// --- 模块内部变量 ---
static rt_device_t serial_dev;           // 串口设备句柄
static struct rt_semaphore rx_sem;       // 用于通知数据包接收完成的信号量
#define PACKET_BUFFER_SIZE 100
static char rx_packet_buffer[PACKET_BUFFER_SIZE]; // 接收数据包的缓冲区
static rt_uint8_t rx_state = 0;          // 解析数据包的状态机
static rt_uint8_t packet_ptr = 0;        // 指向缓冲区的位置

/**
 * @brief  UART 数据接收回调函数
 * @param  dev      触发中断的设备
 * @param  size     收到的数据大小 (在INT_RX模式下通常为1)
 * @return rt_err_t
 * @note   当串口收到数据时，RT-Thread的底层驱动会调用这个函数
 */
static rt_err_t uart_rx_indicate(rt_device_t dev, rt_size_t size)
{
    rt_uint8_t rx_data;

    // 从串口设备中读取一个字节
    if (rt_device_read(dev, -1, &rx_data, 1) != 1) {
        return RT_ERROR;
    }

    // 解析数据包的状态机，协议: @<data>cd
    switch (rx_state)
    {
        case 0: // 空闲状态，等待包头 '@'
            if (rx_data == '@') {
                rx_state = 1;
                packet_ptr = 0; // 重置缓冲区指针
            }
            break;

        case 1: // 接收数据状态
            if (rx_data == 'c') { // 遇到第一个结束符
                rx_state = 2;
            } else {
                // 将数据存入缓冲区
                if (packet_ptr < PACKET_BUFFER_SIZE - 1) {
                    rx_packet_buffer[packet_ptr++] = rx_data;
                }
            }
            break;

        case 2: // 等待第二个结束符 'd'
            if (rx_data == 'd') {
                rx_packet_buffer[packet_ptr] = '\0'; // 添加字符串结束符
                rt_sem_release(&rx_sem);             // 释放信号量，通知应用线程
                rx_state = 0;                        // 重置状态机
            } else { // 如果不是'd'，说明协议错误，重置
                rx_state = 0;
            }
            break;

        default: // 意外情况，重置状态机
            rx_state = 0;
            break;
    }
    return RT_EOK;
}

/**
 * @brief  初始化用于和 OpenMV 通信的 UART
 * @return 0 表示成功, -1 表示失败
 */
int openmv_uart_init(void)
{
    // 1. 查找串口设备
    serial_dev = rt_device_find(UART_DEVICE_NAME);
    if (!serial_dev)
    {
        LOG_E("查找 %s 设备失败!", UART_DEVICE_NAME);
        return -1;
    }

    // 2. 初始化接收信号量
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    // 3. 配置串口参数 (波特率等)
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = 115200;
    rt_device_control(serial_dev, RT_DEVICE_CTRL_CONFIG, &config);

    // 4. 以中断接收模式打开设备
    if (rt_device_open(serial_dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        LOG_E("以 INT_RX 模式打开 %s 设备失败", UART_DEVICE_NAME);
        return -1;
    }

    // 5. 设置接收回调函数
    rt_device_set_rx_indicate(serial_dev, uart_rx_indicate);

    LOG_I("OpenMV UART on %s Initialized successfully", UART_DEVICE_NAME);
    return 0;
}

/**
 * @brief  阻塞等待，直到从 OpenMV 接收到一个完整的数据包
 * @param  buffer 用于存储数据包的用户缓冲区
 * @param  size   用户缓冲区的大小
 * @return rt_err_t
 */
rt_err_t openmv_get_packet(char *buffer, rt_size_t size)
{
    rt_err_t result;
    // 永久等待信号量，直到回调函数释放它
    result = rt_sem_take(&rx_sem, RT_WAITING_FOREVER);

    if (result == RT_EOK)
    {
        // 成功获取信号量，将接收到的数据包复制到用户缓冲区
        strncpy(buffer, rx_packet_buffer, size - 1);
        buffer[size - 1] = '\0'; // 确保字符串正确结尾
    }
    return result;
}
