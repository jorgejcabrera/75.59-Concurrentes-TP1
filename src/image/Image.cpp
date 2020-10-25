//
// Created by Jorge Cabrera on 21/10/2020.
//

#include "Image.h"

#include <utility>
#include<sstream>

Image::Image(map<int, list<Pixel>> pixels) {
    this->pixels = std::move(pixels);
}

map<int, list<Pixel>> *Image::getPixels() {
    return &this->pixels;
}

string Image::toString() {
    stringstream ss;
    for (auto it = this->pixels.begin(); it != this->pixels.end(); it++) {
        for (auto itList = it->second.begin(); itList != it->second.end(); itList++) {
            ss << "[" << itList->getBlue() << " " << itList->getRed() << " " << itList->getGreen() << "] ";
        }
        ss << "\n";
    }
    return ss.str();
}

Image::~Image() = default;