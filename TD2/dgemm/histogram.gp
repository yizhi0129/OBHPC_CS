set title "dgemm n = 100, r = 210"
set term pngcairo   
set output "dgemm.png"  

set style data histograms
set style fill solid
set boxwidth 0.08

set xtics rotate by -45
set xtics ("IJK" 1, "IKJ" 2, "IEX" 3, "UNROLL4 " 4, "UNROLL8 " 5, "CBLAS" 6) 

set ytics 100
set ylabel "MiB/s"
set key top left
set key horizontal

set offset 0.2, 0, 0

plot 'dgemm_clang_O0.txt' using ($0):14 with boxes title "clang -O0" linecolor rgb "blue", \
     'dgemm_gcc_O0.txt' using ($0+0.08):14 with boxes title "gcc -O0" linecolor rgb "brown", \
     'dgemm_clang_O1.txt' using ($0+0.16):14 with boxes title "clang -O1" linecolor rgb "green", \
     'dgemm_gcc_O1.txt' using ($0+0.24):14 with boxes title "gcc -O1" linecolor rgb "orange", \
     'dgemm_clang_O2.txt' using ($0+0.32):14 with boxes title "clang -O2" linecolor rgb "cyan", \
     'dgemm_gcc_O2.txt' using ($0+0.4):14 with boxes title "gcc -O2" linecolor rgb "yellow", \
     'dgemm_clang_o3.txt' using ($0+0.48):14 with boxes title "clang -O3" linecolor rgb "purple", \
     'dgemm_gcc_o3.txt' using ($0+0.56):14 with boxes title "gcc -O3" linecolor rgb "red", \
     'dgemm_clang_Ofast.txt' using ($0+0.64):14 with boxes title "clang -Ofast" linecolor rgb "gray", \
     'dgemm_gcc_Ofast.txt' using ($0+0.72):14 with boxes title "gcc -Ofast" linecolor rgb "pink"