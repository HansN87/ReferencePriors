#!/usr/bin/env python

import numpy 
import pylab as plt
from scipy import interpolate

const = 85.0041 # ref prior of theta = 2

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

y = y / const
xnew = numpy.linspace(x[0],x[-1], 10000)


import scipy
from scipy.special import psi

ana = lambda x: (2*x-1)/(x*(x-1))*numpy.exp(psi(2*x/(2*x-1)))
ynew_ana = ana(xnew) / ana(2.)

fig = plt.figure(figsize=(8, 6), dpi=500)
ax = plt.axes()
ax.plot(x, y, "ro", label="simulation")
ax.plot(xnew, ynew_ana, "g-", label="exact result")
ax.set_ylabel('$\\mathbf{\\pi(\\theta)}$', position=(0., 1.), va='top', ha='right', fontsize=18)
ax.set_xlabel('$\\mathbf{\\theta}$', position=(1., 0.), va='bottom', ha='right', fontsize=18)
ax.yaxis.set_label_coords(-0.1, 1.)
ax.xaxis.set_label_coords(1.0, -0.12)
ax.tick_params(axis='y', which='major', labelsize=15, pad=5)
ax.tick_params(axis='x', which='major', labelsize=15, pad=5)
ax.set_ylim([-1,10])

fig.suptitle('reference prior for unif($\\theta$,$\\theta^2$)', fontsize=18)

plt.legend()

plt.savefig("refprior.png")
           
          
         
        
       
      
     
    
