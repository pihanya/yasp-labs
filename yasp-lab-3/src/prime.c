#include "prime.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef int bool;

#define true 1
#define false 0

const int K = 100;

bool prime_sqrt(unsigned long long x) {
    for(int i = 2; i*i < x; ++i) {
        if(x % i == 0) {
            return false;
        }
    }

    return true;
}

bool ferma(unsigned long long x) {
    if (x == 2) {
        return true;
    }

    srand(time(NULL));
    for (unsigned long long  i = 0; i < K; ++i) {
        long long a = (rand() % (x - 2)) + 2;
        if (gcd(a, x) != 1) {
            return false;
        }

        if (pows(a, x - 1, x) != 1) {
            return false;
        }
    }

    return true;
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

unsigned long long pows(unsigned long long a, unsigned long long b, unsigned long long m) {
    if (b == 0) {
        return 1;
    }

    if (b % 2 == 0) {
        long long t = pows(a, b / 2, m);
        return mul(t, t, m) % m;
    }

    return (mul(pows(a, b - 1, m), a, m)) % m;
}

unsigned long long mul(unsigned long long a, unsigned long long b, unsigned long long m) {
    if (b == 1) {
        return a;
    }

    if (b % 2 == 0) {
        long long t = mul(a, b / 2, m);
        return (2 * t) % m;
    }

    return (mul(a, b - 1, m) + a) % m;
}

int main() {
    unsigned long long int a;

    scanf("%llu", &a);
    printf("Given number is: %llu\n", a);

    if(ferma(a)) {
        printf("%llu is prime", a);
    } else {
        printf("%llu is not prime", a);
    }
}
