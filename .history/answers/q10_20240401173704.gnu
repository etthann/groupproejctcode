set terminal png enhanced size 1000, 800
set output 'gnuplot/q10.png'
set title "Average Land Temperature by Month (2000-2015)"
set xlabel "Month"
set ylabel "Temperature (Celsius)"
set xrange [1:12]
plot 'q10.txt' using 1:2:4 with yerrorbars title "Average Temperature"