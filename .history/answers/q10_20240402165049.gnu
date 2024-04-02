# Set the terminal type to PNG and enhance the quality. Set the size of the output image to 600x600 pixels.
set terminal png enhanced size 600,600

# Set the output file name to 'gnuplot/q10.png'.
set output 'gnuplot/q10.png'

# Set the title of the graph to 'Average Land Temperature by Month'.
set title 'Average Land Temperature by Month'

# Set the label for the x-axis to 'Year'.
set xlabel 'Year'

# Set the label for the y-axis to 'Temperature'.
set ylabel 'Temperature'

# Set the interval for the x-axis ticks to 1.
set xtics 1

# Set the range for the y-axis from 0 to 20.
set yrange [0:20]

# Set the width of the boxes used in boxplots to 0.5.
set boxwidth 0.5

# Plot the data from the file 'q10.txt'. The 'using 1:2:3' part means that columns 1, 2 and 3 are used for the x-values, y-values, and error bar sizes, respectively. The title for this data set in the legend is 'Average Land Temp'. The 'with errorbars' part means that error bars are added to the plot.
plot 'q10.txt' using 1:2:3  title 'Average Land Temp' with errorbars