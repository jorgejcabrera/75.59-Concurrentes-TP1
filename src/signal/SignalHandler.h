//
// Created by Jorge Cabrera on 01/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_SIGNALHANDLER_H
#define INC_75_59_CONCURRENTES_TP1_SIGNALHANDLER_H

#include <csignal>
#include <cstdio>
#include <memory.h>

#include "EventHandler.h"

class SignalHandler {

private:
    static SignalHandler *instance;
    static EventHandler *signal_handlers[NSIG];

    SignalHandler();

    static void dispatcher(int signum);

public:
    static SignalHandler *getInstance();

    static void destroy();

    static EventHandler *registerHandler(int signum, EventHandler *eh);

    int removeHandler(int signum);

};

#endif //INC_75_59_CONCURRENTES_TP1_SIGNALHANDLER_H
