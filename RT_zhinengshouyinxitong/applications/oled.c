/* applications/oled.c */

#include <rtdevice.h>
#include "oled.h"
#include "oled_font.h" // 引入字库

#define I2C_DEVICE_NAME     "i2c1"
#define OLED_ADDR           (0x78 >> 1) // RT-Thread API 使用7位地址, 0x3C

// --- 模块内部使用的静态变量和函数 ---

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

static void oled_write_cmd(rt_uint8_t cmd) {
    if (i2c_bus == RT_NULL) return;
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[2] = {0x00, cmd};
    msgs.addr = OLED_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 2;
    rt_i2c_transfer(i2c_bus, &msgs, 1);
}

static void oled_write_data(rt_uint8_t data) {
    if (i2c_bus == RT_NULL) return;
    struct rt_i2c_msg msgs;
    rt_uint8_t buf[2] = {0x40, data};
    msgs.addr = OLED_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 2;
    rt_i2c_transfer(i2c_bus, &msgs, 1);
}

static void oled_set_cursor(rt_uint8_t y_page, rt_uint8_t x_col) {
    oled_write_cmd(0xB0 | y_page);
    oled_write_cmd(0x10 | ((x_col & 0xF0) >> 4));
    oled_write_cmd(0x00 | (x_col & 0x0F));
}

static void oled_show_char(rt_uint8_t line, rt_uint8_t column, char ch) {
    rt_uint8_t c = ch - ' '; // 计算在ASCII字库中的偏移
    rt_uint8_t x = (column - 1) * 8;

    // 显示上半部分 (8x8)
    oled_set_cursor((line - 1) * 2, x);
    for (rt_uint8_t i = 0; i < 8; i++) {
        oled_write_data(OLED_F8x16[c][i]);
    }

    // 显示下半部分 (8x8)
    oled_set_cursor((line - 1) * 2 + 1, x);
    for (rt_uint8_t i = 0; i < 8; i++) {
        oled_write_data(OLED_F8x16[c][i + 8]);
    }
}

// --- 对外暴露的接口函数实现 ---

void oled_init(void) {
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(I2C_DEVICE_NAME);
    if (i2c_bus == RT_NULL) {
        rt_kprintf("Can't find %s device!\n", I2C_DEVICE_NAME);
        return;
    }

    rt_thread_mdelay(100);
    oled_write_cmd(0xAE); oled_write_cmd(0xD5); oled_write_cmd(0x80); oled_write_cmd(0xA8);
    oled_write_cmd(0x3F); oled_write_cmd(0xD3); oled_write_cmd(0x00); oled_write_cmd(0x40);
    oled_write_cmd(0xA1); oled_write_cmd(0xC8); oled_write_cmd(0xDA); oled_write_cmd(0x12);
    oled_write_cmd(0x81); oled_write_cmd(0xCF); oled_write_cmd(0xD9); oled_write_cmd(0xF1);
    oled_write_cmd(0xDB); oled_write_cmd(0x30); oled_write_cmd(0xA4); oled_write_cmd(0xA6);
    oled_write_cmd(0x8D); oled_write_cmd(0x14); oled_write_cmd(0xAF);

    oled_clear();
    rt_kprintf("OLED on %s initialized.\n", I2C_DEVICE_NAME);
}

void oled_clear(void) {
    for (rt_uint8_t j = 0; j < 8; j++) {
        oled_set_cursor(j, 0);
        for(rt_uint8_t i = 0; i < 128; i++) {
            oled_write_data(0x00);
        }
    }
}

void oled_show_string(rt_uint8_t line, rt_uint8_t column, char *str) {
    while (*str) {
        if (column > 16) { // 超出16列则换行
            column = 1;
            line++;
        }
        if (line > 4) { // 超出4行则返回
            return;
        }
        oled_show_char(line, column, *str);
        column++;
        str++;
    }
}
