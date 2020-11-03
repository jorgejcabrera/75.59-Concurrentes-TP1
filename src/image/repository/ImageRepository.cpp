//
// Created by Jorge Cabrera on 31/10/2020.
//

#include "ImageRepository.h"
#include "ImageSerializer.h"

void ImageRepository::saveAll(list<Image> images, int *ptr) {
    int *localPtr = ptr;
    for (auto it = images.begin(); it != images.end(); it++) {
        Image image = it.operator*();
        ImageSerializer::serialize(image, localPtr);
        localPtr = localPtr + image.getSerializedSize();
    }
}

ImageRepository::ImageRepository(size_t sizeOfElement) {
    this->sizeOfElement = sizeOfElement;
}

Image ImageRepository::findByPosition(int position, int *ptr) const {
    int *localPtr = ptr + this->sizeOfElement * position;
    return ImageSerializer::hydrate(localPtr);
}

void ImageRepository::saveAtPosition(const Image &image, int position, int *ptr) const {
    int *localPtr = ptr + this->sizeOfElement * position;
    ImageSerializer::serialize(image, localPtr);
}

list<Image> ImageRepository::findAll(int totalImages, int *ptr) const {
    list<Image> images;
    for (int i = 0; i < totalImages; i++) {
        Image anImage = findByPosition(i, ptr);
        images.push_back(anImage);
    }
    return images;
}

ImageRepository::~ImageRepository() = default;

ImageRepository::ImageRepository() = default;
