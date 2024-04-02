# Set the terminal type to PNG and enhance the quality. Set the size of the output image to 1000x800 pixels.
set terminal png enhanced size 1000, 800

# Set the output file name to 'gnuplot/q8.png'.
set output 'gnuplot/q8.png'

# Set the title of the graph to 'Yearly Average Temperatures From 1850-2015'.
set title "Yearly Average Temperatures From 1850-2015"

# Set the label for the x-axis to 'Years'.
set xlabel "Years"

# Set the label for the y-axis to 'Temperatures (Celsius)'.
set ylabel "Temperatures (Celsius)"

# Set the interval for the x-axis ticks to 20.
set xtics 20

# Plot the data from the file 'q8.txt'. The 'using ($1 >= 1850 && $1 < 2015 ? $1 : 1/0):2' part means that column 1 is used for the x-values, and column 2 is used for the y-values if the value in column 1 is between 1850 and 2015. If the value in column 1 is outside this range, '1/0' (which represents an undefined value in Gnuplot) is used for the y-value. The title for this data set in the legend is 'Land Average Temperature'. The 'with lines lw 3 lc 1' part means that the data is plotted with lines, the line width is set to 3, and the line color is set to 1. The same is done for 'Land Max Temperature' and 'Land Minimum Temperature' but using columns 3 and 4 for the y-values, respectively.
plot 'q8.txt' using ($1 >= 1850 && $1 < 2015 ? $1 : 1/0):2 title "Land Average Temperature" with lines lw 3 lc 1, \
     'q8.txt' using ($1 >= 1850 && $1 <= 2015 ? $1 : 1/0):3 title "Land Max Temperature" with lines lw 3 lc 2, \
     'q8.txt' using ($1 >= 1850 && $1 < 2015 ? $1 : 1/0):4 title "Land Minimum Temperature" with lines lw 3 lc 3