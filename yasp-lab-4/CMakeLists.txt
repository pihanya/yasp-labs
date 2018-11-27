cmake_minimum_required(VERSION 3.12)
project(yasp_lab_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(yasp_lab_4
        main.c
        llist.h llist.c
        high_order.h high_order.c)
