/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-06     lth       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
extern void uart_dequeue_send_data(void* buf, rt_size_t size);

#include "stdio.h"
/* 定义队列元素结构体 */

/* 定义全局变量 */
rt_mq_t uart_send_queue = RT_NULL;
static rt_uint8_t uart_queue_buf[128];  // 队列接收缓冲区

/* 初始化串口发送队列 */
int uart_queue_init(void)
{
    // 创建消息队列
    uart_send_queue = rt_mq_create("uart_q",
                                  128, // 每个消息的大小
                                  10,                      // 队列深度
                                  RT_IPC_FLAG_FIFO);        // 先进先出

    if (uart_send_queue == RT_NULL)
    {
        rt_kprintf("Failed to create UART send queue!\n");
        return -RT_ERROR;
    }

    rt_kprintf("UART send queue created successfully.\n");
    return RT_EOK;
}
INIT_APP_EXPORT(uart_queue_init);


/* 串口发送任务 */
static void uart_send_thread_entry(void *parameter)
{
    rt_err_t result;

    //rt_kprintf("UART send task started.\n");

    while (1)
    {

         //从队列接收数据
        //rt_kprintf("UART send task started.\n");
        result = rt_mq_recv(uart_send_queue,
                           uart_queue_buf,
                           sizeof(uart_queue_buf),
                           RT_WAITING_FOREVER);  // 永久等待

        if (result == RT_EOK)
        {
            // 处理并发送数据
            uart_dequeue_send_data(uart_queue_buf, sizeof(uart_queue_buf));
        }
        else
        {
            rt_kprintf("Error receiving from UART queue: %d\n", result);
        }

        // 短暂延时，让出CPU
        rt_thread_mdelay(100);
    }
}

/* 创建串口发送任务 */
int uart_send_task_init(void)
{
    rt_thread_t tid;

    // 创建串口发送线程
    tid = rt_thread_create("uart_tx",
                          uart_send_thread_entry,
                          RT_NULL,
                          1024,     // 栈大小
                          12,       // 优先级（高于普通任务）
                          10);      // 时间片

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
        rt_kprintf("UART send task created successfully.\n");
        return RT_EOK;
    }

    rt_kprintf("Failed to create UART send task.\n");
    return -RT_ERROR;
}
INIT_APP_EXPORT(uart_send_task_init);
