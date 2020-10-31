//
// Created by Jorge Cabrera on 31/10/2020.
//

#include "ImageSerializer.h"
#include "../../observatory/camera/Resolution.h"

Image ImageSerializer::fromBytes(const int *bytes) {
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

int *ImageSerializer::toBytes(Image image) {
    int *bytes;
    bytes[0] = image.getId();
    int width = image.getPixels()->begin()->second.size();
    bytes[1] = width;
    int height = image.getPixels()->size();
    bytes[2] = height;
    int i = 3;
    for (auto &it : *image.getPixels()) {
        for (auto itList = it.second.begin(); itList != it.second.end(); itList++) {
            Pixel pixel = itList.operator*();
            bytes[i] = pixel.getRed();
            bytes[i + 1] = pixel.getBlue();
            bytes[i + 2] = pixel.getGreen();
            i = i + 3;
        }
    }
    return bytes;
}

ImageSerializer::~ImageSerializer() = default;

ImageSerializer::ImageSerializer() = default;
