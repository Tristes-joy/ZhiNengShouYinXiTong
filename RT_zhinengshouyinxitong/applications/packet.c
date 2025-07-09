#include "packet.h"
#include "crc8_crc16.h"

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"



#define UART_NAME       "uart2"
#define LED1_PIN    GET_PIN(D, 15)
#define LED2_PIN    GET_PIN(D, 14)
#define BEEP_PIN   GET_PIN(D, 13)
extern rt_mq_t uart_send_queue;

msg_end_info msg_end;
frame_header_struct_t referee_send_header;

static rt_sem_t rx_sem;            // 接收信号量
static rt_device_t serial = RT_NULL;
static rt_timer_t beep_timer;       // 蜂鸣器定时器
static rt_timer_t led_timer;        // LED定时器

uint8_t rx_count;
uint8_t flag_b;

enum {
    CMD_START,
    CMD_DATA,
    CMD_END
};


static rt_err_t uart_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(rx_sem);  // 释放信号量通知线程
    return RT_EOK;
}

static void uart_rx_thread_entry(void *parameter)
{
    rt_uint8_t ch;
    static rt_uint8_t cmd_state = CMD_START;
    static rt_uint8_t cmd_data;

    while (1) {
        /* 等待接收信号量 */
        if (rt_sem_take(rx_sem, RT_WAITING_FOREVER) == RT_EOK) {
            /* 读取所有可用数据 */
            while (rt_device_read(serial, 0, &ch, 1) == 1) {
                switch (cmd_state) {
                case CMD_START:
                    if (ch == '[') {  // 命令开始标志
                        cmd_state = CMD_DATA;
                    }
                    break;

                case CMD_DATA:
                    if (ch == '1' || ch == '2') {
                        cmd_data = ch;  // 保存命令数据
                        cmd_state = CMD_END;
                    } else {
                        cmd_state = CMD_START;  // 无效数据
                    }
                    break;

                case CMD_END:
                    if (ch == ']') {  // 命令结束标志
                        /* 执行命令 */
                        if (cmd_data == '1') {//支付超时
                            rt_pin_write(BEEP_PIN, PIN_HIGH); // 开启蜂鸣器
                            rt_pin_write(LED2_PIN, PIN_HIGH); // 开启灯
                            rt_timer_stop(beep_timer);
                            rt_timer_start(beep_timer); // 启动5秒定时
                            rt_kprintf("Beep on for 5s\n");
                        }
                        else if (cmd_data == '2') {//支付成功
                            rt_pin_write(LED1_PIN, PIN_HIGH); // 点亮LED
                            rt_pin_write(BEEP_PIN, PIN_HIGH);
                            rt_pin_write(LED2_PIN, PIN_LOW);
                            rt_timer_stop(led_timer);
                            rt_timer_start(led_timer); // 启动2秒定时
                            rt_kprintf("LED on for 5s\n");
                        }
                    }
                    cmd_state = CMD_START;  // 重置状态机
                    break;
                }
            }
        }
    }
}

static void beep_timeout(void *param)
{
    rt_pin_write(LED2_PIN, PIN_LOW); // 关闭灯
    rt_pin_write(BEEP_PIN, PIN_LOW); // 关闭蜂鸣器
    rt_kprintf("Beep off\n");
}

/* LED定时器回调 */
static void led_timeout(void *param)
{
    rt_pin_write(LED1_PIN, PIN_LOW);  // 关闭LED
    rt_pin_write(BEEP_PIN, PIN_LOW); // 关闭蜂鸣器
    rt_kprintf("LED off\n");
}

// 初始化串口
int uart_init(void)
{

    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED2_PIN, PIN_LOW); // 初始关闭蜂鸣器
    rt_pin_write(LED1_PIN, PIN_LOW);   // 初始关闭LED
    rt_pin_write(BEEP_PIN, PIN_LOW);
    beep_timer = rt_timer_create("beep_tmr", beep_timeout,
                                    RT_NULL, 5000, RT_TIMER_FLAG_ONE_SHOT);
    led_timer = rt_timer_create("led_tmr", led_timeout,
                                  RT_NULL, 500, RT_TIMER_FLAG_ONE_SHOT);

    serial = rt_device_find(UART_NAME);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", UART_NAME);
        return -RT_ERROR;
    }

    rx_sem = rt_sem_create("rx_sem", 0, RT_IPC_FLAG_FIFO);
        if (rx_sem == RT_NULL) {
            rt_kprintf("create semaphore failed\n");
            return -RT_ERROR;
        }

    if (rt_device_open(serial,RT_DEVICE_OFLAG_RDWR| RT_DEVICE_FLAG_INT_RX) != RT_EOK)
        {
            rt_kprintf("open %s failed!\n", UART_NAME);
            return -RT_ERROR;
        }

    // 配置串口参数（可选）
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;  // 设置波特率
    config.data_bits = DATA_BITS_8;       // 数据位
    config.stop_bits = STOP_BITS_1;       // 停止位
    config.parity    = PARITY_NONE;       // 校验位

    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);
    rt_device_set_rx_indicate(serial, uart_rx_ind) ;

    rt_kprintf("%s init success!\n", UART_NAME);


    rt_thread_t thread = rt_thread_create(
            "uart_rx",
            uart_rx_thread_entry,
            RT_NULL,
            1024,
            25,
            10
        );

        if (thread != RT_NULL) {
            rt_thread_startup(thread);
        } else {
            rt_kprintf("create thread failed\n");
            rt_device_close(serial);
            rt_sem_delete(rx_sem);
            return -RT_ERROR;
        }

        return RT_EOK;
}
INIT_APP_EXPORT(uart_init);



static void uart_send(const void *buffer, rt_size_t size)
{
    if (serial == RT_NULL)
    {
        rt_kprintf("UART not initialized!\n");
        return;
    }

    rt_size_t sent = 0;
    while (sent < size)
    {
        rt_size_t bytes = rt_device_write(serial, 0,
                                         (const rt_uint8_t*)buffer + sent,
                                         size - sent);
        if (bytes == 0)
        {
            rt_thread_mdelay(1); // 短延时防止忙等
        }
        sent += bytes;
    }
}

/* 将数据放入队列 */
void uart_queue_data(uint16_t cmd_id, void* buf, uint16_t len)
{
    uint16_t index = 0;
    uint8_t queue_data[128];        // 定义队列缓存数组
    // 将CMD_ID放入数组
    memcpy(queue_data,  (void*)&cmd_id, sizeof(uint16_t));
    index +=sizeof(uint16_t);
    // 添加数据
    memcpy(queue_data + index, (void*)buf, len);

    // 检查队列是否初始化
    if (uart_send_queue == RT_NULL)
    {
        rt_kprintf("UART queue not initialized!\n");
        return;
    }

    // 将数据放入队列
    if (rt_mq_send(uart_send_queue, &queue_data, sizeof(queue_data)) != RT_EOK)
    {
        rt_kprintf("Failed to send data to UART queue!\n");
    }
}

/* 从队列取出数据并进行协议序列化 */
void uart_dequeue_send_data(void* buf, rt_size_t size)
{
    uint16_t cmd_id;
    memcpy(&cmd_id,buf,sizeof(uint16_t));

    // 根据命令ID处理不同数据类型
    switch(cmd_id)
    {
        case 0x01:
             encode_send_data(cmd_id,((uint8_t*)buf+2),sizeof(information));
             break;
        case 0x02:
             encode_send_data(cmd_id,((uint8_t*)buf+2),sizeof(charge_inf));
             break;
        default:
            //rt_kprintf("Unknown command ID: 0x%04X\n", cmd_id);
            break;
    }
}




void encode_send_data(uint16_t cmd_id, void* buf, uint16_t len){
    static uint8_t send_buf[128];   // 定义发送数据缓存数组
    uint16_t index = 0;             // 序号

    msg_end.end1=END1_SOF;
    // 初始化帧头结构体
    //frame_header_struct_t referee_send_header;  // 定义帧头结构体
    referee_send_header.SOF = HEADER_SOF;       // 数据帧起始字节
    referee_send_header.data_length = len;      // 数据帧中 data 的长度
    referee_send_header.seq++;                  // 包序号

    /* 生成CRC8校验 */
    append_CRC8_check_sum((uint8_t*)&referee_send_header, sizeof(frame_header_struct_t));
    memcpy(send_buf, (uint8_t*)&referee_send_header, sizeof(frame_header_struct_t));
    index += sizeof(frame_header_struct_t);
    // 填充CMD_ID
    memcpy(send_buf + index, (void*)&cmd_id, sizeof(uint16_t));
    index += sizeof(uint16_t);
    // 填充数据包
    memcpy(send_buf + index, (void*)buf, len);
    index += len;

    /* 生成CRC16校验 */
    append_CRC16_check_sum(send_buf, REF_HEADER_CRC_CMDID_LEN + len);
    index += sizeof(uint16_t);

    // 添加视觉解包帧尾
    memcpy(send_buf + index,(void*)&msg_end,sizeof(msg_end));
    index += sizeof(msg_end);

    //调用底层发送函数
    uart_send(send_buf, index);
}
