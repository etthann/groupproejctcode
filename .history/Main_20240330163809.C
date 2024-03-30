// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


// Declare global variables, these variables are to read the CSV data
FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";


// Define max size of 2D array
#define MAX_ROWS 4000
#define MAX_COLS 20
#define MAX_LENGTH 100


// Globally Declare the getTotalRow function
int getTotalRowAndColumn(int *columns);
void storeCSVData(char*** data, int rows, int cols);
float averageLandTemperature(char*** data, int rows, int cols);

// Main funtion
int main() {
    //Declare and Initialize the values of the amount of rows and columns the CSV data has
    int columns;
    int rows = getTotalRowAndColumn(&columns); //Pass the columns address to the getTotalRow function
    
    // Dynamically allocate storage to the 3D array as when you try to set it statically, the program will crash and not run
    // Declares a pointer to a pointer to a pointer to a char, there are three astrisks which corresponds to the 3 dimensions in the array
    // malloc(rows*sizeof(char**)) allocates memory to the first dimension which contains rows(3194) number of rows
    // malloc is used to pass the size of the memory you want to allocate in bytes so while the program runs, it can allocate a certain amount of memory as if we try to allocate too much memory 
    // statically then the program will crash
    char*** data = (char***)malloc(rows * sizeof(char**)); 
    for (int i = 0; i < rows; i++) {
        // For each column it will allocate memory which has column number of char* pointers
        data[i] = (char**)malloc(MAX_COLS * sizeof(char*));
        for (int j = 0; j < MAX_COLS; j++) {
            //Nested for loop that will allocate memory towards the third dimension of the array which will contain MAX_LENGTH number of char values
            data[i][j] = (char*)malloc(MAX_LENGTH * sizeof(char));
        }
    }

    //Store the CSV data into the 3D data array
    storeCSVData(data, rows, columns);

    //Print out the values in the 3D array
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            printf("%s ", data[r][c]); // Print each string in the array
        }
        printf("\n"); // Print a newline after each row
    }


    //Add new functions below here
    printf("The average land temperature is %f",averageLandTemperature(data,rows,columns));



    // Free up the allocated memory when done using the free function
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            free(data[i][j]); //Free up the allocated memory for each element in the second and third dimension
        }
        free(data[i]); // Free up the memory in the rows
    }
    free(data);

    return 0;
}


/**
 * Store the CSV data into a 3D array, where the row is the line number, col is the string element, z is the string value eg. data[-1][-1][0] = 1999-11-01
 * @param data - 3D array pointer so you can change the data inside this function
 * @param rows - The number of rows in the CSV file
 * @param cols - The number of cols in the CSV file
*/
void storeCSVData(char*** data, int rows, int cols) {
    // Open and read the file fileName
    file = fopen(fileName,"r");
    
    //If file is NULL then print that the file can't open
    if (file == NULL) {
        printf("Failed to open %s", fileName);
        return;
    }

    char line[MAX_LENGTH];
    int row = 0;

    // When the file reaches the end, then fgets returns null and if we reached the end of the file which is rows length
    while (fgets(line, MAX_LENGTH, file) != NULL && row < rows) {
        line[strcspn(line, "\n")] = 0; // Remove the newline character
        // Intialize tokenCount to 0 to keep track of the number of words in the current line
        int col = 0;
        // Set our delimiter, which in this case is a comma as we're using a CSV file
        char* token = strtok(line, ",");
        
        //While the token value is not NULL and we haven't reached the last column
        while (token != NULL && col < cols) {
            // Copies the value of token and stores it into data array
            strcpy(data[row][col], token);
            data[row][col][MAX_LENGTH-1] = '\0';
            // Gets the next values 
            token = strtok(NULL, ",");
            // Increments so that the next data will be stored in the next column of the 2D data array
            col++;
        }
        // Increments so the next line will be stored in the next row
        row++;
    }

    // Closes the file that was opened
    fclose(file);

}


/**
 * Function that returns the number of columns and rows in the CSV file
 * @param columns - Pointer for the columns variable that allows us to modify the column value
 * @return It returns the type int and the variable line as that variable holds the value of the number of rows in the CSV file 
 * 
*/
int getTotalRowAndColumn (int *columns) {
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


/**
 * Function that calculates the average land temp per each year
 * @param data - pointer to the data
 * @param row - number of rows in 2d array
 * @param col - number of columns in 2d array
 * @return the average land temperature
 * 
*/
float averageLandTemperature(char*** data, int row, int col) {

    for (int r = 0; r < row; r++) {
        char* date = data[r][0];
        char *token = strtok(date, "-");
        int year = atoi(token);
        if (year >= 1760 && year <=2015 && year == atoi(strtok(data[r][0],"-"))) {
            counter++;
        }
    }

    return averageLandTemp;
}
