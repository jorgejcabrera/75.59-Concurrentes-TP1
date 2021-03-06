//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_CAMERA_H
#define INC_75_59_CONCURRENTES_TP1_CAMERA_H

#include "../../image/builder/ImageBuilder.h"
#include "Resolution.h"

class Camera {
private:
    ImageBuilder imageBuilder;
    Resolution resolution;
public:
    explicit Camera(Resolution resolution);

    Image shot();

    virtual ~Camera();
};


#endif //INC_75_59_CONCURRENTES_TP1_CAMERA_H
