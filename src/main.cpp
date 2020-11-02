#include <zconf.h>
#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include "image/repository/ImageRepository.h"
#include "memory/SharedMemory.h"
#include "log/Logger.h"
#include "signal/SIGINT_Handler.h"
#include "signal/SignalHandler.h"

void bloquearSigint();

int main() {
    /** Initialing parameters */
    int camerasQuantity = 3;
    string logLevel = "DEBUG";
    int width = 2;
    int height = 2;

    cout << "Process id: " << getpid() << " \n";

    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(width, height))
            .withCamerasQuantity(camerasQuantity)
            .build();

    // event handler para la senial SIGINT (-2)
    SIGINT_Handler sigint_handler;
    // se registra el event handler declarado antes
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    while (sigint_handler.getGracefulQuit() == 0) {
        Logger::getInstance(logLevel)->log("----------------------Taking images----------------------");

        /** Taking some images */
        list<Image> images = observatory.takeImagesCapture();
        Logger::getInstance(logLevel)->log("Initial images value: ", images);

        /** Creating Shared Memory */
        SharedMemory memory = SharedMemory(images.size());
        ImageRepository imageRepository = ImageRepository(images.begin()->getSerializedSize());

        /** Save all images */
        imageRepository.saveAll(images, memory.getPtrData());

        /** Concurrencia */
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

    // se recibio la senial SIGINT, el proceso termina
    SignalHandler::destruir();
    Logger::getInstance(logLevel)->log("Process has received a signal and exit with status code 0");
    return 0;
}

void bloquearSigint() {
    sigset_t sa;
    sigemptyset(&sa);
    sigaddset(&sa, SIGINT);
    sigprocmask(SIG_BLOCK, &sa, nullptr);
}