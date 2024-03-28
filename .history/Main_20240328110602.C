// include library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// define variables
#define MAX_LENGTH 10000
#define MAX_ROWS 5000

// main function
int main () {

    FILE *fileRead;
    char csvData[MAX_LENGTH];
    char data[MAX_ROWS][MAX_LENGTH];

    fileRead = fopen("GlobalTemperatures.csv","r");

    if (fileRead == NULL) {
        printf("Failed to open the GlobalTemperatures.csv");
        return 1;
    }
    
    int row = 0;
    while (fgets(csvData, sizeof(csvData),fileRead)) {
        strncpy(data[row],csvData,MAX_LENGTH);
        row++;
    }

    fclose(fileRead);

    for (int r = 0; r < row; r++) { // Use the actual number of rows read
        if (strlen(data[r]) > 0) {
            printf("Row: %d Value: %s", r, data[r]); // Print each line
        }
    }

    return 0;
}