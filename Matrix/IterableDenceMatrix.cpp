#include <sys/param.h>
#include "IterableDenceMatrix.h"

size_t IterableDenceMatrix::GetSize() const{
    return size;
}

int IterableDenceMatrix::FindMax() const{
    int mas[GetSize()];
    for (size_t i = 1; i < GetSize(); i++) {
        for (size_t j = 1; j < GetSize(); j++) {
            if (Data[i][j]>0) {
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

IterableDenceMatrix::IterableDenceMatrix(size_t a) {
    Data = new int *[a];
    for (size_t count = 0; count < a; count++)
        Data[count] = new int[a];
    size = a;
}

IterableDenceMatrix::~IterableDenceMatrix() {
    for (size_t i = 0; i < size; i++)
        delete[] Data[i];
    delete[] Data;
}

int IterableDenceMatrix::GetVal(int a1, int a2) const{
    return Data[a1][a2];
}

void IterableDenceMatrix::SetEdge(int a1, int a2, int a3) {
    Data[a1][a2] = a3;
}

void IterableDenceMatrix::RemoveEdge(int a1, int a2) {
        Data[a1][a2]=0;
}

void IterableDenceMatrix::SetSize(size_t a) {
    this->size = a;
}

IteratorRow IterableDenceMatrix::IterateRows(size_t row) const {
    size_t column = -1;
    while (++column < GetSize() && !GetVal(row, column));
    return IteratorRow(row, column, *this);
}


IteratorRow IterableDenceMatrix::EndRow(size_t row) const {
    return IteratorRow(row, GetSize(), *this);
}


IteratorColumn IterableDenceMatrix::IterateColumns(size_t column) const {
    size_t row = -1;
    while (++row < GetSize() && !GetVal(row, column));
    return IteratorColumn(row, column, *this);
}


IteratorColumn IterableDenceMatrix::EndColumn(size_t column) const {
    return IteratorColumn(GetSize(), column, *this);

}

size_t IterableDenceMatrix::FindDiam() const {
    size_t n = GetSize();
    int **buf = new int *[n];
    for (size_t i = 0; i < n; i++)
        buf[i] = new int [n];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++) {
            buf[i][j] = Data[i][j];
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

