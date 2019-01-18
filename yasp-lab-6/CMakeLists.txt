cmake_minimum_required(VERSION 3.12)
project(yasp_lab_6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(yasp_lab_6
    alloc.c
    alloc.h
    alloc_debug.c
    alloc_debug.h
    CMakeLists.txt
    main.c
    main.h
    Makefile)
