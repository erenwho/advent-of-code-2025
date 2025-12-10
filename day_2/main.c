#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

enum Status
{
    OK,
    ERROR
};

typedef struct Range {
    long long start;
    long long end;
} Range;

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return ERROR;
    }

    long len = get_line_length(file);
    if (len == 0)
    {
        return ERROR;
    }

    char *line = (char*)malloc(len + 1);
    long long invalid_id_sum = 0;
    if (fgets(line, len + 1, file))
    {
        line[strcspn(line, "\n")] = 0;
        
        char *token = strtok(line, ",");
        while (token != NULL)
        {
            long long start, end;
            if (sscanf(token, "%lld-%lld", &start, &end) == 2)
            {
                Range r = {start, end};
                printf("\nRange: (%lld, %lld) ", r.start, r.end);
                fflush(stdout);
                for (long long j = r.start; j <= r.end; j++)
                {
                    if (!is_valid_id_p2(j))
                    {
                        invalid_id_sum += j;
                        printf("Invalid ID: %lld\n", j);
                    }
                }
            }
            token = strtok(NULL, ",");
        }
        printf("\n");
        free(line);
    }
    else
    {
        free(line);
    }

    printf("Invalid ID sum: %lld\n", invalid_id_sum);

    fclose(file);
    return OK;
}