#include "Y_part.h"

Y_part::Y_part() {
    nextY = nullptr;
    y_index = 0;
    value = 0;
}

Y_part::Y_part(size_t y, int val) {
    nextY = nullptr;
    y_index = y;
    value = val;
}

Y_part::~Y_part() {
    if (this->nextY != nullptr) {
        delete (this->nextY);
        this->nextY = nullptr;
    }
}
