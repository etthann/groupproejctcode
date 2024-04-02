# Set terminal and output file
set terminal png enhanced size 1000, 800
# set ouput location
set output 'gnuplot/q7.png'

# Set title and labels
set title "Yearly Average Temperatures Between 19th and 20th Centuries"
set xlabel "Years"
set ylabel "Temperatures (Celcius)"

# Plot the data with different colors for different centuries
#plot using the range for columns 1 from 1800-1899 and 1900-2000 and column 2 for y values if not in range skip values, line setting width and lin
plot 'q1.txt' using ($1 >= 1800 && $1 < 1900 ? $1 : 1/0):2 title "19th Century" with lines lw 3 lc 1, \
     'q1.txt' using ($1 >= 1900 && $1 <= 2000 ? $1 : 1/0):2 title "20th Century" with lines lw 3 lc 2    