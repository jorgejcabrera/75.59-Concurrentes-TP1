//
// Created by Jorge Cabrera on 03/11/2020.
//

#include "FifoReader.h"

using namespace std;

FifoReader::FifoReader(const string nombre) : Fifo(nombre) {
}

FifoReader::~FifoReader() = default;

void FifoReader::start() {
    fd = open(name.c_str(), O_RDONLY);
}

ssize_t FifoReader::pop(int *buffer, ssize_t buffsize) const {
    return read(fd, buffer, buffsize);
}
