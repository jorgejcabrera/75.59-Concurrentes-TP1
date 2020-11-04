//
// Created by Jorge Cabrera on 24/10/2020.
//

#include <unistd.h>

#include "ImageQualityFixer.h"
#include "../../ipc/memory/SharedMemory.h"
#include "../repository/ImageRepository.h"
#include "../../ipc/fifos/FifoWriter.h"
#include "../../ipc/fifos/FifoReader.h"
#include "../repository/ImageSerializer.h"
#include <sstream>

ImageQualityFixer::ImageQualityFixer() = default;

ImageQualityFixer::~ImageQualityFixer() = default;

void ImageQualityFixer::adjust(Image *image) {
    map<int, list<Pixel>> *pixels = image->getPixels();
    for (auto &listOfPixels : *pixels) {
        for (auto &pixel : listOfPixels.second) {
            pixel.adjust();
        }
    }
}

Image ImageQualityFixer::overlap(list<Image> images) {
    int position = rand() % images.size();
    auto it = images.begin();
    std::advance(it, position);
    return it.operator*();
}

void ImageQualityFixer::adjustInParallel(list<Image> images) {
    int imageQuantity = images.size();

    for (int i = 0; i < imageQuantity; ++i) {
        pid_t procId = fork();
        if (procId < 0) {
            perror("fork");
            abort();
        } else if (procId == 0) {
            try {
                /*cout << "I am a child. My pid is: " << getpid() << " my ppid is: " << getppid() << ", element: " << i
                     << " \n";*/
                SharedMemory memory1 = SharedMemory(images.size());
                ImageRepository imageRepository = ImageRepository(images.begin()->getSerializedSize());
                Image image = imageRepository.findByPosition(i, memory1.getPtrData());
                this->adjust(&image);
                imageRepository.saveInPosition(image, i, memory1.getPtrData());
                sleep(rand() % 2);
                exit(0);
            } catch (std::string &errormessage) {
                std::cerr << errormessage << std::endl;
            }
        }
    }

    for (int i = 0; i < imageQuantity; ++i) {
        wait(nullptr);
    }
}

void ImageQualityFixer::writeInFile(string file, Image image) {
    FifoWriter writerChannel(file);
    writerChannel.start();
    int *serializedImage = new int[image.getSerializedSize() / sizeof(int)];
    ImageSerializer::serialize(image, serializedImage);
    writerChannel.push(serializedImage, image.getSerializedSize());
    writerChannel.finish();
    writerChannel.destroy();
}

Image ImageQualityFixer::readFromFile(string file, size_t totalSize) {
    FifoReader readerChannel(file);
    int *buffer = new int[totalSize / sizeof(int)];
    readerChannel.start();
    readerChannel.pop(buffer, totalSize);
    Image anImage = ImageSerializer::hydrate(buffer);
    readerChannel.finish();
    return anImage;
}


string ImageQualityFixer::fileName(int i) {
    string filePartitionPrefix = "/tmp/file_";
    stringstream ss;
    ss.clear();
    ss << filePartitionPrefix << i;
    return ss.str();
}

list<Image> ImageQualityFixer::adjustWithFIFO(list<Image> images) {
    list<Image> adjustedImages;
    for (auto it = images.begin(); it != images.end(); it++) {
        int i = std::distance(images.begin(), it);
        pid_t pid = fork();
        if (pid == 0) {
            string fileName = this->fileName(i);
            Image anImage = this->readFromFile(fileName, it->getSerializedSize());
            adjustedImages.push_back(anImage);
            sleep(rand() % 2);
            exit(0);
        } else {
            string fileName = this->fileName(i);
            writeInFile(fileName, it.operator*());
            wait(nullptr);
        }
    }
    return adjustedImages;
}




