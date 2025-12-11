#include <stdio.h>

typedef struct {
    int dial_pos;
    int max_pos;
} Lock;

void init_lock(Lock *lock, int dial_pos, int max_pos);
int turn_left(Lock *lock, int dist);
int turn_right(Lock *lock, int dist);
