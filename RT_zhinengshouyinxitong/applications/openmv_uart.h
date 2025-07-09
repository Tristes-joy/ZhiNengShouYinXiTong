/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-06     32927       the first version
 */
#ifndef APPLICATIONS_OPENMV_UART_H_
#define APPLICATIONS_OPENMV_UART_H_

int openmv_uart_init(void);
rt_err_t openmv_get_packet(char *buffer, rt_size_t size);

#endif /* APPLICATIONS_OPENMV_UART_H_ */
