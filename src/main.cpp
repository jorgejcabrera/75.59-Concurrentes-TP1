#include <iostream>
#include <unistd.h>
#include "ObservatoryBuilder.h"
#include "ImageQualityFix.h"
#include <fstream>

ofstream getLogger();

void processImagesInParallel(int camerasQuantity, list<Image> &images);

int main() {
    int camerasQuantity = 2;
    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(2, 2))
            .withCamerasQuantity(camerasQuantity)
            .build();

    list<Image> images = observatory.takeImagesCapture();
    ofstream log = getLogger();
    processImagesInParallel(camerasQuantity, images);

    log.close();
    return 0;
}

void processImagesInParallel(int camerasQuantity, list<Image> &images) {
    pid_t pids[camerasQuantity];
    for (int i = 0; i < camerasQuantity; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            cout << "I am a child. My pid is: " << getpid() << " my ppid is: " << getppid() << " \n";
            auto it = images.begin();
            advance(it, i);
            ImageQualityFix().adjust(it.operator->());
            exit(0);
        }
    }
}


ofstream getLogger() {
    ofstream log;
    log.open("/Users/jorge.cabrera/workspace/Facultad/75.59-Concurrentes-TP1/log.txt");
    return log;
}


/**
 * https://stackoverflow.com/questions/876605/multiple-child-process
 * */