#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return ERROR;
    }

    char **buffer = read_file_to_buffer(file);
    int line_count = get_line_count(file);
    int line_length = get_line_length(file);

    int **array = buffer_to_2d_array(buffer, line_count, line_length);
    int **convolved = convolve(array, line_count, line_length);
    int count = count_forkliftable(array, convolved, line_count, line_length);
    printf("PART 1: %d\n", count);

    int removed_rolls = count;
    while (removed_rolls > 0)
    {
        convolved = convolve(array, line_count, line_length);
        removed_rolls = count_forkliftable(array, convolved, line_count, line_length);
        count += removed_rolls;
    }   
    printf("PART 2: %d\n", count);

    free_buffer(buffer, line_count);
    free_grid(array, line_count);
    free_grid(convolved, line_count);

    return OK;
}
