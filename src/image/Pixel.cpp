//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "Pixel.h"
#include <cstdlib>     /* srand, rand */
#include <cmath>       /* pow */

Pixel::Pixel(int red, int blue, int green) {
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void Pixel::adjust() {
    if ((rand() % 10) % 2 == 0) {
        this->red = this->red - 1;
        this->blue = this->blue - 1;
        this->green = this->green - 1;
    } else {
        this->red = pow(this->red, 2);
        this->blue = pow(this->blue, 2);
        this->green = pow(this->green, 2);
    }
}

int Pixel::getBlue() const {
    return this->blue;
}

int Pixel::getRed() const {
    return this->red;
}

int Pixel::getGreen() const {
    return this->green;
}

Pixel::~Pixel() = default;
