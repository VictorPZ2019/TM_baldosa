#!/usr/bin/env python

import serial
import csv

arduino_port = "/dev/ttyACM0"
baud = 115200
filename = "datos.csv"

ser = serial.Serial(arduino_port, baud)
print("conectado al puerdo: " + arduino_port)

while True:
    try:
        file = open(filename, "a")
        print("file creado")
        getData = str(ser.readline())
        data = getData[0:][:-2]
        print(data)
        file = open(filename, "a")
        file.write(data + "\n")
    except:
        #file.close()
        print("Keyboard Interrupt")
        break

