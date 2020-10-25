//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGEBUILDER_H
#define INC_75_59_CONCURRENTES_TP1_IMAGEBUILDER_H

#include "Image.h"
#include "../observatory/camera/Resolution.h"

class ImageBuilder {

private:
    Resolution resolution;
public:
    ImageBuilder();

    ImageBuilder withResolution(Resolution resolution);

    Image build() const;

    virtual ~ImageBuilder();
};


#endif //INC_75_59_CONCURRENTES_TP1_IMAGEBUILDER_H
