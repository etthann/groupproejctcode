# Set the terminal to PNG format
set terminal png enhanced size 1000, 800

# Set the output file name
set output 'gnuplot/q7.png'

# Set the title and labels
set title 'Yearly Average Temperatures Between 19th and 20th Centuries'
set xlabel 'Years'
set ylabel 'Temperatures (Celsius)'
set xtics 25
# Enable the grid
set grid

# Plot the data
plot 'q2.txt' using 1:2 with lines lw 2 lc rgb 'blue' title "19th Century", 'q2.txt' using 1:2 with lines lw 2 lc rgb 'red' title "20th Century"


#Graph Settings
set terminal png enhanced size 1000, 800
set output 'gnuplot/q6.png'
set title 'Average Land Temperature Each Year'
set xlabel 'Year'
set ylabel 'Temperture (Celcius)'
set xtics 25
set grid

#plots the 3 graphs from the imported files with different line types and a legend
plot 'q1.txt' using 1:2 title 'Temp' with linespoints