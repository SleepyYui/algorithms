//
// Created by SleepyYui on 23.03.2023.
// Modified last by SleepyYui on 24.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void fib(unsigned long n, mpz_t *memo[]) {
    if (mpz_cmp_ui(*memo[n % 2], 0) != 0) {
        return;
    }
    if (n <= 2) {
        mpz_set_ui(*memo[n % 2], 1);
        return;
    }
    unsigned long i;
    for (i = 2; i <= n; i++) {
        mpz_add(*memo[i % 2], *memo[(i - 1) % 2], *memo[(i - 2) % 2]);
    }
}

int main(int argc, char *argv[]) {
    // set n to the args provided
    unsigned long n;
    if (argc == 2) {
        n = strtoul(argv[1], NULL, 10);
    } else {
        fprintf(stderr, "usage: fib <n>\n");
        exit(EXIT_FAILURE);
    }
    mpz_t *memo[2];
    printf("allocating %lu bytes\n", sizeof(mpz_t) * 2);
    memo[0] = calloc(1, sizeof(mpz_t));
    memo[1] = calloc(1, sizeof(mpz_t));
    printf("initializing %lu bytes\n", sizeof(mpz_t) * 2);
    mpz_init(memo[0][0]);
    mpz_init(memo[1][0]);
    fib(n, memo);
    printf("done\nresult:\n");
    mpz_out_str(stdout, 10, memo[n % 2][0]);
    printf("\n");
    printf("clearing %lu bytes\n", sizeof(mpz_t) * 2);
    mpz_clear(memo[0][0]);
    mpz_clear(memo[1][0]);
    printf("freeing %lu bytes\n", sizeof(mpz_t) * 2);
    free(memo[0]);
    free(memo[1]);
    return EXIT_SUCCESS;
}
