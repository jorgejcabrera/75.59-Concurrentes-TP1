//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "Observatory.h"

Observatory::Observatory(list<Camera> cameras) {
    this->cameras = cameras;
}

list<Image> Observatory::takeImagesCapture() {
    list<Image> images;
    for (auto &camera : this->cameras) {
        images.push_back(camera.shot());
    }
    return images;
}

Observatory::~Observatory() = default;
