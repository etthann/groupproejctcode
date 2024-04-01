# Set terminal and output file
set terminal png enhanced size 1000, 800
set output 'gnuplot/q8.png'

# Set title and labels
set title "Yearly Average Temperatures From 1850-2015"
set xlabel "Years"
set ylabel "Temperatures"

set xtics 20

# Plot the data with different colors for different lines
plot 'q8.txt' using ($1 >= 1850 && $1 < 2015 ? $1 : 1/0):2 title "Land Average" with lines lw 2 lc rgb 'blue' , \
     'q8.txt' using ($1 >= 1850 && $1 <= 2015 ? $1 : 1/0):3 with lines lw 2 lc rgb 'red' title "Land Max", \
     'q8.txt' using ($1 >= 1850 && $1 < 2015 ? $1 : 1/0):4 with lines lw 2 lc rgb 'green' title "Land Minimum"