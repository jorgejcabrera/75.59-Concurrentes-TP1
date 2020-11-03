//
// Created by Jorge Cabrera on 31/10/2020.
//

#include "ImageRepository.h"
#include "../../observatory/camera/Resolution.h"

void ImageRepository::serialize(Image image, int *ptr) {
    ptr[0] = image.getId();
    int width = image.getPixels()->begin()->second.size();
    ptr[1] = width;
    int height = image.getPixels()->size();
    ptr[2] = height;
    int i = 3;
    for (auto &it : *image.getPixels()) {
        for (auto itList = it.second.begin(); itList != it.second.end(); itList++) {
            Pixel pixel = itList.operator*();
            ptr[i] = pixel.getRed();
            ptr[i + 1] = pixel.getBlue();
            ptr[i + 2] = pixel.getGreen();
            i = i + 3;
        }
    }
}

Image ImageRepository::hydrate(const int *bytes) {
    int offset = 0;
    int id = bytes[offset];
    int width = bytes[offset + 1];
    int height = bytes[offset + 2];
    Resolution resolution = Resolution(width, height);
    offset = 3;
    map<int, list<Pixel>> pixels;
    for (int j = 0; j < height; j++) {
        list<Pixel> rowOfPixels;
        int lastPositionOfRow = (j + 1) * width * 3 + 3;
        while (offset < lastPositionOfRow) {
            int red = bytes[offset];
            int blue = bytes[offset + 1];
            int green = bytes[offset + 2];
            offset = offset + 3;
            rowOfPixels.emplace_back(red, blue, green);
        }
        offset = 3 + (j + 1) * width * 3;
        pixels.emplace(j, rowOfPixels);
    }
    Image image = Image();
    image.setPixels(pixels);
    image.setId(id);
    return image;
}

void ImageRepository::saveAll(list<Image> images, int *ptr) {
    int *localPtr = ptr;
    for (auto it = images.begin(); it != images.end(); it++) {
        Image image = it.operator*();
        this->serialize(image, localPtr);
        localPtr = localPtr + image.getSerializedSize();
    }
}

ImageRepository::ImageRepository(size_t sizeOfElement) {
    this->sizeOfElement = sizeOfElement;
}

Image ImageRepository::findByPosition(int position, int *ptr) {
    int *localPtr = ptr + this->sizeOfElement * position;
    return this->hydrate(localPtr);
}

void ImageRepository::saveAtPosition(const Image &image, int position, int *ptr) {
    int *localPtr = ptr + this->sizeOfElement * position;
    this->serialize(image, localPtr);
}

list<Image> ImageRepository::findAll(int totalImages, int *ptr) {
    list<Image> images;
    for (int i = 0; i < totalImages; i++) {
        Image anImage = findByPosition(i, ptr);
        images.push_back(anImage);
    }
    return images;
}

ImageRepository::~ImageRepository() = default;

ImageRepository::ImageRepository() = default;
