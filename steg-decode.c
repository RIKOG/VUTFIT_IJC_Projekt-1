// steg-decode.c
// Riesenie IJC-DU1, priklad b), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#include <stdio.h>
#include "ppm.c"
#include "bitset.h"
#include "eratosthenes.c"

int main(int argc, char* argv[]) {
    struct ppm *ptr_struct;

    if(argc != 2){
        error_exit("Zly pocet argumentov");
    }else{
        ptr_struct = ppm_read(argv[1]);
    }

    if(ptr_struct == NULL){
        error_exit("Pocas otvarania a citania dat zo suboru doslo k chybe", argv[1]);
    }

    unsigned long velkost = 3 * ptr_struct->xsize * ptr_struct->ysize;
    bitset_alloc(ptr_primes, velkost);
    eratosthenes(ptr_primes);
    char znak = 0;
    int posun = 0;
    int kontrola_formatu = 0;
    for(unsigned long i = 23; i < velkost; i++) {
        if (!(bitset_getbit(ptr_primes, i))) {
            znak |= (ptr_struct->data[i] & 1) << posun;
            posun++;
            if (posun == 8) {
                if(znak == EOF){
                    bitset_free(ptr_struct);
                    bitset_free(ptr_primes);
                    error_exit("Zly format");
                }
                if (znak == '\0') {
                    kontrola_formatu = 1;
                    break;
                }
                printf("%c", znak);
                znak = 0;
                posun = 0;
            }
        }
    }
    printf("\n");

    bitset_free(ptr_struct);
    bitset_free(ptr_primes);
    if(kontrola_formatu == 0){
        error_exit("Sprava neni ukoncena EOF");
    }
    return 0;
}


