# Set the terminal to PNG format
set terminal png enhanced size 1000, 800

# Set the output file name
set output 'gnuplot/q7.png'

# Set the title and labels
set title 'Yearly Average Temperatures Between 19th and 20th Centuries'
set xlabel 'Years'
set ylabel 'Temperatures (Celsius)'

# Enable the grid
set grid

# Plot the data
plot 'q2.txt' using 1:2 title 'Yearly Temperatures' with linespoints