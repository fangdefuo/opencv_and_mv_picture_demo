import sensor, image, time
from pyb import UART, LED
import json
# For color tracking to work really well you should ideally be in a very, very,
# very, controlled enviroment where the lighting is constant...
#yellow_threshold   = (65, 100, -10, 6, 24, 51)
#yellow_threshold   = (63,44,31,70,-35,80)
red_threshold_01 = (61, 69, 39, 54, 23, 50)
# You may need to tweak the above settings for tracking green things...
# Select an area in the Framebuffer to copy the color settings.

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

uart = UART(3, 115200)
led= LED(1)

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob=blob
            max_size = blob.pixels()
    return max_blob

def send_optical_flow_packet(x, y):
    result=bytearray([0x3A,0xA3,10,0x19,(x>>8),x,(y>>8),y,0x00,0x00])
    sBcc=0
    for i in range(2,8):
        if(result[i] < 0):
            result[i] = result[i] + 256
            sBcc =sBcc + result[i]
        else:
            sBcc =sBcc + result[i]
    result[8] = (sBcc >> 8)
    result[9] = sBcc
    uart.write(result)

    #temp = struct.pack("<bbbbbbbbbb",
                       #0x3A,
                       #0xA3,
                       #char(10),
                       #0x19,
                       #char( (x>>8)&0x00FF), # up sample by 4
                       #char(x&0x00FF),
                       #char( (y>>8)&0x00FF), # up sample by 4
                       #char(y&0x00FF),
                       #result[9],
                       #result[10])


while(True):
    # uart.write("hello world!")

    img = sensor.snapshot() # Take a picture and return the image.

    blobs = img.find_blobs([red_threshold_01])
    if blobs:
        max_blob=find_max(blobs)
        print('sum :', len(blobs))
        img.draw_rectangle(max_blob.rect())
        img.draw_cross(max_blob.cx(), max_blob.cy())

        output_str="[%d,%d]" % (max_blob.cx(),max_blob.cy()) #方式1
        #output_str=json.dumps([max_blob.cx(),max_blob.cy()]) #方式2
        print('you send:',output_str)

        send_optical_flow_packet(max_blob.cx(),max_blob.cy())
        led.on()
    else:
        led.off()
        print('not found!')


