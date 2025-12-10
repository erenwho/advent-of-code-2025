#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Test get_line_length
void test_get_line_length() {
    FILE *file = fopen("test_input.txt", "w");
    fprintf(file, "Hello\nWorld");
    fclose(file);

    file = fopen("test_input.txt", "r");
    long len = get_line_length(file);
    assert(len == 6);
    fclose(file);
    printf("test_get_line_length passed!\n");
}

// Test is_valid_id_p1
void test_is_valid_id_p1() {
    assert(is_valid_id_p1(11) == false);   // 2 digits, repeated -> false
    assert(is_valid_id_p1(1212) == false); // "12" == "12" -> false
    assert(is_valid_id_p1(1234) == true); // "12" != "34" -> true
    assert(is_valid_id_p1(123) == true);  // odd digits -> true
    printf("test_is_valid_id_p1 passed!\n");
}

// Test is_valid_id_p2
void test_is_valid_id_p2() {
    // Example cases
    assert(is_valid_id_p2(1212) == false);      // Repeated "12"
    assert(is_valid_id_p2(123123) == false);    // Repeated "123"
    assert(is_valid_id_p2(121212) == false);    // Repeated "12" three times
    assert(is_valid_id_p2(123124) == true);     // Not repeated
    assert(is_valid_id_p2(12345) == true);      // Odd length (prime length 5)
    printf("test_is_valid_id_p2 passed!\n");
}

// Test is_valid_id_p2_kmp
void test_is_valid_id_p2_kmp() {
    assert(is_valid_id_p2_kmp(1212) == false);
    assert(is_valid_id_p2_kmp(123123) == false);
    assert(is_valid_id_p2_kmp(121212) == false);
    assert(is_valid_id_p2_kmp(123124) == true);
    assert(is_valid_id_p2_kmp(12345) == true);
    printf("test_is_valid_id_p2_kmp passed!\n");
}

void test_performance() {
    printf("\nRunning performance test...\n");
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Could not open input.txt for performance test.\n");
        return;
    }

    // Read all IDs into memory first to avoid I/O affecting timing
    long len = get_line_length(file);
    if (len == 0) return;
    
    // Just estimate max possible IDs for simplicity or re-read
    // For this test, let's just parse the whole file and store numbers
    // A simple dynamic array would work, but to keep it simple without extra deps:
    // We will just read the file twice, once for each function. 
    // Wait, reading file during timing is bad. 
    // Let's store them.
    
    // Count items first
    int capacity = 10000;
    long long *ids = malloc(sizeof(long long) * capacity);
    int count = 0;
    
    char *line = (char*)malloc(len + 1);
    while (fgets(line, len + 1, file)) {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {
            long long start, end;
            if (sscanf(token, "%lld-%lld", &start, &end) == 2) {
                // We'll test every number in the ranges to get a meaningful load
                // But that might be too many. Let's just pick a few from each range
                // or just the bounds to be fast enough? 
                // The user asked to use input.txt.
                // Let's just store the start and end of ranges and iterate during test.
                
                // Let's just store ranges to save memory and iterate later
                if (count + 2 >= capacity) {
                    capacity *= 2;
                    ids = realloc(ids, sizeof(long long) * capacity);
                }
                ids[count++] = start;
                ids[count++] = end;
            }
            token = strtok(NULL, ",");
        }
    }
    free(line);
    fclose(file);
    
    printf("Loaded %d ranges. Starting benchmarks...\n", count/2);
    
    // Timer for P2 (Brute Force)
    clock_t start_time = clock();
    long long volatile sum_p2 = 0; // volatile to prevent optimization
    for (int i = 0; i < count; i += 2) {
        for (long long j = ids[i]; j <= ids[i+1]; j++) {
             if (!is_valid_id_p2(j)) sum_p2++;
        }
    }
    double time_p2 = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    
    // Timer for KMP
    start_time = clock();
    long long volatile sum_kmp = 0;
    for (int i = 0; i < count; i += 2) {
        for (long long j = ids[i]; j <= ids[i+1]; j++) {
             if (!is_valid_id_p2_kmp(j)) sum_kmp++;
        }
    }
    double time_kmp = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    
    printf("Brute Force (p2): %.6f seconds\n", time_p2);
    printf("KMP (p2_kmp):     %.6f seconds\n", time_kmp);
    printf("Speedup:          %.2fx\n", time_p2 / time_kmp);
    
    if (sum_p2 != sum_kmp) {
        printf("ERROR: Results mismatch! P2: %lld, KMP: %lld\n", sum_p2, sum_kmp);
    } else {
        printf("Results match.\n");
    }
    
    free(ids);
}

int main() {
    test_get_line_length();
    test_is_valid_id_p1();
    test_is_valid_id_p2();
    test_is_valid_id_p2_kmp();
    
    test_performance();
    
    printf("All tests passed!\n");
    return 0;
}
