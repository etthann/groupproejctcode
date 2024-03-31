#Graph Settings
set terminal png enhanced size 1000, 800
set title 'Average Land Temperature Each Year'
set xlabel 'Year'
set ylabel 'Temperture (Celcius)'
set xtics 25
set grid

#plots the 3 graphs from the imported files with different line types and a legend
plot 'q1.txt' title 'Temp' with lp lt 1 dt 1 lw 1, 