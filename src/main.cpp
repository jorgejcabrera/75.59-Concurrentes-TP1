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

int main() {
    /** Initialing parameters */
    int camerasQuantity = 2;
    string logLevel = "DEBUG";
    int width = 5;
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
    while (shouldItTakeMoreImages(sigint_handler, iteration)) {
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
        ImageQualityFixer().adjustInParallel(images);
        Logger::getInstance(logLevel)->log("All images were adjusted successfully.");

        /** FIFO */
        //list<Image> adjustedImages = ImageQualityFixer().adjustWithFIFO(images);
        //Logger::getInstance(logLevel)->log("All images were adjusted successfully.");

        /** Retrieving adjusted images */
        list<Image> adjustedImages = imageRepository.findAll(images.size(), memory.getPtrData());
        Logger::getInstance(logLevel)->log("Adjusted images value: ", adjustedImages);

        /** Final image */
        Image finalImage = ImageQualityFixer::overlap(adjustedImages);
        Logger::getInstance(logLevel)->log("Final image: " + finalImage.toString());

        memory.free();
    }

    /** Signal was received and the main process must be closed */
    SignalHandler::destroy();
    Logger::getInstance(logLevel)->log(
            "Process has received a signal or it has reached the maximum of iterations, and then it was finished with status code 0.");
    return 0;
}

bool shouldItTakeMoreImages(const SIGINT_Handler &sigint_handler, int iteration) {
    int maxIterationQuantity = 10;
    if (iteration >= maxIterationQuantity)
        return false;
    return sigint_handler.getGracefulQuit() == 0;
}

size_t sizeOfElement(list<Image> &images) { return images.begin()->getSerializedSize(); }

size_t sizeRequired(list<Image> &images) {
    return images.size() * sizeOfElement(images);
}