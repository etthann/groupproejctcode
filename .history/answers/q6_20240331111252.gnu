#Graph Settings
set terminal png enhanced size 1000, 800
load : The term 'load' is not recognized as the name of a cmdlet, function, script file, or operable program. Check the spelling of the name, or if a path was included, verify that the path is correct and try again.
set title 'Average Land Temperature Each Year'
set xlabel 'Year'
set ylabel 'Temperture (Celcius)'
set xtics 25
set grid

#plots the 3 graphs from the imported files with different line types and a legend
plot 'q1.txt' title 'Temp' with lp lt 1 dt 1 lw 1, 