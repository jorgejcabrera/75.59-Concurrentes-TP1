//
// Created by Jorge Cabrera on 31/10/2020.
//

#include "ImageRepository.h"
#include "ImageSerializer.h"
#include "../../ipc/fifos/FifoReader.h"
#include "../../ipc/fifos/FifoWriter.h"
#include <sstream>

/**
 * ******************************************************
 * ******************************************************
 * Following methods were implemented through shared memory.
 * ******************************************************
 * ******************************************************
 * */
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

void ImageRepository::saveInPosition(const Image &image, int position, int *ptr) const {
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

string ImageRepository::partitionKey(int i) {
    string filePartitionPrefix = "/tmp/file_";
    stringstream ss;
    ss.clear();
    ss << filePartitionPrefix << i;
    return ss.str();
}

/**
 * ******************************************************
 * ******************************************************
 * Following methods were implemented with FIFO strategy.
 * ******************************************************
 * ******************************************************
 * */
Image ImageRepository::findByPartition(int partition, size_t totalSize) {
    FifoReader readerChannel(ImageRepository::partitionKey(partition));
    int *buffer = new int[totalSize / sizeof(int)];
    readerChannel.start();
    readerChannel.pop(buffer, totalSize);
    Image anImage = ImageSerializer::hydrate(buffer);
    //cout << "[READER] Lei de la paritcion: " << anImage.toString();
    readerChannel.finish();
    return anImage;
}

void ImageRepository::saveToPartition(int partition, Image image) {
    FifoWriter writerChannel(ImageRepository::partitionKey(partition));
    writerChannel.start();
    int *serializedImage = new int[image.getSerializedSize() / sizeof(int)];
    ImageSerializer::serialize(image, serializedImage);
    writerChannel.push(serializedImage, image.getSerializedSize());
    writerChannel.finish();
    writerChannel.destroy();
    //cout << "[WRITER] Escribi a la particion: " << ImageSerializer::hydrate(serializedImage).toString();
}

ImageRepository::~ImageRepository() = default;

ImageRepository::ImageRepository() = default;
