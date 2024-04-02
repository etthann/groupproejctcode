#Graph Settings
#set png dimension
set terminal png enhanced size 1000, 800
#output the graph into specified location
set output 'gnuplot/q6.png'
#
set title 'Average Land Temperature Each Year'
set xlabel 'Year'
set ylabel 'Temperature (Celcius)'
set xtics 25


#plots the 3 graphs from the imported files with different line types and a legend
#using column 1 as x-axis and column 2 as y-axis with linepoint graph and a legend title
plot 'q1.txt' using 1:2 title 'Temperature' with linespoints
