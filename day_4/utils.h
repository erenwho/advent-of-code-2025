#ifndef UTILS_H
#define UTILS_H

enum Status {
    OK,
    ERROR
};


long char_to_int(char c);
long get_line_length(FILE *file);
long get_file_length(FILE *file);
long get_line_count(FILE *file);
char** read_file_to_buffer(FILE *file);
int** buffer_to_2d_array(char **buffer, int line_count, int line_length);
int** convolve(int **array, int line_count, int line_length);
int count_forkliftable(int **layout, int **neighbors, int line_count, int line_length);
void free_buffer(char **buffer, int line_count);
void free_grid(int **grid, int line_count);

#endif
