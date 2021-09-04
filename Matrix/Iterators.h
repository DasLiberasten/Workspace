#ifndef TEHRAN_1943_ITERATORS_H
#define TEHRAN_1943_ITERATORS_H

#include <cstdio>

class IGraph;

class IteratorColumn {
    size_t row;
    size_t column;
    const IGraph &Matrix;
public:
    IteratorColumn(size_t _row, size_t _column, const IGraph &m) : row(_row), column(_column), Matrix(m) {};
    IteratorColumn &operator++();
    bool operator==(const IteratorColumn &) const;
    bool operator!=(const IteratorColumn &) const;
    int operator*() const;
};


class IteratorRow {
    size_t row;
    size_t column;
    const IGraph &Matrix;
public:
    IteratorRow( size_t _row, size_t _column, const IGraph &m) : row(_row), column(_column), Matrix(m) {};
    IteratorRow &operator++();
    bool operator==(const IteratorRow &) const;
    bool operator!=(const IteratorRow &) const;
    int operator*() const;
};

#endif
