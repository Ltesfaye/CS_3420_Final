import serial # used for reading user input
import time	  # used for creating a minor delay
import struct # imports the struct class to issue a draw command
from Data import data

def readSerial(port,val):
	#sets up all the required data
	ser = serial.Serial()
	ser.baudrate = 115200 
	ser.port = port
	ser.open() # opens port for communication

	if (ser.is_open):
		print ('sucssusfully opened port!!!!!')
		time.sleep(2) # small delay to give the user time to read data

	else:
		print ('Unable to Open Port')
		return 

	ser.read(8)

	while(1): 
		#polls the data from our Serial Communication
		out = ser.readline().decode().strip().split()
		if (len(out) == 2):
			print ("HEre")
			#updates the value of lists that will be used to display
			#val.append((float)out[0],(float)out[1])
	
		elif (len(out) ==4):
			#resets the desplay
			#val.reset()
			print ("HOW")
		else:
			print (out)

def main():
	port = 'COM9' # specifies the port to open based on your device manager 
	values = data([0],[0]) #creates a default construction
	readSerial(port,values)

main() #starts our execution call

