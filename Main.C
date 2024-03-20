#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 10000

int main () {

    FILE *fileRead;
    FILE *fileWrite;
    char csvData[MAX_LENGTH];

    fileRead = fopen("GlobalTemperatures.csv","r");
    fileWrite = fopen("Data.txt","w");
    

    if (fileRead == NULL) {
        printf("Failed to open the GlobalTemperatures.csv");
        return 1;
    }

    while (fgets(csvData, MAX_LENGTH, fileRead)) {
        char *value = csvData;
        char *end;
        while ((end = strchr(value, ',')) != NULL) {
            *end = '\0';
            if (strcmp(value, "") == 0) {
                printf("N/A ");
                fprintf(fileWrite, "N/A ");
            } else {
                printf("%s ",value);
                fprintf(fileWrite, "%s ",value);
            }
            value = end + 1;
        }
        // Handle last value in the line
        if (strcmp(value, "") == 0) {
            printf("N/A ");
            fprintf(fileWrite, "N/A ");
        } else {
            printf("%s ",value);
            fprintf(fileWrite, "%s ",value);
        }
        printf("\n");
    }

    fclose(fileRead);
    fclose(fileWrite);
    return 0;
}