# Set the terminal to PNG format
set terminal png enhanced size 1000, 800

# Set the output file name
set output 'gnuplot/.png'

# Set the title and labels
set title 'Average Land Temperature Each Year from 1852 to 1952'
set xlabel 'Year'
set ylabel 'Temperature (Celsius)'

# Set the x-axis tics
set xtics 10

# Enable the grid
set grid

# Plot the data
plot 'q2.txt' using 1:2 title '19th Century' with linespoints lt rgb "blue", \
     'q2.txt' using 1:3 title '20th Century' with linespoints lt rgb "red"