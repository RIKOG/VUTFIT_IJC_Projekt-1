// bitset.h
// Riesenie IJC-DU1, priklad a), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#pragma once
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "error.h"
typedef unsigned long* bitset_t;

typedef unsigned long bitset_index_t;

#define bitset_create(meno, velkost)\
bitset_index_t meno[velkost/((sizeof(bitset_index_t)*__CHAR_BIT__) ) + (velkost % (sizeof(bitset_index_t)*__CHAR_BIT__) > 0 ? 1 : 0) + 1] = {velkost};\
assert(velkost < 500000002 && velkost > 64)

#define bitset_alloc(meno, velkost) \
assert(velkost < 500000002 && velkost > 64);\
bitset_t meno = (bitset_t) calloc(velkost/((sizeof(bitset_index_t)*__CHAR_BIT__) ) + (velkost % (sizeof(bitset_index_t)*__CHAR_BIT__) > 0 ? 1 : 0) + 1, sizeof(unsigned long));\
if(meno == NULL){\
    error_exit("Nepodarilo sa mallocnut pole bitov");\
}else{\
    *meno = velkost;\
}

#ifdef USE_INLINE
inline void bitset_free(bitset_t meno){
    free(meno);
}

inline unsigned long bitset_size(bitset_t meno){
    return meno[0];
}

inline void bitset_setbit(bitset_t meno, bitset_index_t index, bitset_index_t vyraz){
    if((bitset_index_t)index >= bitset_size(meno)){
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", \
            (unsigned long)index, bitset_size(meno));
    }
    if(vyraz){
        meno[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] |= ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)));
    } else {
        meno[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] &= ~((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)));
    }
}

inline int bitset_getbit(bitset_t meno, bitset_index_t index){
    if(index >= bitset_size(meno)){
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", \
               (unsigned long)index,bitset_size(meno));
    }
    return (bitset_index_t)((meno[(index/(sizeof(bitset_index_t)*__CHAR_BIT__)+1)] &
    ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)))) > 0);
}
#else
#define bitset_free(meno) free(meno)

#define bitset_size(meno) meno[0]

#define bitset_setbit(meno, index, vyraz)\
    if((bitset_index_t)index >= bitset_size(meno)){ \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",\
               (unsigned long)index, bitset_size(meno)); \
    } else {\
    (vyraz ? \
        (meno[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] |= ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__))))\
    :\
        (meno[(index/(sizeof(bitset_index_t)*__CHAR_BIT__))+1] &= ~((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)))) );\
    }

#define bitset_getbit(meno, index)\
    ((bitset_index_t)index >= bitset_size(meno)) ?\
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",\
               (unsigned long)index, bitset_size(meno)), 0 \
    :\
    (bitset_index_t)((meno[(index/(sizeof(bitset_index_t)*__CHAR_BIT__)+1)] & \
    ((bitset_index_t)1 << (index%(sizeof(bitset_index_t)*__CHAR_BIT__)))) > 0)
#endif




