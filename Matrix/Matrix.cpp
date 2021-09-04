#include "Matrix.h"
#include "Proxy.h"
#include <iostream>
#include <cstdio>


Matrix::Matrix() {
    X_Number = 0;
    Y_Number = 0;
    firstM = nullptr;
}

Matrix::Matrix(size_t x, size_t y) {
    X_Number = x;
    Y_Number = y;
    firstM = nullptr;
}

Matrix::Matrix(const Matrix &a) {
    X_Number = a.X_Number;
    Y_Number = a.X_Number;
    if (a.firstM != nullptr) {
        this->firstM = new X_part(a.firstM->x_index);
        X_part *buf11 = a.firstM;
        X_part *buf12 = this->firstM;
        while (true) {
            if (buf11->child != nullptr) {
                buf12->child = new Y_part(buf11->child->y_index, buf11->child->value);
                Y_part *buf21 = buf11->child;
                Y_part *buf22 = buf12->child;
                buf21 = buf21->nextY;
                while (buf21 != nullptr) {
                    buf22->nextY = new Y_part(buf21->y_index, buf21->value);
                    buf22 = buf22->nextY;
                    buf21 = buf21->nextY;
                }
            }
            if (buf11->nextM == nullptr)
                break;
            buf11 = buf11->nextM;
            buf12->nextM = new X_part(buf11->x_index);
            buf12 = buf12->nextM;
        }
    }
}

size_t Matrix::num_rows() const {
    return X_Number;
}

size_t Matrix::num_columns() const {
    return Y_Number;
}

X_part *Matrix::GetFirst() const {
    return firstM;
}

X_partConstProxy Matrix::operator+(size_t i) const {
    X_partConstProxy ret(num_rows(), num_columns(), i, GetFirst(), this);
    while (ret.X_row) {
        if (ret.X_row->x_index == i)
            break;
        ret.X_row = ret.X_row->nextM;
    }
    return ret;
}

X_partProxy Matrix::operator+(size_t i) {
    X_partProxy ret(num_rows(), num_columns());
    ret.x_index = i;
    ret.X_row = GetFirst();
    ret.Buf = this;
    while (ret.X_row) {
        if (ret.X_row->x_index == i)
            break;
        ret.X_row = ret.X_row->nextM;
    }
    return ret;
}

X_partConstProxy Matrix::operator[](size_t i) const {
    return *this->operator+(i);
}

X_partProxy Matrix::operator[](size_t i) {
    return *this->operator+(i);
}

void Matrix::set(int v, size_t x, size_t y) {
    double eps = 0.0000001;
    if (std::abs(v) < eps) return;
    if (!GetFirst()) {
        this->firstM = new X_part(x);
        this->firstM->child = new Y_part(y, v);
    } else {
        X_part *n = GetFirst();
        while (n) {
            if (n->x_index == x) {
                Y_part *k = n->child;
                while (k) {
                    if (k->y_index == y) {
                        k->value = v;
                        return;
                    }
                    k = k->nextY;
                }
                auto *d = new Y_part(y, v);
                d->nextY = n->child;
                n->child = d;
                return;
            }
            n = n->nextM;
        }
        auto *m = new X_part(x);
        m->nextM = this->firstM;
        this->firstM = m;
        this->firstM->child = new Y_part(y, v);
    }
}

Matrix Matrix::operator+(const Matrix &A) const {
    Matrix ret(X_Number, Y_Number);
    try {
        if (X_Number != A.X_Number || Y_Number != A.Y_Number)
            throw "BAD";
        for (size_t i = 0; i < A.X_Number; i++) {
            for (size_t j = 0; j < A.Y_Number; j++) {
                ret[i][j] = this->operator[](i).operator[](j) + A[i][j];
            }
        }
    }
    catch (const char *exception) {
        std::cerr << "Error " << exception << std::endl;
    }
    return ret;
}

Matrix &Matrix::operator=(const Matrix &a) {
    if (this != &a) {
        X_Number = a.X_Number;
        Y_Number = a.X_Number;
        if (firstM != nullptr)
            delete (firstM);
        if (a.firstM != nullptr) {
            this->firstM = new X_part(a.firstM->x_index);
            X_part *buf11 = a.firstM;
            X_part *buf12 = this->firstM;
            while (true) {
                if (buf11->child != nullptr) {
                    buf12->child = new Y_part(buf11->child->y_index, buf11->child->value);
                    Y_part *buf21 = buf11->child;
                    Y_part *buf22 = buf12->child;
                    buf21 = buf21->nextY;
                    while (buf21 != nullptr) {
                        buf22->nextY = new Y_part(buf21->y_index, buf21->value);
                        buf22 = buf22->nextY;
                        buf21 = buf21->nextY;
                    }
                }
                if (buf11->nextM == nullptr)
                    break;
                buf11 = buf11->nextM;
                buf12->nextM = new X_part(buf11->x_index);
                buf12 = buf12->nextM;
            }
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix &A) const {
    double eps = 0.0000001;
    if (this->Y_Number != A.Y_Number && this->X_Number != A.X_Number)
        return false;
    for (size_t i = 0; i < this->X_Number; i++) {
        for (size_t j = 0; j < this->Y_Number; j++) {
            if (std::abs(A[i][j] - this->operator[](i).operator[](j)) > eps)
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &A) const {
    if (this->operator==(A))
        return false;
    return true;
}

Matrix Matrix::operator*(const Matrix &A) const {
    Matrix ret(this->X_Number, A.Y_Number);
    try {
        if (this->Y_Number != A.X_Number)
            throw "BAD";
        for (size_t i = 0; i < this->X_Number; i++) {
            for (size_t j = 0; j < A.Y_Number; j++) {
                int q = 0;
                for (size_t k = 0; k < A.X_Number; k++) {
                    q += this->operator[](i).operator[](k) * A[k][j];
                }
                ret[i][j] = q;
            }
        }
    }
    catch (const char *exception) {
        std::cerr << "Error " << exception << std::endl;
    }
    return ret;
}

Matrix::~Matrix() {
    if (firstM != nullptr) {
        delete firstM;
        firstM = nullptr;
    }
}

double Matrix::get(size_t x, size_t y) {
    return this->operator[](x).operator[](y);
}
