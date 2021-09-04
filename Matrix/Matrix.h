#ifndef MOSCOW_1941_PART2_MATRIX_H
#define MOSCOW_1941_PART2_MATRIX_H

#include <cstdio>
#include "Proxy.h"

class X_partConstProxy;

class X_partProxy;

class Matrix {
    size_t X_Number;
    size_t Y_Number;
    X_part *firstM;
public:
    Matrix();

    Matrix(size_t x, size_t y);

    Matrix(const Matrix &a);

    size_t num_rows() const;

    size_t num_columns() const;

    X_part *GetFirst() const;

    X_partConstProxy operator[](size_t i) const;

    X_partProxy operator[](size_t i);

    X_partConstProxy operator+(size_t i) const;

    X_partProxy operator+(size_t i);

    void set(int v, size_t x, size_t y);

    double get(size_t x, size_t y);

    Matrix operator+(const Matrix &) const;

    Matrix &operator=(const Matrix &a);

    bool operator==(const Matrix &) const;

    bool operator!=(const Matrix &) const;

    Matrix operator*(const Matrix &) const;

    ~Matrix();
};


#endif
