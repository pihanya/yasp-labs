#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "cross_product.h"

#define MAX_RANDOM 5

void fill_random(int ar[], int count) {
    for(int i = 0; i < count; ++i) {
        ar[i] = (rand() % MAX_RANDOM);
    }
}

int main() {
    srand((unsigned) time(NULL));

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

    printf("Cross product: %lld\n", cross_product(a, b, N));
    return 0;
}
