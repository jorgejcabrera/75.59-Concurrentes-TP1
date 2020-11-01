#include "observatory/ObservatoryBuilder.h"
#include "image/algorithm/ImageQualityFix.h"
#include "image/repository/ImageRepository.h"
#include "memory/SharedMemory.h"
#include "log/Logger.h"

int main() {
    /** Taking some photos */
    int camerasQuantity = 3;
    string logLevel = "DEBUG";
    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(5, 5))
            .withCamerasQuantity(camerasQuantity)
            .build();
    list<Image> images = observatory.takeImagesCapture();
    Logger::getInstance(logLevel)->log(images);

    /** Creating Shared Memory */
    SharedMemory memory = SharedMemory(images.size());
    ImageRepository imageRepository = ImageRepository(images.begin()->getSerializedSize());

    /** Save all images */
    imageRepository.saveAll(images, memory.getPtrData());

    /** Concurrencia */
    ImageQualityFix().adjustInParallel(images);
    Logger::getInstance(logLevel)->log("All images were adjusted successfully.");

    // TODO esto se hace al final para esto hay que usar señales
    //Image finalImage = ImageQualityFix().overlap(&images);


    return 0;
}