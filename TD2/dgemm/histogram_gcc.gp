set term pngcairo   
set output "dgemm_gcc.png"  

set style data histograms
set style fill solid
set boxwidth 0.1

set xtics rotate by -45
set xtics ("IJK" 1, "IKJ" 2, "IEX" 3, "UNROLL4 " 4, "UNROLL8 " 5, "CBLAS" 6) 

set ylabel "MiB/s"

set offset 0.2, 0, 0

plot 'dgemm_gcc_O0.txt' using ($0):12 with boxes title "O0", \
     'dgemm_gcc_O1.txt' using ($0+0.1):12 with boxes title "O1", \
     'dgemm_gcc_O2.txt' using ($0+0.2):12 with boxes title "O2", \
     'dgemm_gcc_o3.txt' using ($0+0.3):12 with boxes title "O3", \
     'dgemm_gcc_Ofast.txt' using ($0+0.4):12 with boxes title "Ofast"