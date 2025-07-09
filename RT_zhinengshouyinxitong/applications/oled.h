/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-05     32927       the first version
 */
#ifndef APPLICATIONS_OLED_H_
#define APPLICATIONS_OLED_H_

void oled_init(void);
void oled_clear(void);
void oled_show_string(rt_uint8_t line, rt_uint8_t column, char *str);

#endif /* APPLICATIONS_OLED_H_ */
