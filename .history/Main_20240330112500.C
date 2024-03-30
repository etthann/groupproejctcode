// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Declare global variables, these variables are to read the CSV data
FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";

//Globally Declare the getTotalRow function
int getTotalRow(int *columns);


//Main funtion
int main() {
    //Declare and Initialize the values of the amount of rows and columns the CSV data has
    int columns;
    int rows = getTotalRow(&columns); //Pass the columns address to the getTotalRow function
    
    return 0;
}

/**
 * Function that returns the number of columns and rows in the CSV file
 * 
 * @param columns - Pointer for the columns variable that allows us to modify the column value
 * @return It returns the type int and the variable line as that variable holds the value of the  
 * 
*/
int getTotalRow (int *columns) {
    file = fopen(fileName,"r");

    if (file == NULL) {
        printf("Failed to open %d",fileName);
        return -1;
    }

    int line = 1;
    char c;
    *columns = 1;
    bool firstLine = true;

    do {
        c = fgetc(file);
        if (firstLine && c == ',')
            (*columns)++;    
        if (c== '\n') {
            line++;
            firstLine = false; // Stop counting columns after the first line
        }
    } while (c != EOF);

    fclose(file);
    printf("The number of columns: %d\nThe number of rows:  %d",*columns,line);
    return line;
}

