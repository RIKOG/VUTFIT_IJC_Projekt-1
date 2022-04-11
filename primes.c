// primes.c
// Riesenie IJC-DU1, priklad a), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.c"
#include "error.c"
int main() {
    time_t start;
    start = clock();

    bitset_create(ptr_primes,200000000);
    eratosthenes(ptr_primes);

    int counter = 0;
    bitset_index_t i = bitset_size(ptr_primes) - 1;
    for(;counter < 10; i--) {
        if (!(bitset_getbit(ptr_primes, i))) {
            counter++;
        }
    }
    for(;i<bitset_size(ptr_primes); i++){
        if (!(bitset_getbit(ptr_primes, i))) {
            printf("%ld\n", i);
        }
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
