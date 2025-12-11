#include "cell.h"

void init_cell(Cell *cell, int index, int value) {
    cell->index = index;
    cell->value = value;
}

// sort cells by value in descending order
int compare_cells(const void *a, const void *b) {
    Cell *cell_a = (Cell *)a;
    Cell *cell_b = (Cell *)b;
    if (cell_a->value == cell_b->value)
    {
        if (cell_a->index < cell_b->index)
        {
            return -1;
        }
        return 1;
    } 
    return cell_b->value - cell_a->value;
}
