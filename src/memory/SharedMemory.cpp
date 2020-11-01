//
// Created by Jorge Cabrera on 31/10/2020.
//

#include <string>
#include "SharedMemory.h"
# include <sys/ipc.h>
# include <sys/shm.h>
# include <cstring>
# include <cerrno>

void SharedMemory::create(const std::string &pathName, const char word, size_t capacity) {
    /**
     * La funcion ftok() me permitirá crea una key para identificar
     * el segmento de memoria compartida. Los parámetros serán:
     * 1- necesito el pathname a un archivo que exista y al cual el proceso tenga permisos de lectura. "/bin/ls"
     *  Todos los procesos pordrán generar una misma clave, conociendo cosas comunes,, como la ruta del archivo, de esta manera me aseguro
     *  que todos cuenten con la misma clave.
     * */
    key_t key = ftok(pathName.c_str(), word);
    if (key > 0) {
        /**
         * Creacion de una memoria compartida. Los parámetros a pasar serán:
         * 1- la key creada previamente, que me permite identificar el semento de memoria compartida
         * 2- el tamaño en bytes del semento. Por ejemplo si quisiese guardar dos enteros correspongo 2 * size_of(int)
         * 3- flags:
         *      - 0644 permisos de acceso al segmento de memoria
         *      - IPC_CREAT: crea el segmento de memoria si no existe
         *      - IPC_EXCL usando junto con IPC_CREAT, la operación falla si el segmento existe
         *  Esto me va a devolver un identificador valido del segmento
         */
        this->shmId = shmget(key, capacity, 0644 | IPC_CREAT);
        if (this->shmId > 0) {
            /**
             * Mapeo del segmento de memoria al espacio de direcciones de proceso. Los parámetros serán:
             * 1- shmid que es el identificador de segmento de memoria obtenido por shmget()
             * 2- shmaddr que será la dirección de memoria a la cual se mapea el segmento. Si ponemos NULL la eligirá
             *    el sistema operativo
             * 3- shmflg -> SHM_RDONLY (el segmento se adosa solo para lectura
             * Esto me devuelve un puntero al segmento de memoria compartida.
             * EL kernel no participará, mediante system calls, en la lectura y escritura del bloque de memoria.
             */
            void *tmpPtr = shmat(this->shmId, NULL, 0);
            if (tmpPtr != (void *) -1) {
                this->ptrData = static_cast <int *> (tmpPtr);
            } else {
                std::string message = std::string("Error en shmat () : ") + std::string(strerror(errno));
                throw message;
            }
        } else {
            std::string message = std::string(" Error en shmget () : ") + std::string(strerror(errno));
            throw message;
        }
    } else {
        std::string message = std::string(" Error en ftok () : ") + std::string(strerror(errno));
        throw message;
    }
}

SharedMemory::SharedMemory(int elements) {
    std::string filePath("/bin/ls");
    this->create(filePath, 'A', sizeof(int *) * elements);
}

int *SharedMemory::getPtrData() {
    return this->ptrData;
}

void SharedMemory::free() {
    // detach del bloque de memoria
    shmdt(static_cast<void *> (this->ptrData));
    shmctl(this->shmId, IPC_RMID, nullptr);

}

SharedMemory::SharedMemory() = default;

SharedMemory::~SharedMemory() = default;
