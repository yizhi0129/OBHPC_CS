set title "reduc gcc n = 40000, r = 2000"
set term pngcairo   
set output "reduc_gcc_L3.png"  

set style data histograms
set style fill solid
set boxwidth 0.1

set xtics rotate by -45
set xtics ("BASE" 1, "UNROLL4 " 2, "UNROLL8 " 3, "CBLAS" 4) 

set ytics 4000
set ylabel "MiB/s"

set key top left

set offset 0.2, 0, 0

plot 'gcc_O0_L3.txt' using ($0):15 with boxes title "O0", \
     'gcc_O1_L3.txt' using ($0+0.1):15 with boxes title "O1", \
     'gcc_O2_L3.txt' using ($0+0.2):15 with boxes title "O2", \
     'gcc_O3_L3.txt' using ($0+0.3):15 with boxes title "O3", \
     'gcc_Ofast_L3.txt' using ($0+0.4):15 with boxes title "Ofast"