// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int get_rows(char file[1000]);

int main()
{
    int number_of_rows = get_rows("GlobalTemperatures.csv");
}

int get_rows(char file[1000])
{
    FILE *input;
    int count = 0;
    char buffer[1000];
    input = fopen(file, "r");
    while (fgets(buffer, sizeof(buffer), input))
    {
        count += 1;
    }
    fclose(input);
    return count - 2;
}