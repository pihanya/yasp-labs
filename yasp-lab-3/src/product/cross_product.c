#include <stdlib.h>
#include <stdio.h>

#include "cross_product.h"

ll cross_product(int lvec[], int rvec[], int count) {
    long product = 0L;
    for (size_t i = 0; i < count; ++i) {
        product += (lvec[i] * rvec[i]);
    }

    return product;
}