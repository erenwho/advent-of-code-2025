#include <stdio.h>
#include <assert.h>

#include "lock.h"

enum Status
{
    OK,
    ERROR
};

int main() {
    Lock lock;
    int passes;
    float num_tests = 0;
    float num_passes = 0;

    // Case 1: Start 5, move 6. Should wrap once (5->...->0->99).
    init_lock(&lock, 5, 99);
    passes = turn_left(&lock, 6);
    printf("Left 5->6: Passes=%d (Expected 1), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 1) {
        num_passes++;
    }
    num_tests++;
    
    // Case 2: Start 0, move 1. Should wrap once (0->99).
    init_lock(&lock, 0, 99);
    passes = turn_left(&lock, 1);
    printf("Left 0->1: Passes=%d (Expected 0), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 0) {
        num_passes++;
    }
    num_tests++;

    // Case 3: Start 5, move 106. Should wrap twice.
    init_lock(&lock, 5, 99);
    passes = turn_left(&lock, 106);
    printf("Left 5->106: Passes=%d (Expected 2), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 2) {
        num_passes++;
    }
    num_tests++;

    // Case 4: Start 5, move 5. Should count as 1 pass (landing on 0).
    init_lock(&lock, 5, 99);
    passes = turn_left(&lock, 5);
    printf("Left 5->5: Passes=%d (Expected 1), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 1) {
        num_passes++;
    }
    num_tests++;

    // Case 5: Start 0, move 1. Should count as 0 passes.
    init_lock(&lock, 0, 99);
    passes = turn_left(&lock, 1);
    printf("Left 0->1: Passes=%d (Expected 0), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 0) {
        num_passes++;
    }
    num_tests++;

    // Case 6: Start 0, move 100. Should count as 1 pass.
    init_lock(&lock, 0, 99);
    passes = turn_left(&lock, 100);
    printf("Left 0->100: Passes=%d (Expected 1), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 1) {
        num_passes++;
    }
    num_tests++;

    // Case 7: Start 99, move 1. Should wrap once (99->0).
    init_lock(&lock, 99, 99);
    passes = turn_right(&lock, 1);
    printf("Right 99->1: Passes=%d (Expected 1), Pos=%d\n", passes, lock.dial_pos);
    if (passes == 1) {
        num_passes++;
    }
    num_tests++;

    printf("Percentage passes: %.2f%%\n", num_passes / num_tests * 100.0);

    if (num_passes != num_tests) {
        return ERROR;
    }

    return OK;
}
