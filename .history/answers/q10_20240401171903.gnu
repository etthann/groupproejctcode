set terminal png enhanced size 1000, 800
set output 'output.png'
set title "Average Land Temperature by Month (2000-2015)"
set xlabel "Month"
set ylabel "Temperature (Celsius)"
set xrange [1:12]
plot 'data.txt' using 1:2:3 with yerrorbars title "Average Temperature"