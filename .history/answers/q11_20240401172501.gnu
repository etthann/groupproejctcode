#Graph Settings
set terminal png enhanced size 1000, 800
set output 'gnuplot/q11.png'
set title 'Average Land and Ocean Temperatures (1850-2015)'
set xlabel 'Year'
set ylabel 'Temperature (Celsius)'
set xtics 25
set grid

# Plot the data from the file with different line types and a legend
plot 'q6.txt' using 1:2 title 'Land Average Temperature' with linespoints, \
     'data.txt' using 1:3 title 'Land and Ocean Average Temperature' with linespoints