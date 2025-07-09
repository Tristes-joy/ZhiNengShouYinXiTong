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
#include <stdio.h>
#include <string.h>
#include "oled.h"
#include "openmv_uart.h"
#include "qr_scanner_app.h"
#include "packet.h"
#include <stdlib.h>
#define DBG_TAG "qr_app"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include <rtdevice.h>
#include "drv_common.h"

// --- 物品数据库 ---
typedef struct {
    const char* id;       // 物品ID (来自二维码)
    const char* name;     // 物品名称
    const char* price;    // 物品价格
} Item;

charge_inf imf;

#define BEEP_PIN   GET_PIN(D, 13)

// 将数据库定义为 const，可以节省 RAM
const Item itemDatabase[] = {
    {"APPLE",  "PingGuo",  "5.1"},
    {"BANANA", "XiangJiao", "3.5"},
    {"ORANGE", "ChengZi",  "4.1"},
    {"WATER",  "KuangQuanShui", "2.0"}
};
const int databaseSize = sizeof(itemDatabase) / sizeof(itemDatabase[0]);

/**
 * @brief  根据 ID 在数据库中查找物品信息
 * @param  id 从二维码读取到的字符串
 * @return 指向找到的Item结构体的指针, 如果没找到则返回NULL
 */
const Item* findItemById(const char* id)
{
    for (int i = 0; i < databaseSize; i++) {
        if (strcmp(id, itemDatabase[i].id) == 0) {
            return &itemDatabase[i]; // 找到匹配项，返回其地址
        }
    }
    return NULL; // 遍历完数据库都未找到，返回NULL
}

// --- 主应用线程入口函数 ---
static void qr_scanner_thread_entry(void *parameter)
{
    // 1. 初始化外设
    oled_init();
    if (openmv_uart_init() != 0) {
        LOG_E("OpenMV 通信初始化失败，线程终止。");
        oled_show_string(1, 1, "UART Init Fail!");
        return; // 退出线程
    }

    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT); // 设置为推挽输出模式
    rt_pin_write(BEEP_PIN, PIN_LOW);        // 默认不响 (低电平)

    // 2. 显示初始信息
    oled_clear();
    oled_show_string(1, 1, "System Ready...");
    oled_show_string(2, 1, "Waiting for QR..");
    LOG_I("System Ready.. Waiting for QR..");

    char rx_buffer[100];

    // 3. 主循环
    while (1)
    {
        // 阻塞在这里，直到 openmv_uart 模块收到一个完整的数据包
        if (openmv_get_packet(rx_buffer, sizeof(rx_buffer)) == RT_EOK)
        {
            LOG_I("FindID: %s", rx_buffer);
            const Item* foundItem = findItemById(rx_buffer);

            oled_clear();

            if (foundItem != NULL)
            {
                //LOG_I("FindItem: %s, Price: %s", foundItem->name, foundItem->price);
                rt_pin_write(BEEP_PIN, PIN_HIGH); // 高电平，蜂鸣器响
                rt_thread_mdelay(150);            // 持续响150ms
                rt_pin_write(BEEP_PIN, PIN_LOW);  // 低电平，关闭蜂鸣器

//                oled_show_string(1, 1, "Item Found:");
                strcpy(imf.name,foundItem->name);
                float price=strtof(foundItem->price,NULL);
                imf.price = price*100;
                //LOG_I("FindItem: %s, Price: %s", foundItem->name, imf.price);
                imf.nam_len=strlen(foundItem->name);

//                oled_show_string(2, 1, (char*)foundItem->name);
//                oled_show_string(3, 1, (char*)foundItem->price);
                // OLED一行通常是16个英文字符，缓冲区大小设置得稍大一些以防万一
                char display_line1[20];
                char display_line2[20];
                // 使用 snprintf 格式化要显示的字符串
                // snprintf 是 sprintf 的安全版本，可以防止缓冲区溢出
                snprintf(display_line1, sizeof(display_line1), "Name: %s", foundItem->name);
                snprintf(display_line2, sizeof(display_line2), "Price: %s yuan", foundItem->price);
                oled_show_string(1, 1, "Item Found:");
                // 显示格式化后的字符串
                oled_show_string(2, 1, display_line1);
                oled_show_string(3, 1, display_line2);

                uart_queue_data(0x02,&imf,sizeof(charge_inf));
            }
            else
            {
                LOG_W("DisfindedID '%s'", rx_buffer);
                oled_show_string(1, 1, "Item Not Found!");
                oled_show_string(3, 1, "ID:");
                oled_show_string(4, 1, rx_buffer); // 显示未知的ID
            }
        }
    }
}

/**
 * @brief  创建并启动主应用线程
 * @return 0 表示成功
 */
int start_qr_scanner_app(void)
{
    rt_thread_t tid = rt_thread_create("qr_scanner",
                                       qr_scanner_thread_entry, RT_NULL,
                                       2048,           // (2KB)
                                       25,             // 优先级
                                       10);            // 时间片

    if (tid != RT_NULL) {
        rt_thread_startup(tid);
        LOG_I("QRthread Started");
    } else {
        LOG_E("QRthread failed to Start");
        return -1;
    }
    return 0;
}
// 将此函数导出到 MSH 命令行，方便调试
// 编译下载后，可以在终端输入 start_qr_scanner_app 来运行此应用
MSH_CMD_EXPORT(start_qr_scanner_app, Start the QR code scanner application);
