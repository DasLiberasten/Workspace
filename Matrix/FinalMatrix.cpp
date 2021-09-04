#include <iostream>
#include "FinalMatrix.h"
#include "IterableSparseMatrix.h"
#include "IterableDenceMatrix.h"
using namespace std;
FinalMatrix::FinalMatrix(size_t a) {
    Matrix = new IterableSparseMatrix(a);
    fullness = 0;
    type = false;
}

FinalMatrix::~FinalMatrix() {
    delete Matrix;
}

size_t FinalMatrix::GetSize() const{
    return Matrix->GetSize();
}

int FinalMatrix::FindMax() const{
    return Matrix->FindMax();
}

int FinalMatrix::GetVal(int a1, int a2) const {
    return this->Matrix->GetVal(a1, a2);
}

void FinalMatrix::Sparce_to_dence() {
    auto *buf = new IterableDenceMatrix(GetSize());
    for (size_t i = 0; i < GetSize(); i++) {
        for (size_t j = 0; j < GetSize(); j++) {
            buf->SetEdge(i, j, this->Matrix->GetVal(i, j));
        }
    }
    delete (this->Matrix);
    this->Matrix = buf;
}

void FinalMatrix::Dence_to_sparse() {
    auto *buf = new IterableSparseMatrix(GetSize());
    for (size_t i = 0; i < GetSize(); i++) {
        for (size_t j = 0; j < GetSize(); j++) {
            buf->SetEdge(i, j, this->Matrix->GetVal(i, j));
        }
    }
    delete (this->Matrix);
    this->Matrix = buf;
}

void FinalMatrix::SetEdge(int a1, int a2, int a3) {
    if(this->Matrix->GetVal(a1,a2)==0)
        fullness++;
    this->Matrix->SetEdge(a1, a2, a3);
    if ((2*fullness>this->Matrix->GetSize()*this->Matrix->GetSize()) && !type) {
        this->Sparce_to_dence();
        type = true;
    }
}

void FinalMatrix::RemoveEdge(int a1, int a2) {
        fullness--;
    this->Matrix->RemoveEdge(a1,a2);
    if ((2*fullness<this->Matrix->GetSize()*this->Matrix->GetSize()) && type) {
        this->Dence_to_sparse();
        type = false;
    }
}

void FinalMatrix::SetSize(size_t a) {
    this->Matrix->SetSize(a);
}

IteratorRow FinalMatrix::IterateRows(size_t row) const {
    return this->Matrix->IterateRows(row);
}


IteratorRow FinalMatrix::EndRow(size_t row) const {
    return this->Matrix->EndRow(row);
}


IteratorColumn FinalMatrix::IterateColumns(size_t column) const {
    return this->Matrix->IterateColumns(column);
}


IteratorColumn FinalMatrix::EndColumn(size_t column) const {
    return this->Matrix->EndColumn(column);

}

size_t FinalMatrix::FindDiam() const {
    return this->Matrix->FindDiam();
}
