# color tracking with conic mirror - By: EmaMaker - wed 15 jan 2020
# Based on:
# color tracking - By: paolix - ven mag 18 2018

# Automatic RGB565 Color Tracking Example
#

import sensor, image, time, pyb, math

from pyb import UART
uart = UART(3,19200, timeout_char = 1000)

START_BYTE = chr(105) #'i'
END_BYTE = chr(115) #'s'
BYTE_UNKNOWN = chr(116) #'t'

y_found = False
b_found = False

#From Arduino Documentation at: https://www.arduino.cc/reference/en/language/functions/math/map/
def val_map(x, in_min, in_max, out_min, out_max):
    x = int(x)
    in_min = int(in_min)
    in_max = int(in_max)
    out_min = int(out_min)
    out_max = int(out_max)
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)


# LED Setup ##################################################################
red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)

red_led.off()
green_led.off()
blue_led.on()
##############################################################################


thresholds = [  (69, 100, -2, 15, 16, 40),    # thresholds yellow goal
                (32, 77, -2, 12, -48, -10)]  # thresholds blue goal (6, 31, -15, 4, -35, 0)

roi = (0, 6, 318, 152)

# Camera Setup ###############################################################
'''sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)         # must be turned off for color tracking
sensor.set_auto_whitebal(False)     # must be turned off for color tracking
sensor.set_auto_exposure(False, 10000) vbc
#sensor.set_backlight(1)
#sensor.set_brightness(+2 )
#sensor.set_windowing(roi)
clock = time.clock()'''

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_contrast(1)
sensor.set_saturation(0)
sensor.set_brightness(3)
sensor.set_quality(0)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(False, 3500)
sensor.set_auto_gain(True)
sensor.skip_frames(time = 300)

clock = time.clock()
##############################################################################


while(True):
    clock.tick()

    blue_led.off()

    y_found = False
    b_found = False

    tt_yellow = [(0,999,0,1)]     ## creo una lista di tuple per il giallo, valore x = 999 : non trovata
    tt_blue = [(0,999,0,2)]       ## creo una lista di tuple per il blue, valore x = 999 : non trovata

    img = sensor.snapshot()
    for blob in img.find_blobs(thresholds, pixels_threshold=40, area_threshold=50, merge = True):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())

        if (blob.code() == 1):
            tt_yellow = tt_yellow +  [ (blob.area(),blob.cx(),blob.cy(),blob.code() ) ]
            y_found = True
        if (blob.code() == 2):
            tt_blue = tt_blue +  [ (blob.area(),blob.cx(),blob.cy(),blob.code() ) ]
            b_found = True

    tt_yellow.sort(key=lambda tup: tup[0])  ## ordino le liste
    tt_blue.sort(key=lambda tup: tup[0])    ## ordino le liste

    ny = len(tt_yellow)
    nb = len(tt_blue)

    y_area, y1_cx, y1_cy, y_code = tt_yellow[ny-1]
    b_area, b1_cx, b1_cy, b_code = tt_blue[nb-1]

    y_cx = int(img.width() / 2 - y1_cx)
    y_cy = int(img.height() / 2 - y1_cy)
    b_cx = int(img.width() / 2 - b1_cx)
    b_cy = int(img.height() / 2 - b1_cy)

    #Normalize data between 0 and 100
    if y_found == True:
        y_cx = val_map(y_cx, -img.width() / 2, img.width() / 2, 100, 0)
        y_cy = val_map(y_cy, -img.height() / 2, img.height() / 2, 0, 100)
        #Prepare for send as a list of characters
        s_ycx = chr(y_cx)
        s_ycy = chr(y_cy)
    else:
        y_cx = BYTE_UNKNOWN
        y_cy = BYTE_UNKNOWN
        #Prepare for send as a list of characters
        s_ycx = y_cx
        s_ycy = y_cy

    if b_found == True:
        b_cx = val_map(b_cx, -img.width() / 2, img.width() / 2, 100, 0)
        b_cy = val_map(b_cy, -img.height() / 2, img.height() / 2, 0, 100)

        #Prepare for send as a list of characters
        s_bcx = chr(b_cx)
        s_bcy = chr(b_cy)
    else:
        b_cx = BYTE_UNKNOWN
        b_cy = BYTE_UNKNOWN
        #Prepare for send as a list of characters
        s_bcx = b_cx
        s_bcy = b_cy

    print(str(y_cx) + " | " + str(y_cy) + "  ---  " + str(b_cx) + " | " + str(b_cy))


    uart.write(START_BYTE)
    uart.write(s_bcx)
    uart.write(s_bcy)
    uart.write(s_ycx)
    uart.write(s_ycy)
    uart.write(END_BYTE)

