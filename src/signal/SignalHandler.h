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
    static SignalHandler* instance;
    static EventHandler* signal_handlers [ NSIG ];

    SignalHandler ( void );
    static void dispatcher ( int signum );

public:
    static SignalHandler* getInstance ();
    static void destruir ();
    EventHandler* registrarHandler ( int signum,EventHandler* eh );
    int removerHandler ( int signum );

};

#endif //INC_75_59_CONCURRENTES_TP1_SIGNALHANDLER_H
