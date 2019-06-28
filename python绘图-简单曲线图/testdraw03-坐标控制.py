import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-2*np.pi, 2*np.pi, 0.02)
y = np.sin(x)

# 坐标设置
plt.axis([-10, 10, -2, 2])
# x坐标的间隔
plt.xticks([i*np.pi/2 for i in range(-4, 5)],
           [str(i*0.5)+"$\pi$" for i in range(-4, 5)])
# y坐标的间隔
plt.yticks([i*0.5 for i in range(-4, 5)])
# x坐标的标记
plt.xlabel("x")
# y坐标的标记
plt.ylabel("y")
plt.plot(x, y, color="k", linestyle="-", linewidth=1)
plt.show()
