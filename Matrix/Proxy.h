#ifndef MOSCOW_1941_PART2_X_PARTPROXY_H
#define MOSCOW_1941_PART2_X_PARTPROXY_H

#include <cstdio>
#include "X_part.h"

class Y_partProxy;
class Y_partConstProxy;
class Matrix;

class X_partProxy {
public:
    X_part *X_row;
    Matrix *Buf;
    size_t x_size;
    size_t y_size;
    size_t x_index;

    X_partProxy(const X_partProxy &a);
    X_partProxy(size_t i, size_t i1);
    Y_partProxy operator[](size_t i);
    Y_partProxy operator+(size_t i);
    X_partProxy operator*();
};

class Y_partProxy {
public:
    size_t y_index;
    X_partProxy *FoundRow;
    Y_part *Found;

    Y_partProxy(X_partProxy *pProxy, size_t i);
    operator int() const;
    Y_partProxy operator*();
    Y_partProxy &operator=(int a);
};

class X_partConstProxy {
public:
    const X_part *X_row;
    const Matrix *Buf;
    size_t x_size;
    size_t y_size;
    size_t x_index;

    X_partConstProxy(const X_partConstProxy &a);

    X_partConstProxy(size_t i, size_t i1, size_t i2, X_part *q, const Matrix *a);

    Y_partConstProxy operator[](size_t i) const;

    Y_partConstProxy operator+(size_t i) const;

    X_partConstProxy operator*();
};

class Y_partConstProxy {
public:
    const X_partConstProxy *FoundRow;
    const Y_part *Found;
    size_t y_index;
    Y_partConstProxy(const X_partConstProxy *pProxy, size_t i);
    Y_partConstProxy operator*();

    operator int() const;
};

#endif
