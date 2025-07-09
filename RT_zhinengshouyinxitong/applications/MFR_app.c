/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-06     lth       the first version
 *
 */
#include "MFRC522.h"

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <stdio.h>
#include "packet.h"

information card_imformation;

static void rfid_thread_entry(void *parameter)
{
    unsigned char status;
    unsigned char buf[10];
    unsigned char SN[10];
    int a=0;
    MFRC522_Init();
    sprintf(SN,"0000");
    status = MFRC522_Request(PICC_REQALL, buf);
    while(1)
    {
        status = MFRC522_Request(PICC_REQALL, buf);//
        a++;
       if (status != MI_OK)
       {

           MFRC522_Reset();
           MFRC522_AntennaOff();
           MFRC522_AntennaOn();
       }
       status = MFRC522_Anticoll(buf); //
       if (status == MI_OK)
       {
           sprintf(SN,"%X%X%X%X",buf[0],buf[1],buf[2],buf[3]);
           sprintf((char*)card_imformation.id,SN);
           card_imformation.lens=strlen(card_imformation.id);
           if(strcmp(SN,"0000")!=0)
           {
               uart_queue_data(0x01,&card_imformation,sizeof(card_imformation));
           }
       }
       uart_queue_data(0x01,&card_imformation,sizeof(card_imformation));
        rt_thread_mdelay(1000);
    }
}




int rfid_task_init(void)
{
    rt_thread_t tid;

    // 创建RFID读取线程
    tid = rt_thread_create("rfid",
                          rfid_thread_entry,
                          RT_NULL,
                          1024,    // 栈大小
                          15,      // 优先级（中等级别）
                          10);     // 时间片

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
        rt_kprintf("RFID task created successfully.\n");
        return RT_EOK;
    }

    rt_kprintf("Failed to create RFID task.\n");
    return -RT_ERROR;
}
INIT_APP_EXPORT(rfid_task_init);

// 自动初始化（在系统启动时自动创建任务）
//INIT_APP_EXPORT(rfid_task_init);
