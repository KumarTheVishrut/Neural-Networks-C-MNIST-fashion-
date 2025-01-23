cmake_minimum_required(VERSION 3.0)

project(NeuralNets)

set(CMAKE_BUILD_TYPE   Debug)
set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


add_executable(NeuralNets
    src/main.cpp
    src/Matrix.cpp
    src/NeuralNetwork.cpp
    src/Layer.cpp
    src/Neuron.cpp
    src/utils/MultiplyMatrix.cpp

)
