# set terminal png enhanced size 1000, 800
# set output 'gnuplot/q10.png'
# set title "Average Land Temperature by Month (2000-2015)"
# set xlabel "Month"
# set ylabel "Temperature (Celsius)"
# set xrange [1:12]
# plot 'q10.txt' using 1:2:3 with yerrorbars title "Average Temperature"




# Andy's Graph Settings
set terminal png enhanced size 600,600
set output 'gnuplot/q10.png'
set title 'Average Land Temperature by Month'
set xlabel 'Year'
set ylabel 'Temperature'
set xtics 1
set yrange [0:20]
set boxwidth 0.5
set grid


#plots temperatures with error bars
plot 'q10.txt' using 1:2:3  title 'Average Land Temp' with errorbars