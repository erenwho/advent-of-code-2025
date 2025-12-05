# Advent of Code 2025 - Day 1

## Reference
[Advent of Code 2025 Day 1](https://adventofcode.com/2025/day/1)

## Solution Explanation

The challenge involves simulating a lock dial with positions ranging from 0 to 99 (a size of 100). We are provided with a series of instructions to turn the dial Left or Right by a specific distance.

### The Goal
The objective is to calculate two metrics:
1. **Zero Count**: The number of times the dial ends a turn exactly on position 0.
2. **Zero Passes**: The number of times the dial passes through or lands on position 0 during a turn.

### Implementation Details

The solution is implemented in C and consists of:
- `main.c`: Handles file input, parsing instructions, and driving the simulation.
- `lock.c` / `lock.h`: Defines the `Lock` structure and the logic for turning the dial.

#### Zero Pass Logic

The most critical part of the solution is correctly calculating the number of times the dial passes zero.

**Turning Right:**
When turning right (increasing position), the number of zero passes is straightforward:
```c
passes = (distance + current_pos) / 100;
```

**Turning Left:**
When turning left (decreasing position), the logic handles specific edge cases:
- If the dial is currently at 0, moving left only counts as a pass if we wrap around the entire dial (distance >= 100).
- If the dial is at a positive position, moving left counts as a pass if the distance is sufficient to reach or pass 0.

```c
if (current_pos == 0) {
    passes = distance / 100;
} else {
    if (distance >= current_pos) {
        passes = 1 + (distance - current_pos) / 100;
    }
}
```

This ensures that:
- Moving Left `5` from `5` counts as 1 pass (landing on 0).
- Moving Left `1` from `0` counts as 0 passes (wrapping to 99).
- Moving Left `100` from `0` counts as 1 pass (wrapping all the way back to 0).
