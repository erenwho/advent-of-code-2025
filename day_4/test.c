#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void test_part1() {
    int line_count = 10;
    int line_length = 10;
    
    // Allocate layout
    int **layout = malloc(sizeof(int *) * line_count);
    for (int i=0; i<line_count; i++) {
        layout[i] = calloc(line_length, sizeof(int));
    }
    
    // Example from problem description: "x" marks accessible rolls in original diagram.
    // ..@@.@@@@.
    // @@@.@.@.@@
    // @@@@@.@.@@
    // @.@@@@..@.
    // @@.@@@@.@@
    // .@@@@@@@.@
    // .@.@.@.@@@
    // @.@@@.@@@@
    // .@@@@@@@@.
    // @.@.@@@.@.
    
    char *input[] = {
        "..@@.@@@@.",
        "@@@.@.@.@@",
        "@@@@@.@.@@",
        "@.@@@@..@.",
        "@@.@@@@.@@",
        ".@@@@@@@.@",
        ".@.@.@.@@@",
        "@.@@@.@@@@",
        ".@@@@@@@@.",
        "@.@.@@@.@."
    };

    // Initialize layout
    for (int i=0; i<line_count; i++) {
        for (int j=0; j<line_length; j++) {
            layout[i][j] = char_to_int(input[i][j]);
        }
    }

    // Run Logic
    int **convolved = convolve(layout, line_count, line_length);
    int count = count_forkliftable(layout, convolved, line_count, line_length);

    printf("Test Part 1 Result: %d (Expected: 13)\n", count);
    if (count == 13) printf("PASS\n"); else printf("FAIL\n");
}

int main() {
    test_part1();
    return 0;
}