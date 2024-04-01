# Set terminal and output file
set terminal png enhanced size 1000, 800
set output 'gnuplot/q7.png'

# Set title and labels
set title "Yearly Average Temperatures Between 19th and 20th Centuries"
set xlabel "Years"
set ylabel "Temperatures (Celcius)"

# Plot the data with different colors for different centuries
plot 'q1.txt' using ($1 >= 1800 && $1 < 1900 ? $1 : 1/0):2 title "19th Century" with lines lw 2 lc rgb 'blue' , \
     'q1.txt' using ($1 >= 1900 && $1 <= 2000 ? $1 : 1/0):2 with lines lw 2 lc rgb 'red'    