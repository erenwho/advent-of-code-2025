# Advent of Code 2025 - Day 2

This directory contains the solution for Day 2 of Advent of Code 2025, implemented in C.

## Problem Description
The challenge involves analyzing ranges of ID numbers to determine their validity based on specific pattern matching rules.

- **Part 1**: Checks if an ID has an even number of digits and if the first half of the digits is identical to the second half (e.g., `1212` is invalid, `1234` is valid).
- **Part 2**: Extended the validation to check if the ID contains *any* repeating pattern that spans the entire string (e.g., `121212` is invalid because `12` repeats). This part includes an optimized implementation using the Knuth-Morris-Pratt (KMP) algorithm's LPS array to detect periodicity in O(N) time.

## File Structure

- **`main.c`**: The entry point. Reads ranges from `input.txt`, validates IDs, and computes the sum of invalid IDs.
- **`utils.c` / `utils.h`**: Helper functions for line reading and ID validation logic. Contains both the brute-force and KMP implementations for Part 2.
- **`test.c`**: Unit tests for the utility functions, including a performance benchmark comparing the brute-force vs. KMP approaches.
- **`input.txt`**: The puzzle input containing comma-separated ranges (e.g., `10-20,30-40`).

## Compilation and Execution

### Running the Solution
To compile and run the main solution:

```bash
gcc main.c utils.c -o main.exe
./main.exe
```

### Running Tests
To compile and run the unit tests and performance benchmarks:

```bash
gcc test.c utils.c -o test.exe
./test.exe
```

## Performance Optimization
For Part 2, a KMP-based approach (`is_valid_id_p2_kmp`) was implemented to replace the initial brute-force check (`is_valid_id_p2`).

- **Brute Force**: Checks every possible substring length.
- **KMP Algorithm**: Computes the Longest Prefix Suffix (LPS) array to mathematically determine the smallest repeating unit in linear time.

**Benchmark Results:**
The KMP implementation is approximately **3x faster** than the brute-force approach on the provided input.
