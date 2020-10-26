#include <iostream>
#include <unistd.h>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include <fstream>

void printImages(list<Image> list);

ofstream getLogger() {
    ofstream log;
    log.open("/Users/jorge.cabrera/workspace/Facultad/75.59-Concurrentes-TP1/log.txt");
    return log;
}

void adjustImagesInParallel(list<Image> &images) {
    ofstream log = getLogger();
    int imageQuantity = images.size();
    pid_t pids[imageQuantity];
    int n = imageQuantity;
    for (int i = 0; i < n; ++i) {
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

int main() {
    int camerasQuantity = 2;
    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(2, 2))
            .withCamerasQuantity(camerasQuantity)
            .build();

    list<Image> images = observatory.takeImagesCapture();
    adjustImagesInParallel(images);
    Image finalImage = ImageQualityFix().overlap(&images);
    return 0;
}

void printImages(list<Image> list) {
    for (auto &it : list) {
        cout << it.toString();
    }
}





/**
 * https://stackoverflow.com/questions/876605/multiple-child-process
 * */