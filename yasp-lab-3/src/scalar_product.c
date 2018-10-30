#include <stdlib.h>
#include <stdio.h>
#include <afxres.h>

const int MAX_RAND = 100;

long cross_product(int lvec[], int rvec[], int count) {
    double product = 0.0;
    for (size_t i = 0; i < count; ++i) {
        product += (lvec[i] * rvec[i]);
    }

    return product;
}

void fill_random(double *ar, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        ar[i] = rand() % MAX_RAND;
    }
}

int main() {
    int N;

    printf("Type the size of vectors: \n");
    scanf("%d", &N);

    int a[N];
    int b[N];

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