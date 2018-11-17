#include <stdlib.h>
#include <stdio.h>

#define MAX_RAND 10;

long cross_product(const int lvec[], const int rvec[], int count) {
    long product = 0L;
    for (size_t i = 0; i < count; ++i) {
        product += (lvec[i] * rvec[i]);
    }

    return product;
}

void fill_random(int *ar, int count) {
    for (size_t i = 0; i < count; ++i) {
        ar[i] = rand() % MAX_RAND;
    }
}

int main() {
    int N;

    printf("Type the size of vectors: \n");
    scanf("%d", &N);

    int a[N], b[N];

    fill_random(a, N);
    fill_random(b, N);

    printf("Size of vectors %d\n", N);

    printf("A: ");
    for (int i = 0; i < N; ++i) {
        if(i + 1 == N) {
            printf("%d\n", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }

    printf("B: ");
    for (int i = 0; i < N; ++i) {
        if(i + 1 == N) {
            printf("%d\n", b[i]);
        } else {
            printf("%d ", b[i]);
        }
    }


    printf("Cross product: %ld\n", cross_product(a, b, N));
    return 0;
}