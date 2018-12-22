cmake_minimum_required(VERSION 3.12)
project(yasp_lab_5 C)

set(CMAKE_C_STANDARD 99)

add_executable(verticles
    src/executables/verticles.h src/executables/verticles.c
    src/data/verticle.h src/data/edge.h src/data/line.h
    src/util/draw_utils.h src/util/draw_utils.c)

add_executable(program
    src/executables/main.h src/executables/main.c
    src/data/image.h
    src/filters/gaussian_blur.h src/filters/gaussian_blur.c
    src/filters/image_rotator.h src/filters/image_rotator.c
    src/filters/acid.h src/filters/acid.c
    src/io/bmp_io.h src/io/bmp_io.c
    src/util/bmp_io_statuses.h
    src/data/verticle.h src/data/edge.h)