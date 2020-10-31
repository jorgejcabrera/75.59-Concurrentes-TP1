#include <iostream>
#include <unistd.h>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include <fstream>
#include <vector>
#include "MemoriaCompartida.h"
#include "image/factory/ImageSerializer.h"

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
                string filePath("/bin/ls");
                MemoriaCompartida<int> memory(filePath, 'A');

                //char *result = memory.read();
                //Image *anImagge = ImageBuilder().build().deserialize(result);
                //cout << "Hijo : leo el numero " << anImagge->toString();

                //ImageQualityFix().adjust(anImagge);
                //cout << "Hijo : modifico la imagen a " << anImagge->toString();
                memory.write(2);

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
    int camerasQuantity = 1;
    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(3, 3))
            .withCamerasQuantity(camerasQuantity)
            .build();

    list<Image> images = observatory.takeImagesCapture();
    Image anImage = images.begin().operator*();
    cout << "Imagen inicial: " << anImage.toString() ;


    int* bytes = ImageSerializer().toBytes(anImage);
    Image newImage = ImageSerializer().fromBytes(bytes);
    cout << "Imagen reconstruida: " << newImage.toString() ;

    /** memoria compartida
    * string filePath("/bin/ls");
    * MemoriaCompartida<vector<char>> memory(filePath, 'A');
    * */


    /** Concurrencia
    * adjustImagesInParallel(images);
    * */

    // TODO esto se hace al final para esto hay que usar señales
    //Image finalImage = ImageQualityFix().overlap(&images);

    return 0;
}

/**
 * https://stackoverflow.com/questions/876605/multiple-child-process
 * */