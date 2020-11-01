//
// Created by Jorge Cabrera on 31/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H

#include "../Image.h"

class ImageRepository {
public:
    ImageRepository();

    void save(Image image, int *ptr);

    static Image read(const int *ptr);

    virtual ~ImageRepository();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEREPOSITORY_H
