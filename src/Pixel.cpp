//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "Pixel.h"

Pixel::Pixel(int red, int blue, int green) {
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void Pixel::adjust() {
    this->red = this->red - 1;
    this->blue = this->blue - 1;
    this->green = this->green - 1;
}

int Pixel::getBlue() {
    return this->blue;
}

int Pixel::getRed() {
    return this->red;
}

int Pixel::getGreen() {
    return this->green;
}

Pixel::~Pixel() = default;
