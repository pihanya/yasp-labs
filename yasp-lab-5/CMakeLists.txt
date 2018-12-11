cmake_minimum_required(VERSION 3.12)
project(yasp_lab_5 C)

set(CMAKE_C_STANDARD 99)

add_executable(verticles
    executables/verticles.h executables/verticles.c
    data/verticle.h data/edge.h data/line.h
    util/draw_utils.h util/draw_utils.c)

add_executable(program
    executables/main.h executables/main.c
    data/image.h
    filters/gaussian_blur.h filters/gaussian_blur.c
    filters/image_rotator.h filters/image_rotator.c
    io/bmp_io.h io/bmp_io.c
    util/bmp_io_statuses.h
    data/verticle.h data/edge.h)