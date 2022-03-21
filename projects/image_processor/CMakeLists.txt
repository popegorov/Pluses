cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        filters/blur.cpp
        filters/crop.cpp
        filters/edge_detection.cpp
        filters/grayscale.cpp
        filters/matrix.cpp
        filters/negative.cpp
        filters/sharpening.cpp
        image.cpp
        main.cpp
        )
