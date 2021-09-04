#ifndef MOSCOW_1941_PART2_X_PART_H
#define MOSCOW_1941_PART2_X_PART_H


#include <cstdio>
#include "Y_part.h"

class X_part {
public:
    size_t x_index;
    X_part *nextM;
    Y_part *child;

    X_part(size_t x);

    ~X_part();
};

#endif
