import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-1, 1, 0.1)
y1 = np.exp(x)
y2 = np.exp(2*x)

# 分别画出不同的风格图
plt.plot(x, y1, color='r', linestyle='-', marker='^', linewidth=1)
plt.plot(x, y2, color='b', linestyle='-', marker='s', linewidth=1)

plt.xlabel('x')
plt.ylabel('y')
plt.show()