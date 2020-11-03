# 75.59-Concurrentes-TP1
It's a short POC to play with some OS features such as IPC through shared memory and signals.

IPC is a mechanism which allows processes to communicate with each other and synchronize their actions. The communication between these processes use the shared memory.
It is a concept where multiple processes can access to the common memory.

In this project, simulated images will be processed through the usage of shared memory and FIFO. 
The program will take different sample of images during n iterations. Each sample will be executed
by the program in parallel.

The program is going to finish whenever the OS sends the signal (-2) to the main process, or when 
it reaches the maximum value of iteration (100). 

### Requirements
Please ensure that you have [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. If you need to install Cmake on Mac OS you can use the following command:
```shell script
$ brew install cmake
``` 

### How to use
Firstly, run cmake by shell:
```shell script
$ cmake .
```
Then, you must build the project:
```shell script
$ make
```
Finally, you will be able to execute it:
```shell script
$ ./75_59_Concurrentes_TP1
```