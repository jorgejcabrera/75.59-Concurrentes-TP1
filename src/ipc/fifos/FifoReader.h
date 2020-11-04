//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_FIFOREADER_H
#define INC_75_59_CONCURRENTES_TP1_FIFOREADER_H

#include "Fifo.h"

class FifoReader : public Fifo {
public:
    explicit FifoReader(string nombre);

    ~FifoReader() override;

    void start() override;

    ssize_t pop(int *buffer, ssize_t buffsize) const;
};

#endif //INC_75_59_CONCURRENTES_TP1_FIFOREADER_H
