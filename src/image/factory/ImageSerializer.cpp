//
// Created by Jorge Cabrera on 31/10/2020.
//

#include "ImageSerializer.h"
#include "../../observatory/camera/Resolution.h"
#include "ImageBuilder.h"

Image ImageSerializer::fromBytes(const int *bytes) {
    int offset = 0;
    int width = bytes[offset];
    int height = bytes[offset + 1];
    Resolution resolution = Resolution(width, height);
    offset = 2;
    map<int, list<Pixel>> pixels;
    for (int j = 0; j < height; j++) {
        list<Pixel> rowOfPixels;
        int lastPositionOfRow = (j+1) * width * 3 + 2;
        while (offset < lastPositionOfRow) {
            int red = bytes[offset];
            int blue = bytes[offset + 1];
            int green = bytes[offset + 2];
            offset = offset + 3;
            rowOfPixels.emplace_back(red, blue, green);
        }
        offset = 2 + (j+1) * width * 3 ;
        pixels.emplace(j, rowOfPixels);
    }
    Image image = ImageBuilder().withResolution(resolution).build();
    image.setPixels(pixels);
    return image;
}

int *ImageSerializer::toBytes(Image image) {
    int *bytes;
    int width = image.getPixels()->begin()->second.size();
    bytes[0] = width;
    int height = image.getPixels()->size();
    bytes[1] = height;
    int i = 2;
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
