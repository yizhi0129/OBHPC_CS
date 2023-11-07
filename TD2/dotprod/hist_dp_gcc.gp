set term pngcairo   
set output "dotprod_gcc.png"  

set style data histograms
set style fill solid
set boxwidth 0.1

set xtics rotate by -45
set xtics ("BASE" 1, "UNROLL4 " 2, "UNROLL8 " 3, "CBLAS" 4) 

set ylabel "MiB/s"

set offset 0.2, 0, 0

plot 'dotprod_gcc_O0.txt' using ($0):12 with boxes title "O0", \
     'dotprod_gcc_O1.txt' using ($0+0.1):12 with boxes title "O1", \
     'dotprod_gcc_O2.txt' using ($0+0.2):12 with boxes title "O2", \
     'dotprod_gcc_o3.txt' using ($0+0.3):12 with boxes title "O3", \
     'dotprod_gcc_Ofast.txt' using ($0+0.4):12 with boxes title "Ofast"