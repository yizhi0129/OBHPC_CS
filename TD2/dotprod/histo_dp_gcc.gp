set term pngcairo   # 设置输出图像格式
set output "histogram.png"  # 指定输出文件名

# 设置绘图样式为柱状图
set style data histograms
set style fill solid
set boxwidth 0.2  # 设置柱子的宽度

# 设置 X 轴标签和范围
set xtics rotate by -45
set xtics ("O0" 1, "O1" 2, "O2" 3, "O3" 4, "Ofast" 5)

# 设置 Y 轴标签
set ylabel "MiB/s"

# 绘制多个数据文件
plot 'dotprod_gcc_O0.txt' using 12:xtic(1) with boxes title "O0", \
     'dotprod_gcc_O1.txt' using ($0+0.1):12:xtic(2) with boxes title "O1", \
     'dotprod_gcc_O2.txt' using ($0+0.2):12:xtic(3) with boxes title "O2", \
     'dotprod_gcc_O3.txt' using ($0+0.3):12:xtic(4) with boxes title "O3", \
     'dotprod_gcc_Ofast.txt' using ($0+0.4):12:xtic(5) with boxes title "Ofast"
