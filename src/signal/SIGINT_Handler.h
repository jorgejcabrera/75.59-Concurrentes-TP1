//
// Created by Jorge Cabrera on 01/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_SIGINT_HANDLER_H
#define INC_75_59_CONCURRENTES_TP1_SIGINT_HANDLER_H

#include <csignal>
#include <cassert>

#include "EventHandler.h"

class SIGINT_Handler : public EventHandler {

private:
    sig_atomic_t gracefulQuit;

public:

    SIGINT_Handler () : gracefulQuit(0) {
    }

    ~SIGINT_Handler () override = default;

    int handleSignal ( int signum ) override {
        assert ( signum == SIGINT );
        this->gracefulQuit = 1;
        return 0;
    }

    sig_atomic_t getGracefulQuit () const  {
        return this->gracefulQuit;
    }

};

#endif //INC_75_59_CONCURRENTES_TP1_SIGINT_HANDLER_H
