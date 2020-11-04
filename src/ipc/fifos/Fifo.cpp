//
// Created by Jorge Cabrera on 03/11/2020.
//

#include "Fifo.h"

using namespace std;

Fifo::Fifo(const string &nombre) : name(nombre), fd(-1) {
    mknod(static_cast<const char *>(nombre.c_str()), S_IFIFO | 0666, 0);
}

Fifo::~Fifo() = default;

void Fifo::finish() {
    close(fd);
    fd = -1;
}

void Fifo::destroy() const {
    unlink(name.c_str());
}
