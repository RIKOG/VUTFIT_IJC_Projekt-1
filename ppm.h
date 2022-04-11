// ppm.h
// Riesenie IJC-DU1, priklad b), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#include <stdio.h>
struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);