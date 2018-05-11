
import numpy as np # temp being used for desplay purposes
from easplot import * # Modified Version of MIT EasyPlot python library
import time


x = np.linspace(0, 10, 10)

eplot = EasyPlot(x, x**2, label=r"$y = x^2$", figsize=(8,4), showlegend=True, 
                 ncol=2, ms=10, ls=':', markeredgewidth=1.5, xlabel='x',
                 ylabel='y', title='Work', color='b', marker='s')




eplot._update(x, 0.15*x**3, label='$y = 0.15x^3$', c='c', ls='-', marker='D')

print('Huh')