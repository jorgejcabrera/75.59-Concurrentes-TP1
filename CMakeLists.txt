cmake_minimum_required(VERSION 3.17)
project(75_59_Concurrentes_TP1)

set(CMAKE_CXX_STANDARD 14)

add_executable(75_59_Concurrentes_TP1 src/main.cpp src/image/Image.cpp src/image/Image.h src/image/Pixel.cpp src/image/Pixel.h src/image/builder/ImageBuilder.cpp src/image/builder/ImageBuilder.h src/image/algorithm/ImageQualityFix.cpp src/image/algorithm/ImageQualityFix.h src/observatory/Observatory.cpp src/observatory/Observatory.h src/observatory/camera/Resolution.cpp src/observatory/camera/Resolution.h src/observatory/camera/Camera.cpp src/observatory/camera/Camera.h src/observatory/ObservatoryBuilder.cpp src/observatory/ObservatoryBuilder.h src/memory/SharedMemory.cpp src/memory/SharedMemory.h src/image/repository/ImageRepository.cpp src/image/repository/ImageRepository.h src/log/Logger.cpp src/log/Logger.h src/signal/EventHandler.h src/signal/SIGINT_Handler.h src/signal/SIGINT_Handler.h src/signal/SignalHandler.cpp src/signal/SignalHandler.h)