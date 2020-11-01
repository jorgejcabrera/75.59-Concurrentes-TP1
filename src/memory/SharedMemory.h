//
// Created by Jorge Cabrera on 31/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_SHAREDMEMORY_H
#define INC_75_59_CONCURRENTES_TP1_SHAREDMEMORY_H

#include <cstddef>
# include <string>
# include <string.h>

class SharedMemory {
private:
    int shmId{};

    int *ptrData{};

    void create(const std::string &pathName, char word, size_t capacity);


public:
    SharedMemory();

    SharedMemory(int elements);

    //void write(const int &data, size_t offset);

    int *getPtrData();

    void free();

    virtual ~SharedMemory();
};

#endif //INC_75_59_CONCURRENTES_TP1_SHAREDMEMORY_H
