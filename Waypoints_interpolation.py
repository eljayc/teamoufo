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


# LEE: A really good attempt, good work

# Now imagine a drone flying over these waypoints, which is limited to turning on a single cartesian plane, let's say at 1 radian per second.
# While the B-spline representation is nice, it may exceed turning limit when consecutive waypoints reach pi radians
# So we need a way to introduce a turning limit, which is a function of time

# My approach would be to define a function which travels between 3 points using the maximum turning velocity, and use it in an iterative approach for all coordinate values.

# Fastest point to point is a straight line

# Largest turn is pi radians

# If max angular velocity is 1 rad per sec, then,
# Circumference of minimum turning circle = (velocity * 2 * pi) / 1
# A full circle would be completed in (2 * pi) * 1 seconds (doesn't depend on thrust velocity)
# Radius of minimum turning circle is given by velocity / maximum angular velocity (1)

# I would first look at the shortest time between 3 points where the third point is in the same location as the first
# The shortest distance and time would be a straight line until the vehicle reaches the tangent on the minimum turning circle centred at a radius-length away from the 2nd point in the direction of half the distance between the 1nd point and the 3rd point (in this case, the same direction as 1st and 3rd are at the same location)

# I will have a try at this problem this week and see if I can can get something to work with matplotlib
