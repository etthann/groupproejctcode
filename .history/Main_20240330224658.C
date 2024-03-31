// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


// Declare global variables, these variables are to read the CSV data
FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";
int listHottestColdest[2][2];


// Define max size of 2D array
#define MAX_ROWS 4000
#define MAX_COLS 20
#define MAX_LENGTH 1000


// Globally Declare the getTotalRow function
int getTotalRowAndColumn(int *columns);
void storeCSVData(char*** data, int rows, int cols);
float averageLandTemperatureEachYear(char*** data, int rows, int cols, int targetYear);
void storeAnswerToFile(char*** data, int rows, int columns, const char* fileName, int startYear, int endYear);
float averageLandTemperatureEachCentury(char*** data, int rows, int cols, int startYear, int endYear);
float averageLandTemperatureEachMonth(char*** data, int rows, int columns, int targetMonth);

// Main funtion
int main() {

    //Declare and Initialize the values of the amount of rows and columns the CSV data has
    int columns;
    int rows = getTotalRowAndColumn(&columns); //Pass the columns address to the getTotalRow function
    
    /*Dynamically allocate storage to the 3D array as when you try to set it statically, the program will crash and not run
    Declares a pointer to a pointer to a pointer to a char, there are three astrisks which corresponds to the 3 dimensions in the array
    malloc(rows*sizeof(char**)) allocates memory to the first dimension which contains rows(3194) number of rows
    malloc is used to pass the size of the memory you want to allocate in bytes so while the program runs, it can allocate a certain amount of memory as if we try to allocate too much memory 
    statically then the program will crash*/

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
    // Question 1:
    printf("The average land temperature is %f",averageLandTemperatureEachYear(data,rows,columns,1760));
    storeAnswerToFile(data, rows, columns,"q1", 1760, 2015);


    //Question 2:
    storeAnswerToFile(data,rows,columns,"q2",1760,1799);
    storeAnswerToFile(data,rows,columns,"q2",1800,1899);
    storeAnswerToFile(data,rows,columns,"q2",1900,1999);
    storeAnswerToFile(data,rows,columns,"q2",2000,2015);


    // Question 3:
    storeAnswerToFile(data,rows,columns,"q3",1,1);


    // Question 4
    storeAnswerToFile(data,rows,columns,"q4",1,1);


    // Question 5


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

/*  The code below is for question 1 */

/**
 * This function is used to answer question 1
 * Function that calculates the average land temp per each year
 * @param data - pointer to the data
 * @param row - number of rows in 2d array
 * @param col - number of columns in 2d array
 * @param targetYear - 
 * @return the average land temperature
*/
float averageLandTemperatureEachYear(char*** data, int row, int col, int targetYear) {
    // Declare variables
    int counter = 0;
    float totalTemp = 0.0;
    float averageLandTemp = 0.0;

    // Go through the entire data array
    for (int r = 0; r < row; r++) {
        // Get the date from the data array
        char* date = data[r][0];

        //Get the first value that is seperated by the "-" delimeter
        char *token = strtok(date, "-");
        //Chagne the token value to an integer and store it's value into the year variable
        int year = atoi(token);
        // If the year is equal to the year we want to find
        if (year == targetYear) {
            // Set the monthly temp to 0 and monthCount to 0 as well
            float monthlyTemp = 0.0;
            int monthCount = 0;
            //Use a for loop to turn the temp into a for loop
            for (int c = 1; c < col; c++) {
                // Change the temperature from the 3D data array into a float and store it into the temp variable
                float temp = atof(data[r][1]);
                
                //If the temperature is not 0
                if (temp != 0.0) { 
                    monthlyTemp += temp; //Add the temp to the monthlyTemp
                    monthCount++; //Add one to the total month count
                }
            }

            //If the monthCount is greater than 0
            if (monthCount > 0) {
                //Calculate the total temp
                totalTemp += monthlyTemp / monthCount;
                //Add 1 to the counter
                counter++;
            }
        }
    }
    //If counter is greater than 0 then calculate the average temp, if not then averageLandTemp is 0
    averageLandTemp = (counter > 0) ? totalTemp / counter : 0;
    
    //Returns the averageLandTemp variable which holds the average temp of that year
    return averageLandTemp;
}


// Code Below is Question 2

float averageLandTemperatureEachCentury(char*** data, int rows, int columns, int startYear, int endYear) {
    int counter = 0;
    float totalTemp = 0.0;
    float averageLandTemp = 0.0;

    for (int r = 0; r < rows; r++) {
        char* date = data[r][0];
        char *token = strtok(date, "-");
        int year = atoi(token);
        if (year >= startYear && year <= endYear) {
            float yearlyTemp = averageLandTemperatureEachYear(data, rows, columns, year);
            if (yearlyTemp != 0.0) {
                totalTemp += yearlyTemp;
                counter++;
            }
        }
    }
    averageLandTemp = (counter > 0) ? totalTemp / counter : 0; 
    return averageLandTemp;
}



/**
 * This function is used to answer question 3
 * Function that calculates the average land temperature each month
 * @param data - pointer to the data
 * @param row - number of rows in 2d array
 * @param col - number of columns in 2d array
 * @param targetmonth - the month calculations
 * @return the average land temperature for each month
 * 
*/
float averageLandTemperatureEachMonth(char*** data, int rows, int columns, int targetMonth) {
    float totalTemp = 0.0;
    int count = 0;

    for (int r = 0; r < rows; r++) {
        char* date = data[r][0];
        char *token = strtok(date, "-");
        int month = atoi(token + 5);
        if (month == targetMonth) {
            for (int c = 1; c < columns; c++) {
                float temp = atof(data[r][1]);
                if (temp != 0.0) {
                    totalTemp += temp;
                    count++;
                }
            }
        }
    }
    float averageTemp = (count > 0) ? totalTemp / count : -1;
    return averageTemp;
}



// Question 4
float hottestColdestMonth(char*** data, int row, int columns, int targetYear, float* list) {

    
    float hottest = -10000, coldest = 10000, temp;
    int hottestMonth, coldestMonth;

    for (int i = 0; i < row; i++) {
        char* date = data[i][0];
        char *token = strtok(date, "-");
        int year = atoi(token); 
        
        token = strtok(date, "-");
        int month = atoi(token);
        temp = atof(data[i][1]);
            
        if (temp > list[0][1]){
            hottest = temp;
            list[0][0] = targetYear;
            list[0][1] = month;
        }
        if (temp < coldest){
            coldest = temp;
            list[1][0] = targetYear;
            list[1][1] = month
        }
    }
    return ;
}



// Question 5
// >>>Based on your answer in question 1, what year was the hottest and what year was the coldest?<<<
// 
/*
float hottestColdestYear(char*** data, int rows, int columns, int targetYear) {

    
}



*/

// Quesiton 6
// code for GNUPlot of q1
/*
#Graph Settings
set terminal svg enhanced size 1000, 800
set title 'Average Land Temperature Each Year'
set xlabel 'Year'
set ylabel 'Temperture (Celcius)'
set xtics 25
set grid

#plots the 3 graphs from the imported files with different line types and a legend
plot 'q1.txt' title 'Temp' with lp lt 1 dt 1 lw 1, 

*/

//  Question 7



// Code below is to print the answers into a .txt file

/**
 * Stores the answers to a text file
 * @param
 * @param
 * @param
 * @param
 * @param
 * @param
*/
void storeAnswerToFile (char*** data, int rows, int columns, const char* fileName, int startYear, int endYear) {
    char folder [] = "answers/";
    char fullPath[100];
    strcpy(fullPath,folder);
    strcat(fullPath,fileName);
    strcat(fullPath,".txt");
    int totalYear = endYear- startYear;

    if (strcmp(fileName, "q1") == 0) {
        file = fopen(fullPath,"w");
        for (int i = 0; i < totalYear + 1; i++) {
            float averageTemp = averageLandTemperatureEachYear(data, rows, columns, startYear + i);
            fprintf(file, "%d, %f\n", startYear + i, averageTemp);
        }   

    } if (strcmp(fileName, "q2") == 0) {
        file = fopen(fullPath,"a");
        float averageTemp = averageLandTemperatureEachCentury(data,rows,columns,startYear,endYear);
        fprintf(file,"%dth Century, %f\n",startYear/100,averageTemp);

    }  if (strcmp(fileName, "q3") == 0) {
        file = fopen(fullPath,"w");
        for (int i = 1; i < 13; i++) {
            float averageTemp = averageLandTemperatureEachMonth(data, rows, columns, i);
            fprintf(file, "%d, %f\n", i, averageTemp);
        }
    } if (strcmp(fileName,"q4") == 0) {
        file = fopen(fullPath,"w");
        for (int r = 0; r < 320; r++) {
            for (int c = 0; c < 2; r++) {
                fprintf(file, "Year: %f, Coldest Month: %f, Hottest Month: %f");
            }
        }
    }


    fclose(file);
}