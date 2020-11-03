//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_FIFOLECTURA_H
#define INC_75_59_CONCURRENTES_TP1_FIFOLECTURA_H

#include "Fifo.h"

class FifoLectura : public Fifo {
public:
    FifoLectura(const std::string nombre);

    ~FifoLectura();

    void abrir();

    ssize_t leer(void *buffer, const ssize_t buffsize) const;
};


#endif //INC_75_59_CONCURRENTES_TP1_FIFOLECTURA_H
