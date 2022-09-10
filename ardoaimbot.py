import cv2
from mss import mss
import numpy as np
import win32api
import serial
 
 
fov = int(input("FOV: "))
 
sct = mss()
 
 
arduino = serial.Serial('COM6', 115200)
 
screenshot = sct.monitors[1]
screenshot['left'] = int((screenshot['width'] / 2) - (fov / 2))
screenshot['top'] = int((screenshot['height'] / 2) - (fov / 2))
screenshot['width'] = fov
screenshot['height'] = fov
center = fov/2

embaixo = np.array([140,111,160])
emcima = np.array([148,154,194])
 
speed = float(input("SPEED: "))
print("ARDUINO LOADED")
 
def mousemove(x):
    if x < 0: 
        x = x+256 
 
    pax = [int(x)]
    arduino.write(pax)
 
 
while True:
    if win32api.GetAsyncKeyState(0x01) < 0:
        
        img = np.array(sct.grab(screenshot))
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv, embaixo,emcima)
        kernel = np.ones((3,3), np.uint8)
        dilated = cv2.dilate(mask,kernel,iterations= 5)
        thresh = cv2.threshold(dilated, 60, 255, cv2.THRESH_BINARY)[1]
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
        if len(contours) != 0:
            mouse = cv2.moments(thresh)
            pixel = (int(mouse["m10"] / mouse["m00"]), int(mouse["m01"] / mouse["m00"]))
            
            aimzao = pixel[0] + 2
            
            diff_x = int(aimzao - center)
            
            alvo = diff_x * speed
                
            mousemove(alvo)