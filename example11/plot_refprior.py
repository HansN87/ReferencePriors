#!/usr/bin/env python

import numpy 
import pylab as plt
from scipy import interpolate

const = 15.2821 # reference prior at theta=0.5 (from simulation)

x = []
y = []
with open("result_refprior.txt", 'r') as f:
     data = f.readlines()
     for line in data:
            thisx, thisy = line.split()
	    x.append(float(thisx))
	    y.append(float(thisy))

x=numpy.asarray(x)
y=numpy.asarray(y)

y = y / const * 2./numpy.pi
xnew = numpy.linspace(x[0],x[-1], 10000)

import scipy
from scipy.special import psi

ana = lambda x: x**(-0.5)*(1-x)**(-0.5)
ynew_ana = ana(xnew) / ana(0.5) * 2./numpy.pi

fig = plt.figure(figsize=(8, 6), dpi=500)
ax = plt.axes()
ax.plot(x, y, "ro", label="simulation")
ax.plot(xnew, ynew_ana, "g-", label="Be(1/2,1/2)")
ax.set_ylabel('$\\mathbf{\\pi(\\theta)}$', position=(0., 1.), va='top', ha='right', fontsize=18)
ax.set_xlabel('$\\mathbf{\\theta}$', position=(1., 0.), va='bottom', ha='right', fontsize=18)
ax.yaxis.set_label_coords(-0.1, 1.)
ax.xaxis.set_label_coords(1.0, -0.12)
ax.tick_params(axis='y', which='major', labelsize=15, pad=5)
ax.tick_params(axis='x', which='major', labelsize=15, pad=5)
ax.set_ylim([0.0,3.5])

fig.suptitle('reference prior for triangle(theta) on (0,1)', fontsize=18)

leg = ax.legend(bbox_to_anchor=[0.87, 0.95], loc='upper right', prop={'size':16}, ncol=2, fancybox=True)

plt.savefig("refprior.png")
           
          
         
        
       
      
     
    
