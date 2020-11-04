#include <zconf.h>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFixer.h"
#include "image/repository/ImageRepository.h"
#include "ipc/memory/SharedMemory.h"
#include "log/Logger.h"
#include "signal/SIGINT_Handler.h"
#include "signal/SignalHandler.h"

size_t sizeOfElement(list<Image> &images);

size_t sizeRequired(list<Image> &images);

bool shouldItTakeMoreImages(const SIGINT_Handler &sigint_handler, int iteration);

void destroyAllElements(list<Image> &images, SharedMemory &memory, ImageRepository &imageRepository,
                        ImageQualityFixer &fixer, list<Image> &adjustedImages);

int main() {
    /** Initialing parameters */
    int camerasQuantity = 2;
    cout << "Please enter cameras quantity : ";
    cin >> camerasQuantity;

    string logLevel = "DEBUG";
    cout << "Please enter log level : [DEBUG|INFO] ";
    cin >> logLevel;

    int width = 3;
    cout << "Please enter width : ";
    cin >> width;

    int height = 3;
    cout << "Please enter height : ";
    cin >> width;

    cout << "Process id: " << getpid() << " \n";

    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(width, height))
            .withCamerasQuantity(camerasQuantity)
            .build();

    // event handler para la senial SIGINT (-2)
    SIGINT_Handler sigint_handler;
    // se registra el event handler declarado antes
    SignalHandler::registerHandler(SIGINT, &sigint_handler);

    int iteration = 0;
    while (shouldItTakeMoreImages(sigint_handler, iteration)) {
        try {
            iteration++;
            Logger::getInstance(logLevel)->log("----------------------Taking images----------------------");

            /** Taking some images */
            list<Image> images = observatory.takeImagesCapture();
            Logger::getInstance(logLevel)->log("Initial images value: ", images);

            /** Creating a Shared Memory Buck */
            SharedMemory memory = SharedMemory(sizeRequired(images));
            ImageRepository imageRepository = ImageRepository(sizeOfElement(images));

            /** Saving all images */
            ImageRepository::saveAll(images, memory.getPtrData());

            /** Parallel process */
            ImageQualityFixer fixer = ImageQualityFixer();
            fixer.adjustInParallel(images);
            Logger::getInstance(logLevel)->log("All images were adjusted successfully with shared memory.");

            /** Retrieving adjusted images */
            list<Image> adjustedImages = imageRepository.findAll(images.size(), memory.getPtrData());
            Logger::getInstance(logLevel)->log("Adjusted images value: ", adjustedImages);

            /** Final images */
            Image finalImage = ImageQualityFixer::overlap(adjustedImages);
            Logger::getInstance(logLevel)->log("Final image: " + finalImage.toString());

            /**
             * ********************************************
             *                  FIFO
             * ********************************************
             * */
            /* *
             * list<Image> adjustedImagesWithFIFO = ImageQualityFixer().adjustWithFIFO(images);
             * Logger::getInstance(logLevel)->log("All images were adjusted successfully with FIFO.");
             * Image finalImageWithFIFO = ImageQualityFixer::overlap(adjustedImagesWithFIFO);
             * Logger::getInstance(logLevel)->log("Final image retrieved by FIFO: " + finalImageWithFIFO.toString());
                * */
            destroyAllElements(images, memory, imageRepository, fixer, adjustedImages);
        } catch (std::string &errormessage) {
            std::cout << errormessage << std::endl;
        }
    }

    /** Signal was received and the main process must be closed */
    SignalHandler::destroy();
    observatory.~Observatory();
    Logger::getInstance(logLevel)->log(
            "Process has received a signal or it has reached the maximum of iterations, and then it was finished with status code 0.");
    Logger::getInstance(logLevel)->~Logger();
    return 0;
}


void destroyAllElements(list<Image> &images, SharedMemory &memory, ImageRepository &imageRepository,
                        ImageQualityFixer &fixer, list<Image> &adjustedImages) {
    memory.free(true);
    memory.~SharedMemory();
    imageRepository.~ImageRepository();
    fixer.~ImageQualityFixer();
    for (auto it = adjustedImages.begin(); it != adjustedImages.end(); it++) {
        it.operator*().~Image();
    }
    adjustedImages.clear();
    for (auto it = images.begin(); it != images.end(); it++) {
        it.operator*().~Image();
    }
    images.clear();
}

bool shouldItTakeMoreImages(const SIGINT_Handler &sigint_handler, int iteration) {
    int maxIterationQuantity = 5;
    if (iteration >= maxIterationQuantity)
        return false;
    return sigint_handler.getGracefulQuit() == 0;
}

size_t sizeOfElement(list<Image> &images) {
    return images.begin()->getSerializedSize();
}

size_t sizeRequired(list<Image> &images) {
    return images.size() * sizeOfElement(images);
}