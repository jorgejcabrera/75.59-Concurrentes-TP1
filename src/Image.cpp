//
// Created by Jorge Cabrera on 21/10/2020.
//

#include "Image.h"

Image::Image(int height, int width) {
    this->height = height;
    this->width = width;
}

std::pair<int, int> Image::pixel() {
    return std::pair<int, int>(this->height, this->width);
}

Image::~Image() {

}