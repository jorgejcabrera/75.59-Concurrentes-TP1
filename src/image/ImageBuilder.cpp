//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "ImageBuilder.h"
#include <cstdlib>

Image ImageBuilder::build() const {
    map<int, list<Pixel>> pixels;
    Resolution res = this->resolution;
    for (int i = 0; i < res.getHeight(); i++) {
        list<Pixel> currentPixels;
        for (int j = 0; j < res.getWidth(); j++) {
            currentPixels.emplace_back(Pixel(rand() % 256, rand() % 256, rand() % 256));
        }
        pixels[i] = currentPixels;
    }
    return Image(pixels);
}

ImageBuilder ImageBuilder::withResolution(Resolution resolution) {
    this->resolution = resolution;
    return *this;
}

ImageBuilder::ImageBuilder() = default;

ImageBuilder::~ImageBuilder() = default;
