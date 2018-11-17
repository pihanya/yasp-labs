#include "prime_checker.h"
#include "../etc/math.h"

#include <time.h>
#include <stdlib.h>

const int K = 10000;

bool is_prime(ull x) {
    if (x == 2) {
        return true;
    }

    srand( (unsigned) time(NULL) );
    for (ull i = 0; i < K; ++i) {
        ull a = (rand() % (x - 2)) + 2;
        if (gcd(a, x) != 1) {
            return false;
        }

        if (pows(a, x - 1, x) != 1) {
            return false;
        }
    }

    return true;
}

ull gcd(ull a, ull b) {
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

ull mul(ull a, ull b, ull m) {
    if (b == 1) {
        return a;
    }

    if (b % 2 == 0) {
        ull t = mul(a, b / 2, m);
        return (2 * t) % m;
    }

    return (mul(a, b - 1, m) + a) % m;
}

ull pows(ull a, ull b, ull m) {
    if (b == 0) {
        return 1;
    }

    if (b % 2 == 0) {
        ull t = pows(a, b / 2, m);
        return mul(t, t, m) % m;
    }

    return (mul(pows(a, b - 1, m), a, m)) % m;
}
