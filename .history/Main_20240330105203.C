// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main() {
    FILE *file;
    const char fileName[23] = "GlobalTemperatures.csv";

    file = fopen(fileName,"r");

    if (file == NULL) {
        printf("Can't open file");
    }

}


