# Set the terminal type to PNG and enhance the quality. Set the size of the output image to 1000x800 pixels.
set terminal png enhanced size 1000, 800

# Set the output file name to 'gnuplot/q11.png'.
set output 'gnuplot/q11.png'

# Set the title of the graph to 'Average Land and Ocean Temperatures (1850-2015)'.
set title 'Average Land and Ocean Temperatures (1850-2015)'

# Set the label for the x-axis to 'Year'.
set xlabel 'Year'

# Set the label for the y-axis to 'Temperature (Celsius)'.
set ylabel 'Temperature (Celsius)'

# Set the interval for the x-axis ticks to 25.
set xtics 25

# Enable the grid.
set grid

# Plot the data from the file 'q11.txt'. The 'using 1:($1>=1850 ? $2 : 1/0)' part means that column 1 is used for the x-values, and column 2 is used for the y-values if the value in column 1 is greater than or equal to 1850. If the value in column 1 is less than 1850, '1/0' (which represents an undefined value in Gnuplot) is used for the y-value. The title for this data set in the legend is 'Land Average Temperature'. The 'with linespoints' part means that the data is plotted with both lines and points. The same is done for the 'Land and Ocean Average Temperature' but using column 3 for the y-values.
plot 'q11.txt' using 1:($1>=1850 ? $2 : 1/0) title 'Land Average Temperature' with linespoints, \
     'q11.txt' using 1:($1>=1850 ? $3 : 1/0) title 'Land and Ocean Average Temperature' with linespoints