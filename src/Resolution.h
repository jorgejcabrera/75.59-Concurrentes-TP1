//
// Created by Jorge Cabrera on 24/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_RESOLUTION_H
#define INC_75_59_CONCURRENTES_TP1_RESOLUTION_H

class Resolution {
private:
    int width{};
    int height{};
public:
    Resolution();

    Resolution(int width, int height);

    int getWidth();

    int getHeight();

    virtual ~Resolution();
};


#endif //INC_75_59_CONCURRENTES_TP1_RESOLUTION_H
