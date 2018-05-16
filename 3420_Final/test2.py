import matplotlib.pyplot as plt
import numpy
import math
import time

hl, = plt.plot([], [],'o-r',dashes =[1,1])
plt.title('CS 3420 Final Project')
plt.xlabel('Relative X')
plt.ylabel('Relative Y')

plt.ion()
fig = plt.gcf()
ax = plt.gca()
fig.show()
fig.canvas.draw()

def update_line(hl, new_data,new_datay):
    hl.set_xdata(numpy.append(hl.get_xdata(), new_data))
    hl.set_ydata(numpy.append(hl.get_ydata(), new_datay))
    ax.relim() 
    ax.autoscale_view() 
    plt.draw()

x = 0
count = 0

xPoints = [0]
yPoints = [0]
cv = [[0, 0]]
points=[]
while(x<4):
	if (count !=0):
		update_line(hl,count,count * numpy.random.random_sample())

	x+=.1
	count +=1
	fig.canvas.draw()
	time.sleep(.3)

plt.show(fig)