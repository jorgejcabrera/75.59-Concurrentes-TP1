//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEBUILDER_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEBUILDER_H
#include "Image.h"

class ImageBuilder {

private:
    int height{};
    int width{};
public:
    ImageBuilder();

    ImageBuilder withHeight(int height);

    ImageBuilder withWidth(int width);

    Image build() const;

    virtual ~ImageBuilder();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEBUILDER_H
