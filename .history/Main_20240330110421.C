// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";

int getTotalRow(int *columns);

int main() {
    int *columns;
    int rows = getTotalRow(columns);
    
    return 0;
}

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
            *columns = *columns + 1;    
        if (c== '\n')
            line++;
    } while (c != EOF);

    fclose(file);

    
    return line;

}

