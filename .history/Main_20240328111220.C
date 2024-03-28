// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 10000
#define MAX_ROWS 5000


int main () {

    return 0;
}

void readCSVFile () {
    FILE * fileRead;
    char csvData[MAX_LENGTH];
    char data[MAX_ROWS][MAX_LENGTH];

    fileRead = fopen("GlobalTemperatures.csv","r");

    if (fileRead == NULL) {
        printf("Failed to open CSV File");
    }
    
    int row = 0;

    while (fgets(csvData,sizeof(csvData),fileRead)) {
        strncpy(data[row],csvData,MAX_LENGTH);
        row++;
    }
    fclose(fileRead);

    for (int r = 0; r < row; r++) {
    char *value = strtok(data[r], ",");
    while (value) {
        printf("Value: %s\n", value);
        value = strtok(NULL, ",");
    }
}

}