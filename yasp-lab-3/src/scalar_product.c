#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <afxres.h>

const int N = 5;

double cross_product(const double *lvec, const double *rvec, size_t count) {
    double product = 0.0;
    for (size_t i = 0; i < count; ++i) {
        product += (lvec[i] * rvec[i]);
    }

    return product;
}

void fill_random(double *ar, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        ar[i] = (double) rand() / RAND_MAX * 2.0 - 1.0;
    }
}

int main() {
    double a[N];
    double b[N];

    fill_random(a, N);
    fill_random(b, N);

    int sizeA = sizeof(a) / sizeof(double);
    int sizeB = sizeof(b) / sizeof(double);
    printf("Size of a: %d\nSize of b: %d\n", sizeA, sizeB);

    int bound = min(sizeA, sizeB);
    for (size_t i = 0; i < bound; ++i) {
        printf("A: %.2f, B: %.2f\n", a[i], b[i]);
    }

    printf("Cross product: %.5f\n", cross_product(a, b, N));
    return 0;
}