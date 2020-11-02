//
// Created by Jorge Cabrera on 24/10/2020.
//

#include <unistd.h>

#include "ImageQualityFix.h"
#include "../../memory/SharedMemory.h"
#include "../repository/ImageRepository.h"

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

Image ImageQualityFix::overlap(list<Image> images) {
    int position = rand() % images.size();
    auto it = images.begin();
    std::advance(it, position);
    return it.operator*();
}

void ImageQualityFix::adjustInParallel(list<Image> images) {
    int imageQuantity = images.size();
    int n = imageQuantity;

    for (int i = 0; i < n; ++i) {
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
                imageRepository.saveAtPosition(image, i, memory1.getPtrData());
                sleep(rand() % 2);
                exit(0);
            } catch (std::string &errormessage) {
                std::cerr << errormessage << std::endl;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        wait(nullptr);
    }
}

