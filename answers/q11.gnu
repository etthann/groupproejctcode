#Graph Settings
set terminal png enhanced size 1000, 800
set output 'gnuplot/q11.png'
set title 'Average Land and Ocean Temperatures (1850-2015)'
set xlabel 'Year'
set ylabel 'Temperature (Celsius)'
set xtics 25
set grid

# Plot the data from the file with different line types and a legend
plot 'q11.txt' using 1:($1>=1850 ? $2 : 1/0) title 'Land Average Temperature' with linespoints, \
     'q11.txt' using 1:($1>=1850 ? $3 : 1/0) title 'Land and Ocean Average Temperature' with linespoints