# chapter 24 in python3
# to run in linux terminal: `python3 ch24.py --Kp 2.0 --Ki 10.0`
# close plot to terminate program

import serial
import argparse
ser = serial.Serial('/dev/ttyUSB0',230400,rtscts=1)
print('Opening port: ')
print(ser.name)

"""
arg parse things
"""
parser = argparse.ArgumentParser()
parser.add_argument('--Kp', type=float, default=1.0)
parser.add_argument('--Ki', type=float, default=1.0)
args = parser.parse_args()

write_string = '{} {}\n'
ser.write(write_string.format(args.Kp,args.Ki).encode()) # Kp Ki
print('Writing:', write_string.format(args.Kp,args.Ki))

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
import matplotlib.pyplot as plt
t = range(len(ADCval)) # time array
plt.plot(t,ref,'b*-',label='Reference')
plt.plot(t,ADCval,'r*-',label='ADC value')
plt.xlabel('Sample Number (at 100 Hz)')
plt.ylabel('Brightness (ADC counts)')
plt.suptitle('LED Brightness Feedback Control Demo')
plt.title('Kp: {}, Ki: {}' .format(args.Kp,args.Ki))
plt.legend()
plt.grid()
plt.show()

# be sure to close the port
ser.close()
