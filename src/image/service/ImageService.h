//
// Created by Jorge Cabrera on 17/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGESERVICE_H
#define INC_75_59_CONCURRENTES_TP1_IMAGESERVICE_H


#include "../Image.h"

class ImageService {

public :
    ImageService();

    static size_t serializedSize(list<Image> images);

    virtual ~ImageService();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGESERVICE_H
