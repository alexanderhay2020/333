try:
    import nscopeapi as nsapi
    ns = nsapi.nScope()
except Exception as e:
    print("Unable to communicate with nScope")
    print(e)
else:
    print("Successfully opened connection to nScope!")

# open Ch1 at 1kHz and ask for 3 seconds of data
ns.setChannelsOn(True,False,False,False)
ns.setSampleRateInHz(1000)
ns.requestData(3000)

voltCh1 = []

while ns.requestHasData():
    d = ns.readData(1)
    voltCh1.append(d)

# plot it
import matplotlib.pyplot as plt 
t = range(len(voltCh1)) # time array in ms
plt.plot(t,voltCh1,'r*-')
plt.ylabel('time in ms')
plt.xlabel('volts')
plt.show()