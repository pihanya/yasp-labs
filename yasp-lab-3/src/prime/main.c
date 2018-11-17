#include <stdio.h>
#include <stdlib.h>

#include "../etc/utils.h"
#include "prime_checker.h"

int check_prime(char const *filename) {
}

int main(int argc, char *argv[]) {
    ull a;

    printf("Type a number: ");
    scanf("%llu", &a);

    if (is_prime(a)) {
        printf("%llu is a prime number\n", a);
    } else {
        printf("%llu is not a prime number\n", a);
    }
}

