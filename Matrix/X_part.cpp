#include "X_part.h"

X_part::X_part(size_t x) {
    x_index = x;
    nextM = nullptr;
    child = nullptr;
}

X_part::~X_part() {
    if (this->nextM != nullptr) {
        delete (this->nextM);
        this->nextM = nullptr;
    }
    if (this->child != nullptr) {
        delete (this->child);
        this->child = nullptr;
    }
}