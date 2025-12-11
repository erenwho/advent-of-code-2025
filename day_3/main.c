#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cell.h"
#include "utils.h"

enum Status
{
    OK,
    ERROR
};

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {   
        printf("Error opening file\n");
        return ERROR;
    }
    
    int capacity = 200;
    char **lines = malloc(sizeof(char*) * capacity);
    int line_count = 0;

    while (1)
    {
        long len = get_line_length(file);
        if (len == 0) break;

        if (line_count >= capacity)
        {
            capacity *= 2;
            lines = realloc(lines, sizeof(char*) * capacity);
        }

        lines[line_count] = malloc(sizeof(char) * (len + 1));
        if (fgets(lines[line_count], len + 1, file) == NULL)
        {
            free(lines[line_count]);
            break;
        }
        line_count++;
    }

    long long total_joltage = 0;
    for (int i = 0; i < line_count; i++)
    {
        int len = 0;
        while(lines[i][len] != '\n' && lines[i][len] != '\0' && lines[i][len] != '\r') {
            len++;
        }

        Cell *cells = malloc(sizeof(Cell) * len);
        Cell *cells_sorted = malloc(sizeof(Cell) * len);
        for (int j = 0; j < len; j++)   
        {
            cells[j].index = j;
            cells[j].value = CHAR_TO_INT(lines[i][j]);

            cells_sorted[j].index = j;
            cells_sorted[j].value = CHAR_TO_INT(lines[i][j]);
        }

        qsort(cells_sorted, len, sizeof(Cell), compare_cells);
        long long max_joltage = get_max_joltage_greedy(cells, cells_sorted, len, 12);
        total_joltage += max_joltage;
        free(cells);
    }
    
    printf("Total joltage: %lld\n", total_joltage);

    for (int i = 0; i < line_count; i++)
    {
        free(lines[i]);
    }
    free(lines);

    fclose(file);
    return OK;
}