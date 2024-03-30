// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

FILE * file;
const char fileName[23] = "GlobalTemperatures.csv";

int main() {
    rows = 
    return 0;
}

int getTotalRow () {
    file = fopen(fileName,"r");

    if (file == NULL) {
        printf("Failed to open %d",fileName);
        return 1;
    }

    int line = 1;
    char c;
    
    do {
        c = fgetc(file);
        if (c== '\n')
            line++;
    } while (c != EOF);

    fclose(file);

    return line;

}

