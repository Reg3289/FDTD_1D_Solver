import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# 1. 核心修改：指定去 build 文件夹下寻找 CMake 编译跑出来的数据
file_path = 'build/fdtd_bragg_cmake_results.csv' 

print(f"正在加载数据: {file_path} ...")
try:
    data = np.loadtxt(file_path, delimiter=',')
except FileNotFoundError:
    print(f"找不到数据文件 '{file_path}'，请确保你已经在 build 目录下运行了 ./fdtd_solver！")
    exit()

time_steps, space_size = data.shape
print(f"数据加载成功！共包含 {time_steps} 张快照，空间网格大小为 {space_size}。")

# 2. 设置图表样式 (白底工程风格)
plt.style.use('default') 
fig, ax = plt.subplots(figsize=(10, 5))
x = np.arange(space_size)

line, = ax.plot(x, data[0, :], color='blue', linewidth=2)

fig.patch.set_facecolor('white')
ax.set_facecolor('white')
ax.tick_params(colors='black')
ax.spines['bottom'].set_color('black')
ax.spines['left'].set_color('black')

ax.set_ylim(-1.5, 1.5)
ax.set_xlim(0, space_size - 1)
ax.set_xlabel('Spatial Grid (mm)', color='black', fontsize=12)
ax.set_ylabel('Electric Field (Ez)', color='black', fontsize=12)

title = ax.set_title('OOP FDTD Engine - Bragg Grating', color='black', fontsize=14, fontweight='bold')

# 3. 可视化布拉格光栅区域 (100 到 220)
grating_start = 100
grating_end = 220
ax.axvspan(grating_start, grating_end, color='gray', alpha=0.1, label='Bragg Grating (n=2 / n=1.5)')
ax.legend(loc='upper right', frameon=True, edgecolor='black')

# 4. 动画更新函数
def update(frame):
    line.set_ydata(data[frame, :])
    title.set_text(f'OOP FDTD Engine - Snapshot: {frame} / {time_steps}')
    return line, title

ani = animation.FuncAnimation(fig, update, frames=time_steps, interval=50, blit=True)

print("正在渲染动画，请在弹出的窗口中查看...")
plt.show()
