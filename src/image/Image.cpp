//
// Created by Jorge Cabrera on 21/10/2020.
//

#include "Image.h"
#include <utility>
#include <sstream>
#include <vector>

Image::Image(map<int, list<Pixel>> pixels, int id) {
    this->pixels = std::move(pixels);
    this->id = id;
}

map<int, list<Pixel>> *Image::getPixels() {
    return &this->pixels;
}

string Image::toString() {
    stringstream ss;
    ss << "id: " << this->id << "; width: " << this->getPixels()->begin()->second.size() << "; height: "
       << this->getPixels()->size() << endl;
    for (auto &pixel : this->pixels) {
        for (auto &itList : pixel.second) {
            ss << "[" << itList.getRed() << " " << itList.getBlue() << " " << itList.getGreen() << "] ";
        }
        ss << "\n";
    }
    ss << "\n";
    return ss.str();
}

Image Image::overlap(Image image) {
    if (rand() % 2 == 0) {
        return image;
    }
    return *this;
}

void Image::setPixels(map<int, list<Pixel>> pixels) {
    this->pixels = pixels;
}

void Image::setId(int id) {
    this->id = id;
}

int Image::getId() {
    return this->id;
}

Image::Image() = default;

Image::~Image() = default;