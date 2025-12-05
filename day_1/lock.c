#include "lock.h"

void init_lock(Lock *lock, int dial_pos, int max_pos)
{
    lock->dial_pos = dial_pos;
    lock->max_pos = max_pos;
}

int turn_left(Lock *lock, int dist)
{
    int range = lock->max_pos + 1;
    int zero_passes = 0;
    
    if (lock->dial_pos == 0) {
        zero_passes = dist / range;
    } else {
        if (dist >= lock->dial_pos) {
            zero_passes = 1 + (dist - lock->dial_pos) / range;
        }
    }
    
    lock->dial_pos = (lock->dial_pos - (dist % range) + range) % range;
    return zero_passes;
}

int turn_right(Lock *lock, int dist)
{
    int range = lock->max_pos + 1;
    int zero_passes = (dist + lock->dial_pos)/range;
    lock->dial_pos = (lock->dial_pos + (dist % range)) % range;
    return zero_passes;
}