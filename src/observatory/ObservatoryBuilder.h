//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_OBSERVATORYBUILDER_H
#define INC_75_59_CONCURRENTES_TP1_OBSERVATORYBUILDER_H

#include "Observatory.h"

class ObservatoryBuilder {
private:
    int camerasQuantity{};
    Resolution resolution;
public:
    ObservatoryBuilder();

    ObservatoryBuilder withCamerasQuantity(int camerasQuantity);

    ObservatoryBuilder withImageResolution(Resolution resolution);

    Observatory build();
};


#endif //INC_75_59_CONCURRENTES_TP1_OBSERVATORYBUILDER_H
