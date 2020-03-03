#!/usr/bin/env python3
# chapter 24 in python
# sudo apt-get install python3-pip
# python3 -m pip install pyserial
# sudo apt-get install python3-matplotlib
import serial
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyUSB0',230400,rtscts=1)
print('Opening port: ')
print(ser.name)
ser.write(b'1.0 1.0\n')                     # Kp Ki
sampnum = 0
read_samples = 10
ADCval = []
ref = []

while read_samples > 1:
    data_read = ser.read_until(b'\n',50)
    data_text = str(data_read,'utf-8')
    data = list(map(int,data_text.split()))
    if(len(data)==3):
        read_samples = data[0]
        ADCval.append(data[1])
        ref.append(data[2])
        sampnum = sampnum + 1

                                            # plot it
t = range(len(ADCval))                      # time array
plt.plot(t,ref,'b*-',label="Reference")
plt.plot(t,ADCval,'r*-',label="ADC value")
plt.ylabel('Brightness (ADC counts)')
plt.xlabel('Sample number (at 100 Hz)')
plt.legend()
plt.show()

ser.close()                                 # be sure to close the port
