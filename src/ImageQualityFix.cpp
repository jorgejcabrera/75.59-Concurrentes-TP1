//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "ImageQualityFix.h"

ImageQualityFix::ImageQualityFix() = default;

ImageQualityFix::~ImageQualityFix() = default;

void ImageQualityFix::adjust(Image *image) {
    map<int, list<Pixel>> *pixels = image->getPixels();
    for (auto &listOfPixels : *pixels) {
        for (auto &pixel : listOfPixels.second) {
            pixel.adjust();
        }
    }
}
