//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_FIFO_H
#define INC_75_59_CONCURRENTES_TP1_FIFO_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Fifo {
public:
    explicit Fifo(const string &nombre);

    virtual ~Fifo();

    virtual void start() = 0;

    void finish();

    void eliminar() const;

protected:
    string name;
    int fd;
};


#endif //INC_75_59_CONCURRENTES_TP1_FIFO_H
