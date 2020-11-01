#include <iostream>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include <fstream>
#include <vector>
#include "image/repository/ImageRepository.h"
#include "memory/SharedMemory.h"

void printImages(list<Image> list) {
    for (auto &it : list) {
        cout << it.toString();
    }
}

ofstream getLogger() {
    ofstream log;
    log.open("/Users/jorge.cabrera/workspace/Facultad/75.59-Concurrentes-TP1/log.txt");
    return log;
}

int main() {
    // Taking some photos
    int camerasQuantity = 3;
    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(5, 5))
            .withCamerasQuantity(camerasQuantity)
            .build();
    list<Image> images = observatory.takeImagesCapture();

    // Create Shared memory
    SharedMemory memory = SharedMemory(images.size());
    ImageRepository imageRepository = ImageRepository(images.begin()->getSerializedSize());

    // Save all images
    imageRepository.saveAll(images, memory.getPtrData());

    // Concurrencia
    ImageQualityFix().adjustInParallel(images);

    // TODO esto se hace al final para esto hay que usar señales
    //Image finalImage = ImageQualityFix().overlap(&images);

    return 0;
}