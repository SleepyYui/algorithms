//
// Created by SleepyYui on 11.03.2023.
// Modified last by SleepyYui on 11.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void fib(unsigned long n, mpz_t *memo) {
    if (mpz_cmp_ui(memo[n], 0) != 0) {
        return;
    }
    if (n <= 2) {
        mpz_set_ui(memo[n], 1);
        return;
    }
    if (n % 2 == 0) {
        unsigned long m = n / 2;
        fib(m, memo);
        fib(m - 1, memo);
        mpz_add(memo[n], memo[m], memo[m - 1]);
        mpz_mul(memo[n], memo[n], memo[m - 1]);
        mpz_add(memo[n], memo[n], memo[m]);
    } else {
        unsigned long m = (n + 1) / 2;
        fib(m, memo);
        fib(m - 1, memo);
        mpz_mul(memo[n], memo[m], memo[m]);
        mpz_mul(memo[n - 1], memo[m - 1], memo[m - 1]);
        mpz_add(memo[n], memo[n], memo[n - 1]);
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
    mpz_t *memo = calloc(n + 1, sizeof(mpz_t));
    if (memo == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned long i = 0; i <= n; i++) {
        mpz_init(memo[i]);
    }
    fib(n, memo);
    printf("done\nresult:\n");
    mpz_out_str(stdout, 10, memo[n]);
    printf("\n");
    for (unsigned long i = 0; i <= n; i++) {
        mpz_clear(memo[i]);
    }
    free(memo);
    return EXIT_SUCCESS;
}