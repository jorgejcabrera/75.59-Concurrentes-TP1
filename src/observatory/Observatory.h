//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_OBSERVATORY_H
#define INC_75_59_CONCURRENTES_TP1_OBSERVATORY_H

#include "camera/Camera.h"

class Observatory {
private:
    list<Camera> cameras;
public:
    Observatory();

    explicit Observatory(list<Camera> cameras);

    list<Image> takeImagesCapture();

    virtual~ Observatory();
};


#endif //INC_75_59_CONCURRENTES_TP1_OBSERVATORY_H
