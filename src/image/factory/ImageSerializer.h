//
// Created by Jorge Cabrera on 31/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGESERIALIZER_H
#define INC_75_59_CONCURRENTES_TP1_IMAGESERIALIZER_H

#include <vector>
#include "../Image.h"

class ImageSerializer {
public:
    ImageSerializer();

    Image fromBytes(const int *bytes);

    int *toBytes(Image image);

    virtual ~ImageSerializer();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGESERIALIZER_H
