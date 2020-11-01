#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include "image/repository/ImageRepository.h"
#include "memory/SharedMemory.h"
#include "log/Logger.h"

int main() {
    /** Initialing parameters */
    int camerasQuantity = 3;
    string logLevel = "DEBUG";
    int width = 2;
    int height = 2;

    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(width, height))
            .withCamerasQuantity(camerasQuantity)
            .build();

    int iteration = 0;
    while (iteration < 5) {
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
        iteration++;
    }
    
    return 0;
}