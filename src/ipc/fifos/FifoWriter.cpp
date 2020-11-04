//
// Created by Jorge Cabrera on 03/11/2020.
//

#include "FifoWriter.h"

using namespace std;

FifoWriter::FifoWriter(const string &name) : Fifo(name) {
}

FifoWriter::~FifoWriter() = default;

void FifoWriter::start() {
    fd = open(name.c_str(), O_WRONLY);
}

ssize_t FifoWriter::push(int *buffer, ssize_t size) const {
    return write(fd, buffer, size);
}
