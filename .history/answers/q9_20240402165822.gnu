# Set the terminal type to PNG and enhance the quality. Set the size of the output image to 1000x800 pixels.
set terminal png enhanced size 1000, 800

# Set the output file name to 'gnuplot/q9.png'.
set output 'gnuplot/q9.png'

# Enable multiplot mode, which allows multiple plots on the same image. Set the layout to 3 rows and 1 column.
set multiplot layout 3,1

# Set the title of the first plot to 'Land Minimum', and the labels for the x-axis and y-axis.
set title "Land Minimum"
set xlabel 'Year'
set ylabel 'Temperature (Celsius)'
set xtics 20

# Plot the data from the file 'q8.txt' for the 'Land Minimum' plot. The data is plotted with boxes, and different line colors are used for different centuries.
plot 'q8.txt' using ($1 >= 1850 && $1 < 1900 ? $1 : 1/0):4 with boxes lc 1 title "Land Minimum 19th century", \
     'q8.txt' using ($1 >= 1900 && $1 < 2000 ? $1 : 1/0):4 with boxes lc 2 title "Land Minimum 20th century", \
     'q8.txt' using ($1 >= 2000 && $1 <= 2015 ? $1 : 1/0):4 with boxes lc 3 title "Land Minimum 21st Century"

# Set the title of the second plot to 'Land Maximum', and the labels for the x-axis and y-axis.
set title "Land Maximum"
set xlabel 'Year'
set ylabel 'Temperature (Celsius)'
set xtics 20

# Plot the data from the file 'q8.txt' for the 'Land Maximum' plot. The data is plotted with boxes, and different line colors are used for different centuries.
plot 'q8.txt' using ($1 >= 1850 && $1 < 1900 ? $1 : 1/0):3 with boxes lc 1 title "Land Maximum 19th century", \
     'q8.txt' using ($1 >= 1900 && $1 < 2000 ? $1 : 1/0):3 with boxes lc 2 title "Land Maximum 20th century", \
     'q8.txt' using ($1 >= 2000 && $1 <= 2015 ? $1 : 1/0):3 with boxes lc 3 title "Land Maximum 21st Century"

# Set the title of the third plot to 'Land Average', and the labels for the x-axis and y-axis.
set title "Land Average"
set xlabel 'Year'
set ylabel 'Temperature (Celsius)'
set xtics 20

# Plot the data from the file 'q8.txt' for the 'Land Average' plot. The data is plotted with boxes, and different line colors are used for different centuries.
plot 'q8.txt' using ($1 >= 1850 && $1 < 1900 ? $1 : 1/0):2 with boxes lc 1 title "Land Average 19th century", \
     'q8.txt' using ($1 >= 1900 && $1 < 2000 ? $1 : 1/0):2 with boxes lc 2 title "Land Average 20th century", \
     'q8.txt' using ($1 >= 2000 && $1 <= 2015 ? $1 : 1/0):2 with boxes lc 3 title "Land Average 21st Century"

# End multiplot mode.
unset multiplot