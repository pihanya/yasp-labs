#include "prime.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef int bool;

#define true 1
#define false 0

bool ferma(long long x) {
    if (x == 2) {
        return true;
    }

    srand(time(NULL));
    for (int i = 0; i < 100; ++i) {
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

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

long long pows(long long a, long long b, long long m) {
    if (b == 0) {
        return 1;
    }

    if (b % 2 == 0) {
        long long t = pows(a, b / 2, m);
        return mul(t, t, m) % m;
    }

    return (mul(pows(a, b - 1, m), a, m)) % m;
}

long long mul(long long a, long long b, long long m) {
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
    long long int a;

    scanf("%lld", &a);
    printf("Given number is: %lld\n", a);

    if(ferma(a)) {
        printf("%lld is prime", a);
    } else {
        printf("%lld is not prime", a);
    }
}
