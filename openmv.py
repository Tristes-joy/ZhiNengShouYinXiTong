import sensor
import time
from pyb import UART, LED
led_red = LED(1)
led_green = LED(2)
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA)
sensor.set_contrast(1)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
uart = UART(3, 115200, timeout_char=1000)
clock = time.clock()
print("QR Code Scanner is running...")
while(True):
	clock.tick()
	img = sensor.snapshot()
	codes = img.find_qrcodes()
	if codes:
		led_green.on()
		led_red.off()
		qr_code = codes[0]
		payload = qr_code.payload()
		print("Found QR Code, payload:", payload)
		uart.write(payload)
		time.sleep_ms(500)
	else:
		led_green.off()