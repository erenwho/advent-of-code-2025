#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cell.h"

#define CHAR_TO_INT(c) ((c) - '0')

long long get_max_joltage_greedy(Cell *cells, Cell *cells_sorted, int line_count, int num_digits);
long get_line_length(FILE *file);
int get_min_index_of_value(Cell *cells, int line_count, Cell cell);
int get_max_index_of_value(Cell *cells, int line_count, Cell cell);