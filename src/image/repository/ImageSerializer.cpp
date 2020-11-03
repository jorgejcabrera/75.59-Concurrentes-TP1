//
// Created by Jorge Cabrera on 03/11/2020.
//

#include "ImageSerializer.h"
#include "../../observatory/camera/Resolution.h"

ImageSerializer::ImageSerializer() = default;

ImageSerializer::~ImageSerializer() = default;

void ImageSerializer::serialize(Image image, int *ptr) {
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

Image ImageSerializer::hydrate(const int *bytes) {
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
