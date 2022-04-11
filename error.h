// error.h
// Riesenie IJC-DU1, priklad b), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);