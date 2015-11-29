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
f = interpolate.UnivariateSpline(x, y, k=5, s=0)
xnew = numpy.linspace(x[0],x[-1])
ynew = f(xnew)

fig = plt.figure(figsize=(8, 6), dpi=500)
ax = plt.axes()
ax.plot(x, y, "ro")
ax.plot(xnew, ynew, "k-")
ax.set_ylabel('$\\mathbf{\\pi(\\theta)}$', position=(0., 1.), va='top', ha='right', fontsize=18)
ax.set_xlabel('$\\mathbf{\\theta}$', position=(1., 0.), va='bottom', ha='right', fontsize=18)
ax.yaxis.set_label_coords(-0.1, 1.)
ax.xaxis.set_label_coords(1.0, -0.12)
ax.tick_params(axis='y', which='major', labelsize=15, pad=5)
ax.tick_params(axis='x', which='major', labelsize=15, pad=5)
ax.set_ylim([-1,10])

ax.text(0.9, 0.95, "reference prior for unif($\\theta$,$\\theta^2$)", \
        horizontalalignment='right', \
        verticalalignment='top', \
        fontsize=18, color='black', \
        transform=ax.transAxes)

plt.savefig("refprior.pdf")
           
          
         
        
       
      
     
    
