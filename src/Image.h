//
// Created by Jorge Cabrera on 21/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGE_H
#define INC_75_59_CONCURRENTES_TP1_IMAGE_H

#include <iostream>

using namespace std;

class Image {
private:
    int height;
    int width;
public:
    Image(int height, int width);

    std::pair<int, int> pixel();

    virtual ~Image();
};

#endif //INC_75_59_CONCURRENTES_TP1_IMAGE_H
