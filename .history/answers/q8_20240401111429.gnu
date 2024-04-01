set terminal png enhanced size 1000, 800
set output 'gnuplot/q8.png'
set title "Yearly Average, Max, and Min Land Temperatures from 1850 to 2015"
set xlabel "Year"
set ylabel "Temperature (Celsius)"
plot 'q8.txt' using 1:2 with lines lw 2 lc rgb 'blue' title "Average", \
     'q8.txt' using 1:3 with lines lw 1 lc rgb 'red' title "Max", \
     'q8.txt' using 1:4 with lines lw 1 lc rgb 'green' title "Min"