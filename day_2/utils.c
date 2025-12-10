#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

bool is_valid_id_p1(long long id)
{
    int num_digits = floor(log10((double)id)) + 1;
    if (num_digits % 2 != 0)
    {
        return true;
    }

    int seq_len = num_digits / 2;
    char *seq_1 = (char*)malloc(seq_len + 1);
    char *seq_2 = (char*)malloc(seq_len + 1);

    char id_str[num_digits + 1];
    sprintf(id_str, "%lld", id);
    
    strncpy(seq_1, id_str, seq_len);
    strncpy(seq_2, id_str + seq_len, seq_len);
    seq_1[seq_len] = '\0';
    seq_2[seq_len] = '\0';

    int result = strcmp(seq_1, seq_2);
    free(seq_1);
    free(seq_2);

    if (result != 0)
    {
        return true;
    }
    return false;
}

bool is_valid_id_p2(long long id)
{
    int num_digits = floor(log10((double)id)) + 1;
    int max_seq_len = num_digits / 2;
    char id_str[num_digits + 1];
    sprintf(id_str, "%lld", id);


    for (int seq_len = 1; seq_len <= max_seq_len; seq_len++)
    {
        char *seq_1 = (char*)malloc(seq_len + 1);
        char *seq_2 = (char*)malloc(seq_len + 1);

        int chunks = num_digits / seq_len;
        strncpy(seq_1, id_str, seq_len);
        seq_1[seq_len] = '\0';

        bool pattern_repeated = true;
        for (int i = 0; i < chunks; i++)
        {
            if (num_digits % seq_len != 0) 
            {
                pattern_repeated = false;
                break;
            }
            strncpy(seq_2, id_str + i * seq_len, seq_len);
            seq_2[seq_len] = '\0';
            int result = strcmp(seq_1, seq_2);
            if (result != 0)
            {
                pattern_repeated = false;
                break;
            }
        }
        
        free(seq_1);
        free(seq_2);

        if (pattern_repeated)
        {
            return false;
        }
    }
    return true;
}

// Helper function to compute KMP LPS array
void compute_lps_array(const char* str, int M, int* lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M)
    {
        if (str[i] == str[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

bool is_valid_id_p2_kmp(long long id)
{
    int num_digits = floor(log10((double)id)) + 1;
    char id_str[num_digits + 1];
    sprintf(id_str, "%lld", id);

    int *lps = (int*)malloc(sizeof(int) * num_digits);
    compute_lps_array(id_str, num_digits, lps);

    // The length of the longest proper prefix which is also a suffix
    int overlap = lps[num_digits - 1];
    
    // The length of the repeating unit
    int len = num_digits - overlap;
    
    bool is_repeated = false;

    // Check if the pattern length divides the total length perfectly
    // AND the pattern is not the entire string itself (len < num_digits)
    // AND lps[n-1] is not 0 (meaning there is some suffix that is also a prefix)
    if (len < num_digits && num_digits % len == 0 && overlap > 0)
    {
        is_repeated = true;
    }

    free(lps);
    return !is_repeated;
}
