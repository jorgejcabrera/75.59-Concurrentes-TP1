//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "ImageBuilder.h"
#include <cstdlib>

ImageBuilder ImageBuilder::withHeight(int height) {
    this->height = height;
    return *this;
}

ImageBuilder ImageBuilder::withWidth(int width) {
    this->width = width;
    return *this;
}

Image ImageBuilder::build() const {
    map<int, list<Pixel>> pixels;
    for (int i = 0; i < this->height; i++) {
        list<Pixel> currentPixels;
        for (int j = 0; j < this->width; j++) {
            currentPixels.emplace_back(Pixel(rand() % 256, rand() % 256, rand() % 256));
        }
        pixels[i] = currentPixels;
    }
    return Image(pixels);
}

ImageBuilder::ImageBuilder() = default;

ImageBuilder::~ImageBuilder() = default;
