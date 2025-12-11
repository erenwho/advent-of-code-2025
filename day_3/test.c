#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cell.h"
#include "utils.h"

// Helper to create cells from string
void create_cells(const char *str, Cell *cells, Cell *cells_sorted) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        cells[i].index = i;
        cells[i].value = CHAR_TO_INT(str[i]);
        cells_sorted[i] = cells[i];
    }
    qsort(cells_sorted, len, sizeof(Cell), compare_cells);
}

void test_example_cases() {
    printf("Running example cases...\n");
    
    // Case 1: 987654321111111, pick 2 -> 98
    {
        const char *input = "987654321111111";
        int len = strlen(input);
        Cell *cells = malloc(sizeof(Cell) * len);
        Cell *cells_sorted = malloc(sizeof(Cell) * len);
        create_cells(input, cells, cells_sorted);
        
        long long result = get_max_joltage_greedy(cells, cells_sorted, len, 2);
        assert(result == 98);
        printf("PASS: %s -> %lld\n", input, result);
        
        free(cells);
        free(cells_sorted);
    }

    // Case 2: 811111111111119, pick 2 -> 89
    {
        const char *input = "811111111111119";
        int len = strlen(input);
        Cell *cells = malloc(sizeof(Cell) * len);
        Cell *cells_sorted = malloc(sizeof(Cell) * len);
        create_cells(input, cells, cells_sorted);
        
        long long result = get_max_joltage_greedy(cells, cells_sorted, len, 2);
        assert(result == 89);
        printf("PASS: %s -> %lld\n", input, result);
        
        free(cells);
        free(cells_sorted);
    }

    // Case 3: 234234234234278, pick 2 -> 78
    {
        const char *input = "234234234234278";
        int len = strlen(input);
        Cell *cells = malloc(sizeof(Cell) * len);
        Cell *cells_sorted = malloc(sizeof(Cell) * len);
        create_cells(input, cells, cells_sorted);
        
        long long result = get_max_joltage_greedy(cells, cells_sorted, len, 2);
        assert(result == 78);
        printf("PASS: %s -> %lld\n", input, result);
        
        free(cells);
        free(cells_sorted);
    }

     // Case 4: 818181911112111, pick 2 -> 92
    {
        const char *input = "818181911112111";
        int len = strlen(input);
        Cell *cells = malloc(sizeof(Cell) * len);
        Cell *cells_sorted = malloc(sizeof(Cell) * len);
        create_cells(input, cells, cells_sorted);
        
        long long result = get_max_joltage_greedy(cells, cells_sorted, len, 2);
        assert(result == 92);
        printf("PASS: %s -> %lld\n", input, result);
        
        free(cells);
        free(cells_sorted);
    }
}

void test_complex_cases() {
    printf("Running complex N > 2 cases...\n");
    {
        // Case 1: 9879, pick 3 -> 989
        const char *input = "9879";
        int len = strlen(input);
        Cell *cells = malloc(sizeof(Cell) * len);
        Cell *cells_sorted = malloc(sizeof(Cell) * len);
        create_cells(input, cells, cells_sorted);
        
        long long result = get_max_joltage_greedy(cells, cells_sorted, len, 3);
        assert(result == 989); 
        printf("PASS: %s (N=3) -> %lld\n", input, result);
        
        free(cells);
        free(cells_sorted);
    }
}

int main() {
    test_example_cases();
    test_complex_cases();
    printf("All tests passed!\n");
    return 0;
}