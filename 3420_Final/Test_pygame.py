import matplotlib.pyplot as plt
import numpy
import math
from BSpline import *
import time
 
hl, = plt.plot([], [])
hl_s, = plt.plot([], [])
plt.title('CS 3420 Final Project')
plt.xlabel('Relative X')
plt.ylabel('Relative Y')

plt.ion()
fig = plt.gcf()
ax = plt.gca()
fig.show()
fig.canvas.draw()








x = 0
count = 0

xPoints = [0]
yPoints = [0]
cv = [[0, 0]]
points=[]

while (x<4):
    # compute something
    if (count !=0):
    	xPoints.append(count)
    	yPoints.append(count * np.random.random_sample())
    	cv.append([count, count*np.random.random_sample()])

    plt.plot(xPoints, yPoints,'o-r',dashes= [2,2]) # plot something
    length = len(cv)
    if (length>6):
    	multiple = math.floor(length/6.0)
    	points = bspline(np.array(cv),n=(100*multiple),degree=3,periodic=False)
    	plt.plot(points[:,0],points[:,1], '-b')

    fig.canvas.draw()
    x+=0.1
    count += 1
    time.sleep(.4)

plt.show(fig)