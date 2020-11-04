//
// Created by Jorge Cabrera on 31/10/2020.
//

#include "Logger.h"
#include <sstream>

#include <ctime>
#include <chrono>
#include <utility>

using namespace std::chrono;

string getTimestamp() {
    system_clock::time_point tp = system_clock::now();
    time_t tm = system_clock::to_time_t(tp);
    struct tm stm = *localtime(&tm);
    auto dur = tp.time_since_epoch();
    dur -= duration_cast<seconds>(dur);

    char timestamp[32] = {0};
    snprintf(timestamp, sizeof(timestamp),
             "%04u-%02u-%02u %02u:%02u:%02u.%03lld",
             stm.tm_year + 1900, stm.tm_mon + 1, stm.tm_mday,
             stm.tm_hour, stm.tm_min, stm.tm_sec,
             duration_cast<milliseconds>(dur).count());

    return timestamp;
}

Logger *Logger::instance = nullptr;

void Logger::destroy() {
    this->file.close();
    if (instance != nullptr) {
        delete (instance);
        instance = nullptr;
    }
}

Logger::Logger(std::string level) {
    this->level = std::move(level);
}

Logger *Logger::getInstance(std::string level) {
    if (Logger::instance == nullptr) {
        Logger::instance = new Logger(std::move(level));
    }
    auto logger = Logger::instance;
    return logger;
}

void Logger::log(const std::string &message, const std::list<Image> &images) {
    this->file.open("/Users/jorge.cabrera/workspace/Facultad/75.59-Concurrentes-TP1/log.txt", ios::app);
    if (!this->file.is_open()) {
        cerr << "It was an error when open log file.\n";
    }
    if (this->level == "DEBUG") {
        this->file << "[" << getTimestamp() << "] [" << this->level << "] " << message << "\n";
        string strImages = toString(images);
        this->file << strImages;
        this->file.close();
    }
}

void Logger::log(const std::string &message) {
    this->file.open("/Users/jorge.cabrera/workspace/Facultad/75.59-Concurrentes-TP1/log.txt", ios::app);
    if (!this->file.is_open()) {
        cerr << "It was an error when open log file.\n";
    }
    if (this->level == "DEBUG") {
        this->file << "[" << getTimestamp() << "] [" << this->level << "] " << message << "\n";
        this->file.close();
    }
}

string Logger::toString(const list<Image> &list) {
    stringstream ss;
    for (auto it = list.begin(); it != list.end(); it++) {
        Image image = it.operator*();
        ss << image.toString();
    }
    return ss.str();
}