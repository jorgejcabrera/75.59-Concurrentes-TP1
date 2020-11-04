//
// Created by Jorge Cabrera on 03/11/2020.
//

#include "FifoEscritura.h"

using namespace std;

FifoEscritura::FifoEscritura(const string &nombre) : Fifo(nombre) {
}

FifoEscritura::~FifoEscritura() = default;

void FifoEscritura::start() {
    fd = open(name.c_str(), O_WRONLY);
}

ssize_t FifoEscritura::escribir(int *buffer, const ssize_t buffsize) const {
    return write(fd, buffer, buffsize);
}
