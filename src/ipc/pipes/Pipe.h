//
// Created by Jorge Cabrera on 03/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_PIPE_H
#define INC_75_59_CONCURRENTES_TP1_PIPE_H

#include <unistd.h>
#include <fcntl.h>

class Pipe {

private:
    int descriptores[2];
    bool lectura;
    bool escritura;

public:
    static const int LECTURA = 0;
    static const int ESCRITURA = 1;

    Pipe();

    ~Pipe();

    void setearModo(const int modo);

    ssize_t escribir(const void *dato, const int datoSize);

    ssize_t leer(void *buffer, const int buffSize);

    int getFdLectura() const;

    int getFdEscritura() const;

    void cerrar();
};

#endif //INC_75_59_CONCURRENTES_TP1_PIPE_H
