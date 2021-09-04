#include "Iterators.h"
#include "IGraph.h"
IteratorRow & IteratorRow::operator++() {
    while (Matrix.GetVal(this->row, this->column) != -1 && ++(this->column) < Matrix.GetSize() && !Matrix.GetVal(this->row, this->column));
    return *this;
}

IteratorColumn & IteratorColumn::operator++() {
    while (Matrix.GetVal(this->row, this->column) != -1 && ++(this->row) < Matrix.GetSize() && !Matrix.GetVal(this->row, this->column));
    return *this;
}

bool IteratorRow::operator==(const IteratorRow & it) const {
    return (this->row == it.row && this->column == it.column && &(this->Matrix) == &it.Matrix);
}


bool IteratorColumn::operator==(const IteratorColumn & it) const {
    return (this->row == it.row && this->column == it.column && &(this->Matrix) == &it.Matrix);
}

bool IteratorRow::operator!=(const IteratorRow & it) const {
    return !(*this == it);
}

bool IteratorColumn::operator!=(const IteratorColumn & it) const {
    return !(*this == it);
}

int IteratorRow::operator*() const {
    return Matrix.GetVal(this->row, this->column);
}

int IteratorColumn::operator*() const {
    return Matrix.GetVal(this->row, this->column);
}
