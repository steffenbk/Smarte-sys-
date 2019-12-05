# -*- coding: utf-8 -*-
"""
Created on Tue Dec  3 22:48:37 2019

@author: Prolanyte
"""

from math import sin, degrees
import numpy as np

g = 9.8
u = 17
disTar = int(input("Distance to target in meters: "))
DisTra = 0
R = 0
printed = False

for i in np.arange(0.0, 1.5733, 0.01):
        R = (u**2*sin(2*i))/g
        r =  int(R)
    
        if DisTra < r:
            DisTra = r
        if r == disTar:
            if printed != True:
                print("Optimal angle: ", degrees(i))
                printed = True
        

if printed == False:
    print("Target distance too far")
    print("Maximum distance: ", DisTra)