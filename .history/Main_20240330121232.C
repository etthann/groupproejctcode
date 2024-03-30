// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Declare global variables, these variables are to read the CSV data
FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";

//Globally Declare the getTotalRow function
int getTotalRow(int *columns);

#define MAX_ROWS 4000
#define MAX_COLS 20

//Main funtion
int main() {
    //Declare and Initialize the values of the amount of rows and columns the CSV data has
    int columns;
    const int rows = getTotalRow(&columns); //Pass the columns address to the getTotalRow function
    char data[MAX_ROWS][MAX_COLS];
    
    storeCSVData(&data);

    return 0;
}

void storeCSVData (char (*data)) {
    file = fopen(fileName,"r");
    
}

/**
 * Function that returns the number of columns and rows in the CSV file
 * 
 * @param columns - Pointer for the columns variable that allows us to modify the column value
 * @return It returns the type int and the variable line as that variable holds the value of the number of rows in the CSV file 
 * 
*/
int getTotalRow (int *columns) {
    // Open and read from the file, fileName
    file = fopen(fileName,"r");

    //If file returns null prompt the user that they could not open the CSV file and stops the function from running by returning -1
    if (file == NULL) {
        printf("Failed to open %d",fileName);
        return -1;
    }

    //Declare variables
    int line = 1;
    char c;
    *columns = 1;
    bool firstLine = true;

    //Use a do while loops to find the number of rows and columns in the csv file
    do {
        //Get all the values in the file
        c = fgetc(file);

        //If it's the first line and the value of c is a comma , then add 1 to the columns pointer
        if (firstLine && c == ',')
            (*columns)++;    
        //If c is equal to a new line \n then add one to the line variable and set the boolean firstLine to false as it's no longer the first line in the CSV anymore
        if (c== '\n') {
            line++;
            firstLine = false; // Stop counting columns after the first line
        }
    } while (c != EOF); // Continue running until c reaches the end of the file

    // Close the file read
    fclose(file);

    //Print out the number of columns and rows
    printf("The number of columns: %d\nThe number of rows:  %d",*columns,line);

    //Return the number of rows
    return line;
}

