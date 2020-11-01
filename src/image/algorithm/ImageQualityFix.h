//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIX_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIX_H

#include "../Image.h"

class ImageQualityFix {
private:
    static void adjust(Image *image);

public:
    ImageQualityFix();

    void adjustInParallel(list<Image> images);

    static Image overlap(list<Image> *images);

    virtual ~ImageQualityFix();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEQUALITYFIX_H
