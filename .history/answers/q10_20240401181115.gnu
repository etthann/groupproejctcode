
#Graph Settings
set terminal png enhanced size 600,600
set output 'gnuplot/q10.png'
set title 'Average Land Temperature by Month'
set xlabel 'Year'
set ylabel 'Temperature'
set xtics 1
set yrange [0:20]
set boxwidth 0.5


#plots temperatures with error bars
plot 'q10.txt' using 1:2:3  title 'Average Land Temp' with errorbars