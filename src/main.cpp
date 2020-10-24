#include <iostream>
#include "ObservatoryBuilder.h"
#include "ImageQualityFix.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Observatory observatory = ObservatoryBuilder()
            .withImageResolution(Resolution(2, 2))
            .withCamerasQuantity(1)
            .build();

    list<Image> images = observatory.takeImagesCapture();

    ImageQualityFix().adjust(images.begin().operator->());
    
    return 0;
}
