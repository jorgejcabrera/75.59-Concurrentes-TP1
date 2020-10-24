#include <iostream>
#include "ImageBuilder.h"
#include "ImageQualityFix.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Image image = ImageBuilder()
            .withWidth(2)
            .withHeight(2)
            .build();

    ImageQualityFix().adjust(&image);

    return 0;
}
