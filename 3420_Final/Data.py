import numpy as np # temp being used for desplay purposes
import threading # used to start two threads which will be used for polling and displaying
from easplot import EasyPlot # Modified Version of MIT EasyPlot python library

class data:
	def __init__(self, x_val,y_val):
		self.x = x_val
		self.y = y_val
		self.graph = EasyPlot(self.x, self.y, label=r"$relative position$", figsize=(8,4), showlegend=True, 
                 ncol=2, ms=10, ls=':', markeredgewidth=1.5, xlabel='Relative-X',
                 ylabel='Realtive-Y', title='Work', color='b', marker='s')

	def append(self,x_val,y_val):
		self.x.append(x_val)
		self.y.append(y_val)
		self.graph.update()

	def getX(self):
		return self.x

	def getY(self):
		return self.y

	def reset(self):
		self.x = []
		self.y = []
		self.graph.reset()