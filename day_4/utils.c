#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static int kernel[3][3] = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
};

long char_to_int(char c)
{
    if (c == '@')
    {
        return 1;
    }
    return 0;
}

long get_line_length(FILE *file)
{
    long pos = ftell(file);
    long max_length = 0;
    long current_length = 0;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        current_length++;
        if (c == '\n')
        {
            if (current_length > max_length)
            {
                max_length = current_length;
            }
            current_length = 0;
        }
    }
    // Check last line if no newline
    if (current_length > max_length)
    {
        max_length = current_length + 1; // Treat as if it had a newline for buffer safety
    }

    fseek(file, pos, SEEK_SET);
    return max_length;
}

long get_line_count(FILE *file)
{
    long pos = ftell(file);
    long lines = 0;
    long chars_on_line = 0;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        chars_on_line++;
        if (c == '\n')
        {
            lines++;
            chars_on_line = 0;
        }
    }
    if (chars_on_line > 0)
    {
        lines++;
    }

    fseek(file, pos, SEEK_SET);
    return lines;
}

char** read_file_to_buffer(FILE *file)
{
    long line_count = get_line_count(file);
    long line_length = get_line_length(file);
    if (line_count == 0 || line_length == 0)
    {
        return NULL;
    }   
    char **buffer = malloc(sizeof(char *) * line_count);
    for (int i = 0; i < line_count; i++)
    {
        buffer[i] = malloc(sizeof(char) * (line_length + 1)); // +1 for null terminator if needed, though we deal with chars
        if (fgets(buffer[i], line_length + 1, file) == NULL) {
            // Handle error or end of file
            break;
        }
    }
    fseek(file, 0, SEEK_SET);
    return buffer;
}

int** buffer_to_2d_array(char **buffer, int line_count, int line_length)
{
    int **array = malloc(sizeof(int *) * line_count);
    for (int i = 0; i < line_count; i++)
    {
        array[i] = malloc(sizeof(int) * line_length);
    }
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < line_length; j++)
        {
            array[i][j] = char_to_int(buffer[i][j]);
        }
    }
    
    return array;
}

int** convolve(int **array, int line_count, int line_length)
{
    int **convolved = malloc(sizeof(int *) * line_count);
    for (int i = 0; i < line_count; i++)
    {
        convolved[i] = malloc(sizeof(int) * line_length);
    }
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < line_length; j++)
        {
            convolved[i][j] = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k < 0 || i + k >= line_count || j + l < 0 || j + l >= line_length)
                    {
                        continue;
                    }
                    convolved[i][j] += array[i + k][j + l] * kernel[k + 1][l + 1];
                }
            }
        }
    }

    return convolved;
}

int count_forkliftable(int **layout, int **neighbors, int line_count, int line_length)
{
    int count = 0;
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < line_length; j++)
        {
            if (layout[i][j] == 1 && neighbors[i][j] < 4)
            {
                layout[i][j] = 0; // remove roll
                count++;
            }
        }
    }
    return count;
}

void free_buffer(char **buffer, int line_count)
{
    if (buffer == NULL) return;
    for (int i = 0; i < line_count; i++)
    {
        free(buffer[i]);
    }
    free(buffer);
}

void free_grid(int **grid, int line_count)
{
    if (grid == NULL) return;
    for (int i = 0; i < line_count; i++)
    {
        free(grid[i]);
    }
    free(grid);
}