// error.c
// Riesenie IJC-DU1, priklad b), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#include "error.h"
#include <stdarg.h>
#include <stdio.h>

void warning_msg(const char *fmt, ...){
    va_list ap;
    fprintf(stderr,"CHYBA: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr,"\n");
}

void error_exit(const char *fmt, ...){
    va_list ap;
    fprintf(stderr,"CHYBA: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    exit(1);
}