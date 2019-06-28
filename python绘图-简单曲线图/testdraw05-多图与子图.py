import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-1, 1, 0.1)

y1 = np.exp(x)
y2 = np.exp(2*x)
y3 = np.exp(1.5*x)

#生成第一个图fig.1,并且处理fig.1
plt.figure(1)
# fig.1为一行两列布局，现在画第一个子图
plt.subplot(1, 2, 1)
plt.plot(x, y1, color='r', linestyle='-', marker='^', linewidth=1)

plt.xlabel('x')
plt.ylabel('y1')

#生成第二个图，并且处理fig.2
plt.figure(2)
plt.plot(x, y2, color='k', linestyle='-', marker='s', linewidth=1)
plt.xlabel('x')
plt.ylabel('y2')

#处理fig.1
plt.figure(1)
# 现在画第二个子图
plt.subplot(1, 2, 2)
plt.plot(x, y3, color='b', linestyle='-', marker='v', linewidth=1)

plt.xlabel('x')
plt.ylabel('y3')

plt.show()
