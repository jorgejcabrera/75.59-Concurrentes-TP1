//
// Created by Jorge Cabrera on 24/10/2020.
//

#include <unistd.h>

#include "ImageQualityFixer.h"
#include "../../ipc/memory/SharedMemory.h"
#include "../repository/ImageRepository.h"

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


list<Image> ImageQualityFixer::adjustWithFIFO(list<Image> images) {
    list<Image> adjustedImages;
    for (auto it = images.begin(); it != images.end(); it++) {
        int i = std::distance(images.begin(), it);
        pid_t pid = fork();
        if (pid == 0) {
            Image anImage = ImageRepository::findByPartition(i, it->getSerializedSize());
            adjustedImages.push_back(anImage);
            sleep(rand() % 2);
            exit(0);
        } else {
            ImageRepository::saveToPartition(i, it.operator*());
            wait(nullptr);
        }
    }
    return adjustedImages;
}




