#include <iostream>
#include <unistd.h>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include <fstream>
#include <vector>
#include "MemoriaCompartida.h"
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

void adjustImagesInParallel(list<Image> &images) {
    int imageQuantity = images.size();
    int n = imageQuantity;

    for (int i = 0; i < n; ++i) {
        pid_t procId = fork();
        if (procId < 0) {
            perror("fork");
            abort();
        } else if (procId == 0) {
            try {
                cout << "I am a child. My pid is: " << getpid() << " my ppid is: " << getppid() << " \n";
                // Memoria compartida
                SharedMemory memory1 = SharedMemory();
                Image image = ImageRepository().read(memory1.getPtrData());

                cout << "Imagen reconstruida en proceso: " << image.toString() << endl;

                ImageQualityFix().adjust(&image);
                ImageRepository().save(image, memory1.getPtrData());

                exit(0);
            } catch (std::string &errormessage) {
                std::cerr << errormessage << std::endl;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }
}

int main() {
    // Memoria compartida
    SharedMemory memory = SharedMemory();
    ImageRepository imageRepository = ImageRepository();

    // Take some photos
    int camerasQuantity = 1;
    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(3, 3))
            .withCamerasQuantity(camerasQuantity)
            .build();
    list<Image> images = observatory.takeImagesCapture();

    // Save an image
    Image anImage = images.begin().operator*();
    cout << "An image is: " << anImage.toString() << endl;
    imageRepository.save(anImage, memory.getPtrData());

    // Concurrencia
    // adjustImagesInParallel(images);

    // Valido
    Image newImage = imageRepository.read(memory.getPtrData());
    cout << "The final image is: " << newImage.toString() << endl;

    // TODO esto se hace al final para esto hay que usar señales
    //Image finalImage = ImageQualityFix().overlap(&images);

    return 0;
}

/**
 * https://stackoverflow.com/questions/876605/multiple-child-memory
 * */