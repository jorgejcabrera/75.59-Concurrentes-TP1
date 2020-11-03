#include <zconf.h>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include "image/repository/ImageRepository.h"
#include "ipc/memory/SharedMemory.h"
#include "log/Logger.h"
#include "signal/SIGINT_Handler.h"
#include "signal/SignalHandler.h"

size_t sizeOfElement(list<Image> &images);

size_t sizeRequired(list<Image> &images);

bool shouldTakeMoreImages(const SIGINT_Handler &sigint_handler, int iteration);

int main() {
    /** Initialing parameters */
    int camerasQuantity = 3;
    string logLevel = "DEBUG";
    int width = 3;
    int height = 2;

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
    while (shouldTakeMoreImages(sigint_handler, iteration)) {
        iteration++;
        Logger::getInstance(logLevel)->log("----------------------Taking images----------------------");

        /** Taking some images */
        list<Image> images = observatory.takeImagesCapture();
        Logger::getInstance(logLevel)->log("Initial images value: ", images);

        /** Creating Shared Memory */
        SharedMemory memory = SharedMemory(sizeRequired(images));
        ImageRepository imageRepository = ImageRepository(sizeOfElement(images));

        /** Save all images */
        ImageRepository::saveAll(images, memory.getPtrData());

        /** Concurrency */
        ImageQualityFix().adjustInParallel(images);
        Logger::getInstance(logLevel)->log("All images were adjusted successfully.");

        /** Retrieving adjusted images */
        list<Image> adjustedImages = imageRepository.findAll(images.size(), memory.getPtrData());
        Logger::getInstance(logLevel)->log("Adjusted images value: ", adjustedImages);

        /** Final image */
        Image finalImage = ImageQualityFix::overlap(adjustedImages);
        Logger::getInstance(logLevel)->log("Final image: " + finalImage.toString());

        memory.free();
    }

    /** Signal was received and main process must be closed */
    SignalHandler::destroy();
    Logger::getInstance(logLevel)->log("Process has received a signal and then it was terminated with status code 0");
    return 0;
}

bool shouldTakeMoreImages(const SIGINT_Handler &sigint_handler, int iteration) {
    int maxIterationQuantity = 100;
    if (iteration > maxIterationQuantity)
        return false;
    return sigint_handler.getGracefulQuit() == 0;
}

size_t sizeOfElement(list<Image> &images) { return images.begin()->getSerializedSize(); }

size_t sizeRequired(list<Image> &images) {
    return images.size() * sizeOfElement(images);
}