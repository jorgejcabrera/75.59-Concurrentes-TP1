//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_FIFOLECTURA_H
#define INC_75_59_CONCURRENTES_TP1_FIFOLECTURA_H

#include "Fifo.h"

class FifoLectura : public Fifo {
public:
    explicit FifoLectura(string nombre);

    ~FifoLectura() override;

    void start() override;

    ssize_t leer(int *buffer, ssize_t buffsize) const;
};

#endif //INC_75_59_CONCURRENTES_TP1_FIFOLECTURA_H
