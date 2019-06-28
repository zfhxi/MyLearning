import matplotlib.pylab as plt

x = [1, 2, 3, 4]
y = [1.2, 2.5, 4.5, 7.3]

# 设定线条样式，颜色洋红，标记点为x号，线条风格虚线，宽度为4
plt.plot(x, y, color='m', marker='x', linestyle=':', linewidth=4)
# 保存图片，设定分辨率8x120=960
plt.savefig("D:\折线.png", dpi=120)
# 显示图片
plt.show()
