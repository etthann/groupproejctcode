#Graph Settings
set terminal png enhanced size 1000, 800
set output 'gnuplot/q11.png'
set title 'Average Land Temperature Each Year'
set xlabel 'Year'
set ylabel 'Temperture (Celcius)'
set xtics 25
set grid

#plots the 3 graphs from the imported files with different line types and a legend
plot 'q11.txt' using 1:2 title 'Temp' with linespoints