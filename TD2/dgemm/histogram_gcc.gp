set title "dgemm compile gcc n = 100, r = 210"
set term pngcairo   
set output "dgemm_gcc.png"  

set style data histograms
set style fill solid
set boxwidth 0.1

set xtics rotate by -45
set xtics ("IJK" 1, "IKJ" 2, "IEX" 3, "UNROLL4 " 4, "UNROLL8 " 5, "CBLAS" 6) 

set ytics 100
set ylabel "MiB/s"
set key top left

set offset 0.2, 0, 0

plot 'dgemm_gcc_O0.txt' using ($0):14 with boxes title "O0", \
     'dgemm_gcc_O1.txt' using ($0+0.1):14 with boxes title "O1", \
     'dgemm_gcc_O2.txt' using ($0+0.2):14 with boxes title "O2", \
     'dgemm_gcc_o3.txt' using ($0+0.3):14 with boxes title "O3", \
     'dgemm_gcc_Ofast.txt' using ($0+0.4):14 with boxes title "Ofast"