cmake_minimum_required (VERSION 2.6)
project(NeuralNetworkSandbox)

set(CMAKE_CXX_FLAGS -std=c++11)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/Net")

file(GLOB SOURCES "src/*.cpp"
                  "src/Net/*.cpp")

add_executable(NeuralNetworkSandbox ${SOURCES})
