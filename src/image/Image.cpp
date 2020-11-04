//
// Created by Jorge Cabrera on 21/10/2020.
//

#include "Image.h"
#include <utility>
#include <sstream>

Image::Image(map<int, list<Pixel>> pixels, int id) {
    this->pixels = std::move(pixels);
    this->id = id;
}

map<int, list<Pixel>> *Image::getPixels() {
    return &this->pixels;
}

string Image::toString() {
    stringstream ss;
    ss << "{ \n id: " << this->id << ",\n width: " << this->getPixels()->begin()->second.size() << ",\n height: "
       << this->getPixels()->size() << ",\n" << " pixels: {\n";
    for (auto &pixel : this->pixels) {
        ss << "     ";
        for (auto &itList : pixel.second) {
            ss << " [" << itList.getRed() << " " << itList.getBlue() << " " << itList.getGreen() << "]";
        }
        ss << "\n";
    }
    ss << "}" << "\n";
    return ss.str();
}

size_t Image::getSerializedSize() {
    return this->getPixels()->size() * this->getPixels()->begin()->second.size() * sizeof(int) * 3 + 3 * sizeof(int);
}

void Image::setPixels(map<int, list<Pixel>> pixels) {
    this->pixels = pixels;
}

void Image::setId(int id) {
    this->id = id;
}

int Image::getId() const {
    return this->id;
}

Image::Image() = default;

Image::~Image() {
    for (auto &pixel : this->pixels) {
        for (auto itRow = pixel.second.begin(); itRow != pixel.second.end(); itRow++) {
            itRow.operator*().~Pixel();
        }
    }
    this->pixels.clear();
}