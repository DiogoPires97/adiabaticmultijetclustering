import math
import numpy as np
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

Eff = []

with open('/Users/diogopires/Desktop/jets/Diogo/Results/plot_data_QBC.txt') as fobj:
    for line in fobj:
        Eff.append(line)
        print(line)

for i in range(len(Eff)):
	Eff[i] = int(Eff[i])


plt.style.use('ggplot')
plt.title('QBC \n e+e- , \u221As = 91 GeV')
plt.xlabel('Efficiency (%)')
plt.ylabel('Number of Events')	
plt.hist(Eff, bins = 10, color='b', edgecolor='black', linewidth=1)
plt.show()


############################
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
# hist, xedges, yedges = np.histogram2d(cK, qK, bins=7, range=[[0, 6], [0, 6]])

# # Construct arrays for the anchor positions of the 16 bars.
# xpos, ypos = np.meshgrid(xedges[:-1] + 0.25, yedges[:-1] + 0.25, indexing="ij")
# xpos = xpos.ravel()
# ypos = ypos.ravel()
# zpos = 0

# # Construct arrays with the dimensions for the 16 bars.
# dx = dy = 0.5 * np.ones_like(zpos)
# dz = hist.ravel()

# ax.bar3d(xpos, ypos, zpos, dx, dy, dz, zsort='average')

# plt.show()
##############################



