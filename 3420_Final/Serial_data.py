import serial # used for reading user input
import time	  # used for creating a minor delay
import random
import math
from Data import *

def readSerial(port,val):
	#sets up all the required data
	ser = serial.Serial()
	ser.baudrate = 115200  #sets the required braudband rate
	ser.port = port
	ser.open() # opens port for communication

	if (ser.is_open):
		print ('Sucssusfully opened port!!!!!')
		time.sleep(2) # small delay to give the user time to read data

	else:
		print ('Unable to Open Port!!!!!!')
		return 

	#ser.read(8) # not sure if it's currently doing anything
	#count = 0 # used for debuging
	'''if (count %10 == 5):
			#start_time = time.time() # uncomment to desplay computation time per adding points tested with 500 points and takes max 4/1000 to desplay
			val.append(count,count*random.random())
			#print(str( math.floor(count/10))+". " + "--- %s seconds ---" % (time.time() - start_time))
'''
	#samples about 5/100 of sec each loop
	while(1): 

		#polls the data from our Serial Communication
		out = ser.readline().decode().strip().split()
		#print (out)
		if (len(out) == 3 and out[2] == '121212'): #updates the value of lists that will be used to display
			val.updatelabel(0)
			temp0 = float(out[0])/10000
			temp1 = float(out[1])/10000
			val.append(float(temp0),float(temp1))

		elif (len(out) == 3 and out[2] == '1010'): #updates the value of lists that will be used to display
			val.updatelabel(1)
			temp0 = float(out[0])/10000
			temp1 = float(out[1])/10000
			val.append(float(temp0),float(temp1))

		elif (len(out) == 3 and out[2] == '1111'): #updates the value of lists that will be used to display
			val.updatelabel(2)
			temp0 = float(out[0])/10000
			temp1 = float(out[1])/10000
			val.append(float(temp0),float(temp1))
			
			
	
		elif (len(out) == 1 and out[0] == '100000'):
			val.reset() #resets the desplay
		
		val.draw() # issues a draw command


def main():
	port = 'COM9' # specifies the port to open based on your device manager 
	values = data(0,0) #creates a default construction
	values.draw() # desplays the blank screen to begin with
	readSerial(port,values)
	#ser.close()


main() #starts our execution call

