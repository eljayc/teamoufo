from matplotlib import pyplot as plt
import numpy as np
from scipy import interpolate

# coordinates
x = np.array([10, 15, 17, 9, 20])
y = np.array([5, 16, 7, 12, 8])

# s=0 to pass through all points; per=F for open loop
path, u = interpolate.splprep([x, y], s = 0, per = False)

# fits for 100 evenly-spaced distance values
xi, yi = interpolate.splev(np.linspace(0, 1, 100), path)

# plot
fig, ax = plt.subplots(1, 1)
ax.plot(x, y, 'ob')
ax.plot(xi, yi, '-g')
plt.show()
