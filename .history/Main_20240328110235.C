// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// define 
#define MAX_LENGTH 10000
#define MAX_ROWS 5000

int main () {

    FILE *fileRead;
    FILE *fileWrite;
    char csvData[MAX_LENGTH];
    char data[MAX_ROWS][MAX_LENGTH];

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

    int num_rows = sizeof(data) / sizeof(data[0]);
    int num_cols = sizeof(data[0]) / sizeof(data[0][0]);

    fclose(fileRead);

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            if (strlen(data[r][c]) > 0) {
                printf("Row: %d Value: %s\n", r, data[r][c]);
            }
        }
    }
    return 0;
}