//
// Created by Jorge Cabrera on 01/11/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_EVENTHANDLER_H
#define INC_75_59_CONCURRENTES_TP1_EVENTHANDLER_H


class EventHandler {

public:
    virtual int handleSignal ( int signum ) = 0;
    virtual ~EventHandler () = default;;
};

#endif //INC_75_59_CONCURRENTES_TP1_EVENTHANDLER_H
