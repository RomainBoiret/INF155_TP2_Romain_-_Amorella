# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Define the project and its name
project(tp2)

# Add the source files
set(SOURCES
    main_test_partie1.c
    t_circuit.c
    t_circuit.h
    t_entree.c
    t_entree.h
    t_pin_entree.c
    t_pin_entree.h
    t_pin_sortie.c
    t_pin_sortie.h
    t_porte.c
    t_porte.h
    t_sortie.c
    t_sortie.h
)

# Add an executable target
add_executable(my_executable ${SOURCES})
