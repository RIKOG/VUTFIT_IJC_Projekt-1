// eratosthenes.c
// Riesenie IJC-DU1, priklad a), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#include <math.h>
#include "eratosthenes.h"
void eratosthenes(bitset_t pole){

    bitset_setbit(pole,0,1); //0 neni prvocislo
    bitset_setbit(pole,1,1); //1 neni prvocislo

    unsigned long velkost = bitset_size(pole);
    unsigned long root = sqrt(velkost);

    for(bitset_index_t i = 2; i < root; i++){
        if(bitset_getbit(pole, i) == 0){
            for(bitset_index_t j = 2; (j * i) < velkost; j++){
                bitset_setbit(pole,j * i,1);
            }
        }
    }
}