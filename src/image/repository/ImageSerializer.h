//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGESERIALIZER_H
#define INC_75_59_CONCURRENTES_TP1_IMAGESERIALIZER_H

#include "../Image.h"

class ImageSerializer {
public:
    ImageSerializer();

    static void serialize(Image image, int *ptr);

    static Image hydrate(const int *ptr);

    virtual ~ImageSerializer();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGESERIALIZER_H
