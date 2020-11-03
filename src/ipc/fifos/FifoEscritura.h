//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_FIFOESCRITURA_H
#define INC_75_59_CONCURRENTES_TP1_FIFOESCRITURA_H

#include "Fifo.h"

class FifoEscritura : public Fifo {
public:
    FifoEscritura(const std::string nombre);

    ~FifoEscritura();

    void abrir();

    ssize_t escribir(const void *buffer, const ssize_t buffsize) const;
};


#endif //INC_75_59_CONCURRENTES_TP1_FIFOESCRITURA_H
