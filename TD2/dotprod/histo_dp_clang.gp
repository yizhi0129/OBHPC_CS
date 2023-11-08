set title "dotprod clang n = 50, r = 120"
set term pngcairo   
set output "dotprod_clang.png"  

set style data histograms
set style fill solid
set boxwidth 0.1

set xtics rotate by -45
set xtics ("BASE" 1, "UNROLL4 " 2, "UNROLL8 " 3, "CBLAS" 4) 

set ytics 4000
set ylabel "MiB/s"

set offset 0.2, 0, 0

plot 'dotprod_clang_O0.txt' using ($0):15 with boxes title "O0", \
     'dotprod_clang_O1.txt' using ($0+0.1):15 with boxes title "O1", \
     'dotprod_clang_O2.txt' using ($0+0.2):15 with boxes title "O2", \
     'dotprod_clang_o3.txt' using ($0+0.3):15 with boxes title "O3", \
     'dotprod_clang_Ofast.txt' using ($0+0.4):15 with boxes title "Ofast"