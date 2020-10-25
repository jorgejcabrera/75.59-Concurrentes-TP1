//
// Created by Jorge Cabrera on 24/10/2020.
//

#include "ObservatoryBuilder.h"

ObservatoryBuilder::ObservatoryBuilder() = default;

ObservatoryBuilder ObservatoryBuilder::withCamerasQuantity(int camerasQuantity) {
    this->camerasQuantity = camerasQuantity;
    return *this;
}

ObservatoryBuilder ObservatoryBuilder::withImageResolution(Resolution resolution) {
    this->resolution = resolution;
    return *this;
}

Observatory ObservatoryBuilder::build() {
    list<Camera> cameras;
    for (int i = 0; i < camerasQuantity; i++) {
        cameras.emplace_back(resolution);
    }
    return Observatory(cameras);
}

