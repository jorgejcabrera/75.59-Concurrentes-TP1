# 75.59-Concurrentes-TP1
It's a short POC to play with some OS features such as IPC through shared memory and signals.

IPC is a mechanism which allows processes to communicate with each other an synchronize their actions. The communication between these processes used the shared memory.
It is a concept where two or more process can access the common memory.

### Requirements
Please ensure that you have [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. If you need to install Cmake on Mac OS you can use the following command:
```shell script
brew install cmake
``` 

### How to use
First of all, run cmake by shell:
```shell script
cmake .
```
Then you must build the project:
```shell script
make
```
Finally, you will be able to run with:
```shell script
./75_59_Concurrentes_TP1
```