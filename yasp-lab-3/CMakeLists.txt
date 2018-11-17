cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(prime_checker C)

add_executable(prime
        src/prime/main.c
        src/prime/prime_ferma.c
        src/prime/prime_checker.h
        src/etc/math.h
        src/etc/utils.h)

add_executable(product
        src/product/cross_product.c
        src/product/main.c)