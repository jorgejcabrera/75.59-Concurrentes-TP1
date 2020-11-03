//
// Created by Jorge Cabrera on 21/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_IMAGE_H
#define INC_75_59_CONCURRENTES_TP1_IMAGE_H

#include <iostream>
#include <map>
#include <list>
#include "Pixel.h"

using namespace std;

class Image {
private:
    int id{};
    map<int, list<Pixel>> pixels;
public:
    Image();

    Image(map<int, list<Pixel>> pixels, int id);

    map<int, list<Pixel>> *getPixels();

    void setPixels(map<int, list<Pixel>> pixels);

    void setId(int id);

    int getId() const;

    size_t getSerializedSize();

    string toString();

    virtual ~Image();
};

#endif //INC_75_59_CONCURRENTES_TP1_IMAGE_H
