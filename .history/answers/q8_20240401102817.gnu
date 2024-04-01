set terminal png enhanced size 1000, 800
set output 'output.png'
set title "Yearly Average, Max, and Min Land Temperatures from 1850 to 2015"
set xlabel "Year"
set ylabel "Temperature (Celsius)"
plot 'q8.txt' using 1:2 with lines lw 2 lc rgb 'blue' title "Average", \
     'data.txt' using 1:3 with lines lw 1 lc rgb 'red' title "Max", \
     'data.txt' using 1:4 with lines lw 1 lc rgb 'green' title "Min"