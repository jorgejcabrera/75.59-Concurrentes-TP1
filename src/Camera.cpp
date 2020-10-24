//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "Camera.h"

Camera::Camera(Resolution resolution) {
    this->resolution = resolution;
    this->imageBuilder = ImageBuilder();
}

Camera::~Camera() = default;

Image Camera::shot() {
    return this->imageBuilder
            .withResolution(this->resolution)
            .build();
}