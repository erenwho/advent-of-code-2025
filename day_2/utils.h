#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

long get_line_length(FILE *file);
bool is_valid_id_p1(long long id);
bool is_valid_id_p2(long long id);
bool is_valid_id_p2_kmp(long long id);

#endif
