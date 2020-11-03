//
// Created by Jorge Cabrera on 03/11/2020.
//

#include "FifoLectura.h"

using namespace std;

FifoLectura::FifoLectura(const string nombre) : Fifo(nombre) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
    fd = open(nombre.c_str(), O_RDONLY);
}

ssize_t FifoLectura::leer(int *buffer, const ssize_t buffsize) const {
    return read(fd, buffer, buffsize);
}
