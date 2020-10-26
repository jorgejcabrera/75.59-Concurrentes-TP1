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

Image ImageQualityFix::overlap(list<Image> *images) {
    if (images->size() <= 1) {
        return *images->begin();
    }
    Image overlappedImage;
    for (auto it = images->begin(); it.operator++() != images->end(); it++) {
        overlappedImage = overlappedImage.overlap(*it.operator->());
    }
}
