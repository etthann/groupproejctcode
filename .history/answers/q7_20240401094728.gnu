set terminal png enhanced size 1000, 800
set output 'gnuplot/q7.png'
set title "Yearly Average Temperatures Between 19th and 20th Centuries"
set xlabel "Years since start of century"
set ylabel "Temperatures"
set xrange [0:100]  # This ensures that the x-axis scale is the same for both centuries
plot 'q2_19th.txt' using ($1-1800):2 with lines lw 2 lc rgb 'blue' title "19th Century", \
     'q2_20th.txt' using ($1-1900):2 with lines lw 2 lc rgb 'red' title "20th Century"