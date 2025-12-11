#ifndef CELL_H
#define CELL_H

typedef struct Cell {
    int index;
    int value;
} Cell;

int compare_cells(const void *a, const void *b);

#endif