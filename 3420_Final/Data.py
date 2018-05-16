import matplotlib.pyplot as plt
import numpy
import math
from BSpline import *
import time

hl, = plt.plot([], [],'o-r',dashes =[1,1])
hl_s, = plt.plot([], [],'-b')
plt.title('CS 3420 Final Project')
plt.xlabel('Relative X')
plt.ylabel('Relative Y')

plt.ion()
fig = plt.gcf()
ax = plt.gca()
fig.show()
fig.canvas.draw()

def update_line(hl, new_data,new_datay):
	# updates the the dotted line drawing 
    hl.set_xdata(numpy.append(hl.get_xdata(), new_data))
    hl.set_ydata(numpy.append(hl.get_ydata(), new_datay))
    ax.relim() 
    ax.autoscale_view() 
    plt.draw()

def update_Spline(hl, new_data, new_datay):
	# updates the spline drawing 
    hl.set_xdata(numpy.append([], new_data))
    hl.set_ydata(numpy.append([], new_datay))
    ax.relim() 
    ax.autoscale_view() 
    plt.draw()

def getDistance(a,b): # used for filtering out small movements?
	dist = (a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1])
	return dist
class data:
	def __init__(self, x_val,y_val):
		hl.set_ydata(np.array([0]))
		hl.set_xdata(np.array([0]))
		hl_s.set_ydata(np.array([0]))
		hl_s.set_xdata(np.array([0]))
		self.sPoint = [[x_val,y_val]]
		self.length = 1
		self.priorPoints = [0,0]

		
	def append(self,x_val,y_val):
		self.length +=1
		update_line(hl,x_val,y_val)
		self.sPoint.append([x_val, y_val])
		multiple =math.ceil(self.length/10)
		print ("Scale_up_Factor:  "+ str(multiple)) #used for debuging limit tets
		points = bspline(np.array(self.sPoint),n= (100*multiple),degree=3,periodic=False)
		update_Spline(hl_s,points[:,0],points[:,1])

	def getPoints(self):
		return self.spoints

	def reset(self):
		#resets the data for all the figures
		hl.set_ydata(np.array([0]))
		hl.set_xdata(np.array([0]))
		hl_s.set_ydata(np.array([0]))
		hl_s.set_xdata(np.array([0]))
		self.sPoint = [[0,0]]
		self.length =1

	def draw(self):
		fig.canvas.draw() # issues the figure draw update command
		