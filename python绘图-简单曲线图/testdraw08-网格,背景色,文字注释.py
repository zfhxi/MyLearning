import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-1, 1, 0.1)
y = [2*i for i in x]

# 背景色设置，一定要再plot前，否则覆盖
plt.subplot(facecolor='y')
plt.plot(x, y, color='r', linestyle='-', marker='^', linewidth=1)

# 任意位置添加文字注释
plt.text(-0.5,-0.5,"y=2x",fontsize=10,color='r')
# 为某一个点添加注释
# 'A'-注释文本，xy-注释的点的坐标，xytext-注释文本的起始坐标
# arrowprops-箭头, headwidth-箭头宽度，width-箭身的宽度
plt.annotate('A',xy=(0,0),xytext=(-0.3,-0.3),arrowprops=dict(facecolor='k',headwidth=10,width=2))

# 显示网格，axis属性有x, y, both(默认)
plt.grid(axis='y',color='k', linestyle=':')
plt.show()