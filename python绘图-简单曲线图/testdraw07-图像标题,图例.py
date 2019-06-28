import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-1, 1, 0.1)

y1 = np.exp(x)
y2 = np.exp(2*x)

# label为图例中的标记名称
plt.plot(x, y1, color='r', linestyle='-', marker='^', linewidth=1, label="y1")
plt.plot(x, y2, color='b', linestyle='-', marker='s', linewidth=1, label="y2")

# loc表示位置
# loc属性有：'best', 'upper right', 'upper left', 'lower left', 'lower right', 'right', 'center left', 'center right', 'lower center', 'upper center', 'center'
plt.legend(loc='upper left', bbox_to_anchor=(0.2, 0.95))
# 图标题
plt.title('figure 1')
plt.show()
