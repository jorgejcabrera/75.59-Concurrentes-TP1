//
// Created by Jorge Cabrera on 31/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_LOGGER_H
#define INC_75_59_CONCURRENTES_TP1_LOGGER_H

#import <string>
#include <fstream>
#include <list>
#include "../image/Image.h"

class Logger {
private:
    static Logger *instance;
    std::ofstream file;
    string level;

    explicit Logger(string level);

public:
    static Logger *getInstance(string level);

    void log(const std::string &message, const std::list<Image> &images);

    void log(const std::string &message);

    void destroy();

    static string toString(const list<Image> &list);
};


#endif //INC_75_59_CONCURRENTES_TP1_LOGGER_H
