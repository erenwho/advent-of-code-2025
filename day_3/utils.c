#include "utils.h"
#include "cell.h"
#include <math.h>

// sorry if this is unreadable :(
long long get_max_joltage_greedy(Cell *cells, Cell *cells_sorted, int line_count, int num_digits) {
    if (num_digits == 0) return 0;
    int *digits = malloc(sizeof(int) * num_digits);
    
    for (int i = 0; i < line_count; i++) {
        Cell cell_a = cells_sorted[i];
        if (cell_a.index > line_count - num_digits) continue;

        int prev_index = cell_a.index;
        digits[0] = cell_a.value;
        for (int j = 1; j < num_digits; j++) {
            int max_value = -1; 
            for (int k = prev_index + 1; k < line_count - (num_digits - j - 1); k++) {
                if (cells[k].value > max_value) {
                    max_value = cells[k].value;
                    prev_index = k;
                }
            }
            digits[j] = max_value;
        }
        break;
    }

    long long max_joltage = 0;
    for (int i = 0; i < num_digits; i++) {
        max_joltage += (long long)digits[i] * (long long)pow(10, num_digits - i - 1);
    }
    free(digits);
    return max_joltage;
}

long get_line_length(FILE *file)
{
    long pos = ftell(file);
    long length = 0;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        length++;
        if (c == '\n')
        {
            break;
        }
    }

    fseek(file, pos, SEEK_SET);
    return length;
}

// uneeded but w/e 
int get_min_index_of_value(Cell *cells, int line_count, Cell cell) {
    int min_index = cell.index;
    for (int i = 1; i < line_count; i++) {
        if (cells[i].value == cell.value && cells[i].index < min_index) {
            min_index = cells[i].index;
        }
    }
    return min_index;
}

int get_max_index_of_value(Cell *cells, int line_count, Cell cell) {
    int max_index = cell.index;
    for (int i = 1; i < line_count; i++) {  
        if (cells[i].value == cell.value && cells[i].index > max_index) {
            max_index = cells[i].index;
        }
    }
    return max_index;
}


