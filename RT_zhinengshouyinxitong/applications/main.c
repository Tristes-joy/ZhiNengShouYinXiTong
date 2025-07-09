/* applications/main.c for Step 1 */
#include <rtthread.h>
#include <rtdevice.h>
#include "oled.h"
#include "qr_scanner_app.h"
#include "led_control.h"

int main(void)
{
    start_qr_scanner_app(); // 启动应用线程

    led_control_init();
    return 0;
}
