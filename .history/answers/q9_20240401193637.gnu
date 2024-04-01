# Set terminal and output file
set terminal png enhanced size 1000, 800
set output 'gnuplot/q9.png'

# Set title
set title "Land Minimum"
set xlabel 'Year'
set ylabel 'Temperature (Celcius)'

set xtics 20

# Plot the data with different colors for different centuries
plot 'q8.txt' using ($1 >= 1850 && $1 < 1900 ? $1 : 1/0):3 with boxes lc 1 title "Land Minimum 19th century", \
     'q8.txt' using ($1 >= 1900 && $1 < 2000 ? $1 : 1/0):3 with boxes lc 2 title "Land Minimum 20th century", \
     'q8.txt' using ($1 >= 2000 && $1 <= 2015 ? $1 : 1/0):3 with boxes lc rgb 'green' title "Land Minimum 21st Century"