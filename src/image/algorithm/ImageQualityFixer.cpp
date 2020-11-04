//
// Created by Jorge Cabrera on 24/10/2020.
//

#include <unistd.h>

#include "ImageQualityFixer.h"
#include "../../ipc/memory/SharedMemory.h"
#include "../repository/ImageRepository.h"
#include "../../ipc/fifos/FifoEscritura.h"
#include "../../ipc/fifos/FifoLectura.h"
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

void ImageQualityFixer::writeInFile(string archivo, Image image) {
    FifoEscritura canalDeEscritura(archivo);
    canalDeEscritura.abrir();
    int *serializedImage = new int[image.getSerializedSize() / sizeof(int)];
    ImageSerializer::serialize(image, serializedImage);
    canalDeEscritura.escribir(serializedImage, image.getSerializedSize());
    std::cout << "[Escritor] Escribi el mensaje en el fifo: " << ImageSerializer::hydrate(serializedImage).toString()
              << std::endl;
    canalDeEscritura.cerrar();
    canalDeEscritura.eliminar();
}

Image ImageQualityFixer::readFromFile(string file, size_t totalSize) {
    FifoLectura canalDeLectura(file);
    int *buffer = new int[totalSize / sizeof(int)];
    canalDeLectura.abrir();
    canalDeLectura.leer(buffer, totalSize);
    Image anImage = ImageSerializer::hydrate(buffer);
    canalDeLectura.cerrar();
    return anImage;
}


string ImageQualityFixer::fileName(string prefix, int i) {
    stringstream ss;
    ss.clear();
    ss << prefix << i;
    return ss.str();
}

list<Image> ImageQualityFixer::adjustWithFIFO(list<Image> images) {
    list<Image> adjustedImages;
    for (auto it = images.begin(); it != images.end(); it++) {
        int i = std::distance(images.begin(), it);
        string filePartitionPrefix = "/tmp/file_";
        pid_t pid = fork();
        if (pid == 0) {
            string fileName = this->fileName(filePartitionPrefix, i);
            Image anImage = this->readFromFile(fileName, it->getSerializedSize());
            cout << "[Hijo] se encontro la imagen: " << i << " " << anImage.toString() << endl;
            sleep(rand() % 2);
            exit(0);
        } else {
            stringstream ss;
            ss.clear();
            ss << filePartitionPrefix << i;
            writeInFile(ss.str(), it.operator*());

            wait(nullptr);
            //std::cout << "[Escritor] Se escribio en it: " << i << " " << it->toString() << std::endl;
        }
    }
    return adjustedImages;
}




