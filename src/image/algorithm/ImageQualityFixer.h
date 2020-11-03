//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIXER_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIXER_H

#include "../Image.h"

class ImageQualityFixer {
private:
    static void adjust(Image *image);

public:
    ImageQualityFixer();

    void adjustInParallel(list<Image> images);

    static Image overlap(list<Image> images);

    virtual ~ImageQualityFixer();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIXER_H
