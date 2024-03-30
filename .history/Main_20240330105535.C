// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

FILE * file;

int main() {
    file = fopen(fileName,"r");

    if (file == NULL) {
        printf("Can't open file");
    }

    int current_line =1 ;
    char c;
    do {
        c = fgetc(file);
        if (c == '\n')
        current_line++;

    } while (c != EOF);

    fclose(file);

    printf("lines: %d\n",current_line);

    return 0;
}

int getTotalRow () {
    
}

