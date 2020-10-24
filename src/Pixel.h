//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_PIXEL_H
#define INC_75_59_CONCURRENTES_TP1_PIXEL_H

class Pixel {
private:
    int red;
    int blue;
    int green;
public:
    Pixel(int red, int blue, int green);

    int getRed();

    int getBlue();

    int getGreen();

    void adjust();

    virtual ~ Pixel();
};


#endif //INC_75_59_CONCURRENTES_TP1_PIXEL_H
