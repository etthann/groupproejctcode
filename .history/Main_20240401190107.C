// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


// Declare global variables, these variables are to read the CSV data
FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";
float listHottestColdest[2][3];

// Define max size of 2D array
#define MAX_ROWS 4000
#define MAX_COLS 20
#define MAX_LENGTH 1000


// Globally Declare the functions that are used
int getTotalRowAndColumn(int *columns);
void storeCSVData(char*** data, int rows, int cols);
float averageLandTemperatureEachYear(char*** data, int rows, int cols, int targetYear);
void storeAnswerToFile(char*** data, int rows, int columns, const char* fileName, int startYear, int endYear);
float averageLandTemperatureEachCentury(char*** data, int rows, int cols, int startYear, int endYear);
float averageLandTemperatureEachMonth(char*** data, int rows, int cols, int targetMonth);
void hottestColdestYear();
void writeColumnsToFile(char*** data, int rows, int columns, const char fileName[]);
void question10(char*** data,int rows,int cols, const char fileName[]);
float averagelandAndOceanTemperatures(char*** data, int row, int col, int targetYear);


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


    //Add new functions below here

    // Question 1:
    storeAnswerToFile(data, rows, columns,"q1", 1760, 2015);

    //Question 2:
    storeAnswerToFile(data,rows,columns,"q2",1760,1799);
    storeAnswerToFile(data,rows,columns,"q2",1800,1899);
    storeAnswerToFile(data,rows,columns,"q2",1900,1999);
    storeAnswerToFile(data,rows,columns,"q2",2000,2015);

    //Question 3:
    storeAnswerToFile(data,rows,columns,"q3",1,1);

    //Question 4:
    storeAnswerToFile(data,rows,columns,"q4",1,1);

    // Question 5
    writeColumnsToFile(data, rows, columns, "answers/q8.txt");

    // Question 10
    question10(data,rows,columns,"answers/q10.txt");

    //Question 11:
    storeAnswerToFile(data,rows,columns,"q11",1850,2015);

    // Free up allocated memory using the free function
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
        char dateCopy[100];  // Adjust the size as needed
        strcpy(dateCopy, data[r][0]);
        //Get the first value that is seperated by the "-" delimeter
        char *token = strtok(dateCopy, "-");
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
/**
 * Calculate teh average land temperature for each century
 * @param data - 3D array, that holds all the data from the CSV file
 * @param rows - Number of rows in the CSV files
 * @param columns - Number of columns in the CSV file
 * @param startYear - The year the century is started from
 * 
*/
float averageLandTemperatureEachCentury(char*** data, int rows, int columns, int startYear, int endYear) {
    // Initiating variables
    int counter = 0;
    float totalTemp = 0.0;
    float averageLandTemp = 0.0;

    // Loop for each row of the data array
    for (int r = 0; r < rows; r++) {
        char dateCopy[100];  // array to copy the date
        strcpy(dateCopy, data[r][0]); // using strcpy function to copy the date from the first column of the row (date) into new array
        char *token = strtok(dateCopy, "-"); // get year value
        int year = atoi(token); // change year into integer and store in year variable
        if (year >= startYear && year <= endYear) { // if condition for yearly temperature
            float yearlyTemp = averageLandTemperatureEachYear(data, rows, columns, year); // call on the averageLandTemperature function and store value in yearlyTemp
            if (yearlyTemp != 0.0) { // if statement to check if value is 0 
                totalTemp += yearlyTemp; // if not add the yearlyTemp to totalTemp
                counter++; // counter +1
            }
        }
    }
    averageLandTemp = (counter > 0) ? totalTemp / counter : 0; // basically a if else statement that checks if counter is greater than 1 and will find the average, else return 0
    return averageLandTemp; // return final average value
}


// Code below is Question 3
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
    // Initialize variables to find total temp
    float totalTemp = 0.0;
    int count = 0;

    for (int r = 0; r < rows; r++) {
        char dateCopy[100]; // Initialize array that will hold the date
        strcpy(dateCopy, data[r][0]); // Copy the date from data[r][0] into dateCopy
        char *token = strtok(dateCopy, "-"); // Get the year value from dateCopy
        token = strtok(NULL,"-"); // Get the month value from the date
        int month = atoi(token); // Store the value into the month value
        if (month == targetMonth) { // If the month is equal to the targetMonth 
            for (int c = 1; c < columns; c++) { // Use a for loop to go through all the months
                float temp = atof(data[r][1]); // store the temperature into the temp variable
                if (temp != 0.0) { // If the temperature isn't 0
                    totalTemp += temp; // Add it to the total temperature
                    count++; // Add 1 to the counter
                }
            }
        }
    }
    float averageTemp = (count > 0) ? totalTemp / count : -1; // If count is greater than 0 then calculate the average temp if not averageTemp is -1
    return averageTemp; // return the averageTemp variable
}




/**
 * This function is used to answer question 4
 * Function that calculates the average land temperature each month
 * @param data - pointer to the data
 * @param row - number of rows in 2d array
 * @param col - number of columns in 2d array
 * @param listHottestColdest - 2D array taht stores the hottest and coldest value
 * @return void
 * 
*/
void hottestColdestMonth(char*** data, int row, int columns, float **listHottestColdest) {
    // declaring intial values
    listHottestColdest[0][2] = -10000; // Set the Hottest temperature to -10000
    listHottestColdest[1][2] = 10000;  // Set the Coldest temperature to 10000
    float temp;

    // loop through the entire data array
    for (int r = 0; r < row; r++) {
        char dateCopy[100]; // Initialize a new char array that will hold the copy of the date
        strcpy(dateCopy, data[r][0]); // copy the date
        char *token = strtok(dateCopy, "-"); // seperate the date using "-" as the delimiter 
        float year = atof(token); // store the first value into the year variable

        token = strtok(NULL, "-"); // get the second value of dateCopy using the "-" delimiter
        float month = atof(token); // store the month into the month variable
        temp = atof(data[r][1]); // change the value of the second column of the data array to a floating number and storing to temp variable
            
        if (temp > listHottestColdest[0][2]){ // if statement for checking if temperature is greater than stored temperature
            listHottestColdest[0][0] = year; // update year row for hottest
            listHottestColdest[0][1] = month; // update month row for hottest
            listHottestColdest[0][2] = temp; // Update hottest temperature row
        }
        
        if (temp < listHottestColdest[1][2]){
            listHottestColdest[1][0] = year; // update year row for coldest
            listHottestColdest[1][1] = month; // update year row for coldest
            listHottestColdest[1][2] = temp; // Update coldest temperature row
        }
    }
}


//This function solves question 5
/**
 * Find the hottest and coldest year
*/
void hottestColdestYear() {
    // Open up answers/q1.txt and read from the file
    FILE *q1Values = fopen("answers/q1.txt", "r");
    // If q1Values is equal to NULL
    if (q1Values == NULL) {
        //Prompt the user that q1.txt cannot be opened
        printf("File q1.txt cannot be opened."); 
    }

    //Initialize values
    int year, highYear, lowYear;
    float avgTemp,hightemp2;
    float highTemp = -10000;
    float lowTemp = 10000;

    // While fscanf keeps returning two as in there are two inputs
    while (fscanf(q1Values, "%d , %f", &year, &avgTemp) == 2) {
        //If avgTemp is greather than highTemp
        if (avgTemp > highTemp) {
            //Store the highTemp and the year it occured
            highTemp = avgTemp;
            highYear = year;
        }
        // If avgTemp is less than lowTemp
        if (avgTemp < lowTemp) {
            // Store the temp into lowTemp variable and the year it occured
            lowTemp = avgTemp;
            lowYear = year;
        }
    }
    // close file after use
    fclose(q1Values);
    FILE *q5Values = fopen("answers/q5.txt","w"); // open file q5.txt for writing the answer
    fprintf(q5Values, "The hottest year is %d, with a temperature of %f\n", highYear, highTemp); // print statement for hottest year and the temp into txt file
    fprintf(q5Values, "The coldest year is %d, with a temperature of %f", lowYear, lowTemp); // print statement for coldest year and the temperature associated with it.
    fclose(q5Values); // close file
}


//For Q.8 find the average for all of em 
//Right now it just prints everytnig into the q8.txt not the average

// Question 8
typedef struct {
    double sum1, sum2, sum3;
    int count;
} YearData;

/**
 * Writes the second to fourth column from a CSV file to a file.
 * @param data - pointer to the data
 * @param rows - number of rows in the 2D array
 * @param columns - number of columns in the 2D array
 * @param fileName - name of the output file
 */
void writeColumnsToFile(char*** data, int rows, int columns, const char fileName[]) {
    // Initialize an array of YearData structures, assuming the data spans no more than 300 years
    YearData yearData[300] = {0};

    // Loop over each row of the data
    for (int r = 0; r < rows; r++) {
        // Copy the date string to a temporary variable
        char dateCopy[100];
        strcpy(dateCopy, data[r][0]);

        // Tokenize the date string to extract the year
        char *token = strtok(dateCopy, "-");
        int year = atoi(token);

        // If the year is within the range 1850 to 2015
        if (year >= 1850 && year <= 2015) {
            // Calculate the index in the yearData array corresponding to the year
            int index = year - 1850;

            // Accumulate the values for each column and increment the count
            yearData[index].sum1 += atof(data[r][1]);
            yearData[index].sum2 += atof(data[r][3]);
            yearData[index].sum3 += atof(data[r][4]);
            yearData[index].count++;
        }
    }

    // Open the file for writing
    FILE* file = fopen(fileName, "w");
    // If the file could not be opened, print an error message and return
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Loop over each element in the yearData array
    for (int i = 0; i < 300; i++) {
        // If the count for the year is greater than 0
        if (yearData[i].count > 0) {
            // Calculate the year and the averages for each column
            int year = i + 1850;
            double avg1 = yearData[i].sum1 / yearData[i].count;
            double avg2 = yearData[i].sum2 / yearData[i].count;
            double avg3 = yearData[i].sum3 / yearData[i].count;

            // Write the year and averages to the file
            fprintf(file, "%d, %f, %f, %f\n", year, avg1, avg2, avg3);
        }
    }

    // Close the file
    fclose(file);
}

//Question 10
/** 
 * Function to write average land temperature by month and the uncertainty data to a file if the year is 2000 or later
 * @param data - 3D array that holds every value in the CSV file
 * @param rows - Number of rows of the CSV file
 * @param cols - Number of cols in the CSV file
 * @param fileName - The name of the file that we are writing the data to
 * 
*/
void question10 (char*** data,int rows, int cols, const char fileName[]) {
    // Open the file for writing
    FILE* file = fopen(fileName, "w");

    // If the file could not be opened, print an error message and return
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Loop over each row of the data
    for (int r = 0; r < rows; r++) {
        // Copy the date string to a temporary variable
        char dateCopy[100];
        strcpy(dateCopy, data[r][0]);

        // Tokenize the date string to extract the year
        char *token = strtok(dateCopy, "-");
        int year = atoi(token);

        // If the year is 2000 or later
        if (year >= 2000) { 
            // Convert the land temp and the uncertanty to a float type
            float value1 = atof(data[r][1]);
            float value2 = atof(data[r][2]);

            // Write the date and the two values to the file
            fprintf(file, "%s, %f, %f\n", data[r][0], value1, value2);
        }
    }

    // Close the file
    fclose(file);
}

//Question 11
/**
 * Find the average Ocean Temperatures
 * @param data - 3D array that holds every value in the CSV file
 * @param rows - Number of rows of the CSV file
 * @param cols - Number of cols in the CSV file
 * @param targetYear - The year we are targetting
*/
float averagelandAndOceanTemperatures(char*** data, int row, int col, int targetYear) {
    // Declare variables
    int counter = 0;
    float totalTemp = 0.0;
    float landAndOceanAverageTemperature = 0.0;

    // Go through the entire data array
    for (int r = 0; r < row; r++) {
        // Get the date from the data array
        char dateCopy[100];  // Adjust the size as needed
        strcpy(dateCopy, data[r][0]);
        //Get the first value that is seperated by the "-" delimeter
        char *token = strtok(dateCopy, "-");
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
                float temp = atof(data[r][7]);
                
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
    //If counter is greater than 0 then calculate the average temp, if not then landAndOceanAverageTemperature is 0
    landAndOceanAverageTemperature  = (counter > 0) ? totalTemp / counter : 0;
    
    //Returns the landAndOceanAverageTemperature variable which holds the average temp of that year
    return landAndOceanAverageTemperature;
}


// Code below is to print the answers into a .txt file
/**
 * This function stores the answers to a text file. It takes in a 3D char array, 
 * the number of rows and columns in the data, the name of the file to write to, 
 * and the start and end years for the data.
 *
 * @param data A 3D char array containing the data to be written to the file.
 * @param rows The number of rows in the data.
 * @param columns The number of columns in the data.
 * @param fileName The name of the file to write to.
 * @param startYear The start year for the data.
 * @param endYear The end year for the data.
 */
void storeAnswerToFile (char*** data, int rows, int columns, const char* fileName, int startYear, int endYear) {
    // Folder path
    char folder [] = "answers/";
    // Initialize char array that will hold the full path
    char fullPath[100];
    //Copy folder to fullpath
    strcpy(fullPath,folder);
    // Combine file name and full path
    strcat(fullPath,fileName);
    //Combine full path and .txt
    strcat(fullPath,".txt");
    //Calculate the total year
    int totalYear = endYear- startYear;
    //2D array called month which holds all the month's names
    char month[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    //If fileName == q1
    if (strcmp(fileName, "q1") == 0) {
        // Open the file and write to the file
        file = fopen(fullPath,"w");
        // loop through for  totalYear + 1 times
        for (int i = 0; i < totalYear + 1; i++) {
            //Calculate the averageTemp
            float averageTemp = averageLandTemperatureEachYear(data, rows, columns, startYear + i);
            //Print the value into the file
            fprintf(file, "%d, %f\n", startYear + i, averageTemp);
        }   
    //If fileName == q2
    } if (strcmp(fileName, "q2") == 0) {
        file = fopen(fullPath,"a");
        float averageTemp = averageLandTemperatureEachCentury(data,rows,columns,startYear,endYear);
        fprintf(file,"%dth Century, %f\n",(startYear/100) + 1,averageTemp);

    }  if (strcmp(fileName, "q3") == 0) {
        file = fopen(fullPath,"w");
       for (int i = 1; i < 13; i++) {
            float averageTemp = averageLandTemperatureEachMonth(data, rows, columns, i);
            fprintf(file, "%s, %f\n", month[i-1], averageTemp);
        }
    }  if (strcmp(fileName,"q4") == 0) {
        float** listHottestColdest = (float**)malloc(2 * sizeof(float*));
        for (int i = 0; i < 2; i++) {
            listHottestColdest[i] = (float*)malloc(3 * sizeof(float));
        }

        hottestColdestMonth(data, rows, columns, listHottestColdest);

        file = fopen(fullPath,"w");
        fprintf(file, "Hottest Ever Recorded Month: Year = %.0f, Month = %s, Temperature = %f\n",listHottestColdest[0][0], month[(int)listHottestColdest[0][1]-1], listHottestColdest[0][2]);
        fprintf(file, "Coldest Ever Recorded Month: Year = %.0f, Month = %s, Temperature = %f\n",listHottestColdest[1][0], month[(int)listHottestColdest[1][1]-1], listHottestColdest[1][2]);

        for (int i = 0; i < 2; i++) {
            free(listHottestColdest[i]);
        }
        free(listHottestColdest);
     } if (strcmp(fileName, "q11") == 0) {
        file = fopen(fullPath,"w");
        for (int i = 0; i < totalYear + 1; i++) {
            float averageTemp = averageLandTemperatureEachYear(data, rows, columns, startYear + i);
            float averageLandAndOceanTemp = averagelandAndOceanTemperatures(data, rows, columns, startYear + i);
            fprintf(file, "%d, %f, %f\n", startYear + i, averageTemp,averageLandAndOceanTemp);
        }
     }   



    if (file != NULL) {
        fclose(file);
    }
}