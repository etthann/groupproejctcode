// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 10000
#define MAX_ROWS 5000
#define MAX_COLS 50

int main () {

    FILE *fileRead;
    FILE *fileWrite;
    char csvData[MAX_LENGTH];
    char data[MAX_ROWS][MAX_COLS][MAX_LENGTH];

    fileRead = fopen("GlobalTemperatures.csv","r");
    

    if (fileRead == NULL) {
        printf("Failed to open the GlobalTemperatures.csv");
        return 1;
    }
    
    int row = 0;
    while (fgets(csvData, sizeof(csvData), fileRead)) {
        int col = 0;
        char *value = strtok(csvData, ",");
        while (value) {
            strncpy(data[row][col],value,MAX_LENGTH);
            value = strtok(NULL,",");
            col++;
        }
        row++;
    }

    fclose(fileRead);

    for (int r = 0; r < sizeof(data); r++) {
        for (int c = 0; c < sizeof(data[r]); c++) {
            printf("Row: %d Value: %c",r,data[r][c]);
        }
    }  

    return 0;
}