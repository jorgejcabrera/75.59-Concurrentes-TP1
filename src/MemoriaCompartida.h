//
// Created by Jorge Cabrera on 30/10/2020.
//

#ifndef INC_75_59_CONCURRENTES_TP1_MEMORIACOMPARTIDA_H
#define INC_75_59_CONCURRENTES_TP1_MEMORIACOMPARTIDA_H

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <string>
# include <string.h>
# include <iostream>
# include <errno.h>

template<class T>
class MemoriaCompartida {

private :
    int shmId;
    T *ptrDatos;

    int cantidadProcesosAdosados() const;

public :
    MemoriaCompartida();

    void create(const std::string &pathName, const char word);

    void free();

    MemoriaCompartida(const std::string &pathName, const char word);

    MemoriaCompartida(const MemoriaCompartida &origen);

    ~MemoriaCompartida();

    MemoriaCompartida<T> &operator=(const MemoriaCompartida &origen);

    void write(const T &data);

    T read() const;
};

/**
 * La memoria compartida no tiene un proceso dueño. El dueño es el usuario. Nos permitirá compartir un valor entre procesos.
 * IMPORTANTE: Cada vez que usamos memoria compartida, tenemos que asegurar un mecanismo de exclusión mutua, que permite los procesos
 * accedad de a uno por vez. Debemos acceder de forma sincronizada porque ninguna lectura/escritura en memoria es atómica.
 * */
template<class T>
MemoriaCompartida<T>::MemoriaCompartida() : shmId(0), ptrDatos(NULL) {
}

template<class T>
void MemoriaCompartida<T>::create(const std::string &pathName, const char word) {
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
        this->shmId = shmget(key, sizeof(T), 0644 | IPC_CREAT);
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
                this->ptrDatos = static_cast <T *> (tmpPtr);
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


template<class T>
void MemoriaCompartida<T>::free() {

    /**
     * De esta forma dejamos de poder acceder (desadosado) al segemento de memoria compartido en el proceso.
     * Todos los procesos que hicisron attach deben hacer detach. Recibe por parámetro la dirección del segmento obtenido.
     * La memoria, deja de poder ser accedida por el proceso, pero continua existiendo.
     */
    int errorDt = shmdt((void *) this->ptrDatos);

    if (errorDt != -1) {
        // TODO esto deberia borrarlo en mi programa
        int procAdosados = this->cantidadProcesosAdosados();
        if (procAdosados == 0) {
            /**
             * De esta forma destruyo el objeto IPC.
             */
            shmctl(this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::string message = std::string("Error en shmdt() : ") + std::string(strerror(errno));
        throw message;
    }
}

template<class T>
MemoriaCompartida<T>::MemoriaCompartida(const std::string &pathName, const char word): shmId(0), ptrDatos(NULL) {
    key_t key = ftok(pathName.c_str(), word);

    if (key > 0) {
        this->shmId = shmget(key, sizeof(T) * 1024, 0644 | IPC_CREAT);

        if (this->shmId > 0) {
            void *tmpPtr = shmat(this->shmId, NULL, 0);
            if (tmpPtr != (void *) -1) {
                this->ptrDatos = static_cast <T * > ( tmpPtr );
            } else {
                std::string message = std::string("Error en shmat () : ") + std::string(strerror(errno));
                throw message;
            }
        } else {
            std::string message = std::string("Error en shmget () : ") + std::string(strerror(errno));
            throw message;
        }
    } else {
        std::string message = std::string(" Error en ftok () : ") + std::string(strerror(errno));
        throw message;
    }
}

template<class T>
MemoriaCompartida<T>::MemoriaCompartida(const MemoriaCompartida &origen): shmId(origen.shmId) {
    void *tmpPtr = shmat(origen.shmId, NULL, 0);

    if (tmpPtr != (void *) -1) {
        this->ptrDatos = static_cast <T * > ( tmpPtr );
    } else {
        std::string mensaje = std::string(" Error en shmat () : ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template<class T>
MemoriaCompartida<T>::~MemoriaCompartida() {
    int errorDt = shmdt(static_cast < void *> (this->ptrDatos ));

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if (procAdosados == 0) {
            shmctl(this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::cerr << " Error en shmdt () : " << strerror(errno) << std::endl;
    }
}

template<class T>
MemoriaCompartida<T> &MemoriaCompartida<T>::operator=(const MemoriaCompartida &origen) {
    this->shmId = origen.shmId;
    void *tmpPtr = shmat(this->shmId, NULL, 0);

    if (tmpPtr != (void *) -1) {
        this->ptrDatos = static_cast <T * > ( tmpPtr );
    } else {
        std::string mensaje = std::string(" Error en shmat () : ") + std::string(strerror(errno));
        throw mensaje;
    }

    return *this;
}

template<class T>
void MemoriaCompartida<T>::write(const T &data) {
    *(this->ptrDatos) = data;
}

template<class T>
T MemoriaCompartida<T>::read() const {
    return *(this->ptrDatos);
}

template<class T>
int MemoriaCompartida<T>::cantidadProcesosAdosados() const {
    shmid_ds estado;
    shmctl(this->shmId, IPC_STAT, &estado);
    return estado.shm_nattch;
}


#endif //INC_75_59_CONCURRENTES_TP1_MEMORIACOMPARTIDA_H
