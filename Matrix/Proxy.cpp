#include "Proxy.h"
#include "Matrix.h"
X_partProxy::X_partProxy(size_t i, size_t i1) {
    this->X_row = nullptr;
    this->Buf = nullptr;
    x_size = i;
    y_size = i1;
    x_index = 0;
}

X_partProxy::X_partProxy(const X_partProxy &a) {
    this->X_row = a.X_row;
    this->Buf = a.Buf;
    x_size = a.x_size;
    y_size = a.y_size;
    x_index = a.x_index;
}

Y_partProxy::Y_partProxy(X_partProxy *pProxy, size_t i) {
    this->FoundRow = pProxy;
    this->Found = nullptr;
    this->y_index = i;
}

X_partConstProxy::X_partConstProxy(size_t i, size_t i1, size_t i2, X_part *q, const Matrix *a) {
    x_size = i;
    y_size = i1;
    x_index = i2;
    Buf = a;
    X_row = q;
}

X_partConstProxy::X_partConstProxy(const X_partConstProxy &a) {
    this->X_row = a.X_row;
    this->Buf = a.Buf;
    x_size = a.x_size;
    y_size = a.y_size;
    x_index = a.x_index;
}

Y_partConstProxy::Y_partConstProxy(const X_partConstProxy *pProxy, size_t i) {
    this->FoundRow = pProxy;
    this->y_index = i;
    this->Found = nullptr;
}

Y_partProxy X_partProxy::operator+(size_t i) {
    Y_partProxy n(this, i);
    n.y_index = i;
    if (n.FoundRow->X_row == nullptr)
        return n;
    n.Found = n.FoundRow->X_row->child;
    while (n.Found) {
        if (n.Found->y_index == i)
            return n;
        n.Found = n.Found->nextY;
    }
    return n;
}

Y_partConstProxy X_partConstProxy::operator+(size_t i) const {
    Y_partConstProxy n(this, i);
    if (n.FoundRow->X_row == nullptr)
        return n;
    n.Found = n.FoundRow->X_row->child;
    while (n.Found) {
        if (n.Found->y_index == i)
            return n;
        n.Found = n.Found->nextY;
    }
    return n;
}

Y_partProxy X_partProxy::operator[](size_t i) {
    return this->operator+(i);
}

X_partProxy X_partProxy::operator*() {
    return *this;
}

Y_partProxy Y_partProxy::operator*() {
    return *this;
}

Y_partConstProxy Y_partConstProxy::operator*() {
    return *this;
}

X_partConstProxy X_partConstProxy::operator*() {
    return *this;
}

Y_partConstProxy X_partConstProxy::operator[](size_t i) const {
    return this->operator+(i);
}

Y_partProxy::operator int() const {
    if (Found == nullptr && this->FoundRow->x_index <= this->FoundRow->x_size &&
        this->y_index <= this->FoundRow->y_size) {
        return 0;
    }
    if (this->Found==nullptr)
        return -1;
    int q = this->Found->value;
    return q;
}

Y_partConstProxy::operator int() const {
    if (this->Found == nullptr && this->FoundRow->x_index <= this->FoundRow->x_size && this->y_index <= this->FoundRow->y_size) {
        return 0;
    }
    if (this->Found==nullptr)
        return -1;
    int q = this->Found->value;
    return q;
}

Y_partProxy &Y_partProxy::operator=(int a) {
    if (this->Found == nullptr && this->FoundRow->x_index < this->FoundRow->x_size && this->y_index < this->FoundRow->y_size) {
        this->FoundRow->Buf->set(a, this->FoundRow->x_index, this->y_index);
    } else
        this->Found->value = a;
    return *this;
}