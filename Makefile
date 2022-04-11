LC_ALL=cs_CZ.utf8

CFLAGS =-g -std=c11 -pedantic -Wall -Wextra -lm -O2
COMPILER = gcc

all: primes primes-i steg-decode

primes: primes.c eratosthenes.c error.c bitset.h eratosthenes.h error.h
	$(COMPILER) $(CFLAGS) primes.c -o primes

primes-i: primes.c eratosthenes.c error.c bitset.h eratosthenes.h error.h
	$(COMPILER) $(CFLAGS) primes.c -o primes-i -DUSE_INLINE

steg-decode: steg-decode.c error.c error.h ppm.c ppm.h bitset.h eratosthenes.h eratosthenes.c
	$(COMPILER) $(CFLAGS) steg-decode.c -o steg-decode

run: primes primes-i
	./primes && ./primes-i

.PHONY : clean clean_o
clean:
	rm primes primes-i steg-decode *.o