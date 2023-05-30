#include <stdio.h>


// This computes if n is a prime number.
int myst5(unsigned long long n) {
    if (n <= 1) {
        return 0;
    }

    if (n <= 3) {
        return 1;
    }

    if ((n & 1) == 0) { // even number
        return 0;
    }

    unsigned long long i = 2;
    ++i;
    while (i*i <= n) {
        if (n % i == 0) {
            return 0;
        }
    }

    // for (unsigned long long i = 3; i*i <= n; ++i) {
    //     if (n % i == 0) {
    //         return 0;
    //     }
    // }

    return 1;
}


int main() {
    for (unsigned long long i = 1; i <= 50; ++i) {
        printf("prime[%llu] = %i\n", i, myst5(i));
    }

    return 0;
}