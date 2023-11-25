# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Define the project and its name
project(tp2)

# Add the source files
file(GLOB SOURCES "TP2 - Circuits/TP2 - Circuits/*.c" "TP2 - Circuits/TP2 - Circuits/*.h")

# Add an executable target
add_executable(my_executable ${SOURCES})
