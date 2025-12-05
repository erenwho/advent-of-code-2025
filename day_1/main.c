#include <stdio.h>
#include <stdlib.h>

#include "lock.h"

enum Direction
{
    LEFT,
    RIGHT
};

enum Status
{
    OK,
    ERROR
};

struct Move
{
    enum Direction direction;
    int distance;
};

int main()
{
    Lock lock;
    init_lock(&lock, 50, 99);
    int zero_count = 0;
    int zero_passes = 0;

    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return ERROR;
    }

    char line[8];
    printf("Initial dial position: %d\n", lock.dial_pos);
    while (fgets(line, 8, file))
    {
        struct Move move;
        move.direction = line[0] == 'L' ? LEFT : RIGHT;
        move.distance = atoi(line + 1);
        printf("Move: %d %d\n", move.direction, move.distance);
        if (move.direction == LEFT)
        {
            zero_passes += turn_left(&lock, move.distance);
        }
        else
        {
            zero_passes += turn_right(&lock, move.distance);
        }
        printf("Dial position: %d\nZero passes: %d\n", lock.dial_pos, zero_passes);

        if (lock.dial_pos == 0)
        {
            zero_count++;
        }
    }

    printf("Dial position: %d\nZero count: %d\nZero passes: %d\n", lock.dial_pos, zero_count, zero_passes);

    return OK;
}
