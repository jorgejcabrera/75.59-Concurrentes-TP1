//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_FIFOWRITER_H
#define INC_75_59_CONCURRENTES_TP1_FIFOWRITER_H

#include "Fifo.h"

class FifoWriter : public Fifo {
public:
    explicit FifoWriter(const string &name);

    ~FifoWriter() override;

    void start() override;

    ssize_t push(int *buffer, ssize_t size) const;
};


#endif //INC_75_59_CONCURRENTES_TP1_FIFOWRITER_H
