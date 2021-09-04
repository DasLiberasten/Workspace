#include <sys/param.h>
#include "IterableSparseMatrix.h"
#include "Matrix.h"

int IterableSparseMatrix::FindMax() const{
    int mas[GetSize()];
    for (size_t i = 0; i < GetSize(); i++)
        mas[i]=0;
    for (size_t i = 0; i < GetSize(); i++) {
        for (size_t j = 0; j < GetSize(); j++) {
            if ((*Data)[i][j] > 0) {
                mas[i] += 1;
                mas[j] += 1;
            }
        }
    }
    int maxNum = mas[0];
    for (size_t i = 1; i < GetSize(); i++) {
        if (maxNum <= mas[i]) {
            maxNum = mas[i];
        }
    }
    return maxNum;
}

size_t IterableSparseMatrix::GetSize() const{
    return size;
}

IterableSparseMatrix::IterableSparseMatrix(size_t a) {
    size = a;
    Data = new Matrix(a, a);
}

IterableSparseMatrix::~IterableSparseMatrix() {
    delete Data;
}

int IterableSparseMatrix::GetVal(int a1, int a2) const{
    return (*Data)[a1][a2];
}

void IterableSparseMatrix::SetEdge(int a1, int a2, int a3) {
    (*Data)[a1][a2] = a3;
}

void IterableSparseMatrix::RemoveEdge(int a1, int a2) {
        (*Data)[a1][a2] = 0;
}

void IterableSparseMatrix::SetSize(size_t a) {
    this->size = a;
}

IteratorRow IterableSparseMatrix::IterateRows(size_t row) const {
    size_t column = -1;
    while (++column < GetSize() && !GetVal(row, column));
    return IteratorRow(row, column, *this);
}


IteratorRow IterableSparseMatrix::EndRow(size_t row) const {
    return IteratorRow(row, GetSize(), *this);
}


IteratorColumn IterableSparseMatrix::IterateColumns(size_t column) const {
    size_t row = -1;
    while (++row < GetSize() && !GetVal(row, column));
    return IteratorColumn(row, column, *this);
}


IteratorColumn IterableSparseMatrix::EndColumn(size_t column) const {
    return IteratorColumn(GetSize(), column, *this);

}

size_t IterableSparseMatrix::FindDiam() const {
    size_t n = GetSize();
    int **buf = new int *[n];
    for (size_t i = 0; i < n; i++)
        buf[i] = new int [n];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++) {
            buf[i][j] = (*Data)[i][j];
            if (buf[i][j] == 0)
                buf[i][j] = -1;
        }
    }
    for (size_t k = 0; k < n; k++)
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++){
                if (i != j && buf[i][k] != -1 && buf[k][j] != -1 && buf[i][j] == -1)
                    buf[i][j] = buf[i][k] + buf[k][j];
                if (i != j && buf[i][k] != -1 && buf[k][j] != -1 && buf[i][j] != -1)
                    buf[i][j] = MIN(buf[i][j], buf[i][k] + buf[k][j]);
            }

    int max = buf[0][1];
    for(size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++) {
            if(buf[i][j] > max)
                max = buf[i][j];
        }
    }
    for (size_t i = 0; i < n; i++)
        delete[] buf[i];
    delete[] buf;
    return max;
}
