//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "Resolution.h"

Resolution::~Resolution() = default;

Resolution::Resolution(int width, int height) {
    this->width = width;
    this->height = height;
}

int Resolution::getWidth() {
    return this->width;
}

int Resolution::getHeight() {
    return this->height;
}

Resolution::Resolution() = default;
