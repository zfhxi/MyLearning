import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-5, 5, 0.02)
y = np.sin(x)

# 坐标控制，x为[-pi,pi]，y为[-2,2]，即plt.axis([x_min, x_max, y_min, y_max])
plt.axis([-np.pi, np.pi, -2, 2])
plt.plot(x, y, color='b', linestyle='-.', linewidth=1)
plt.show()