#ifndef MOSCOW_1941_PART2_Y_PART_H
#define MOSCOW_1941_PART2_Y_PART_H


#include <cstdio>

class Y_part {
public:
    size_t y_index;
    int value;
    Y_part *nextY;

    Y_part();

    Y_part(size_t y, int val);

    ~Y_part();
};


#endif
