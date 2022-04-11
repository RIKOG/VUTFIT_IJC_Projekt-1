// ppm.c
// Riesenie IJC-DU1, priklad b), 25.3.2021
// Autor: Richard Gajdosik, FIT
// Prelozene: gcc 9.3

#include <stdio.h>
#include "ppm.h"
#include "error.c"

// format obrazku
// "P6" <ws>+
// <xsizetxt> <ws>+ <ysizetxt> <ws>+
// "255" <ws>
// <binarni data, 3*xsize*ysize bajtu RGB>
// <EOF>

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};
struct ppm * ppm_read(const char * filename){

    char buff[16];
    unsigned xsize = 0, ysize = 0, actual_size = 0, max_size = 8000*8000*3;
    int color = 0, chyba = 0;

    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        warning_msg("Nepodarilo sa otvorit subor", filename);
        return NULL;
    }

    if (!fgets(buff, sizeof(buff), fp)) {
        warning_msg("Nepodarilo sa nacitat data", filename);
        chyba = 1;
    }

    if (buff[0] != 'P' || buff[1] != '6') {
        warning_msg("Zly format, musi byt P6", filename);
        chyba = 1;
    }

    if (fscanf(fp, "%u %u", &xsize, &ysize) != 2) {
        warning_msg("Nespravny format zadania velkosti obrazku", filename);
        chyba = 1;
    }
    if (fscanf(fp, "%d", &color) != 1) {
        warning_msg("Neobsahuje komponent farby", filename);
        chyba = 1;
    }
    if (color != 255) {
        warning_msg("Neobsahuje farby 0 az 255", filename);
        chyba = 1;
    }
    // Skontrolujeme ci sa nevyskytla ziadna chyba pri nacitani dat, ak ano zatvorime subor a vratime null
    if(chyba == 1){
        if (fclose(fp) == EOF) {
            warning_msg("Nepodarilo sa zatvorit subor", filename);
        }
        return NULL;
    }
    // Po spravnom nacitani velkosti si vypocitame realnu velkost
    actual_size = xsize * ysize * 3;

    if(actual_size >= max_size){
        warning_msg("Obrazok prekrocil limit velkosti");
        if (fclose(fp) == EOF) {
            warning_msg("Nepodarilo sa zatvorit subor", filename);
        }
        return NULL;
    }

    // Zacneme allokovat pamat az po tom co sme si overili ze subor je korektny a daju sa z neho citat data
    struct ppm *ptr_struct = malloc(sizeof(struct ppm)+sizeof(char)*3*xsize*ysize);

    if(ptr_struct == NULL){
        if (fclose(fp) == EOF) {
            warning_msg("Nepodarilo sa zatvorit subor", filename);
        }
        warning_msg("Nepodarilo sa allokovat pamat", filename);
        return NULL;
    }

    // Zacneme zapisovat do structu az ked sme si isty ze sa nam podarilo allokovat vsetku potrebnu pamat
    ptr_struct->xsize = xsize, ptr_struct->ysize = ysize;

    // Posunieme sa na dalsi riadok, kedze samotne data obrazku zacinaju az tam
    while (fgetc(fp) != '\n');

    // Citame data
    unsigned long x = fread(ptr_struct->data, sizeof(char), actual_size, fp);
    // Skontrolujeme ci fread nacital presne tolko dat, kolko sme mu prikazali cez actual_size
    if(x != actual_size){
        ppm_free(ptr_struct);
        if (fclose(fp) == EOF) {
            warning_msg("Nepodarilo sa zatvorit subor", filename);
        }
        warning_msg("Chybny format");
        return NULL;
    }

    // Skontrolujeme ci sa nam skutocne podarilo z otvoreneho suboru vytiahnut nejake data
    if(ptr_struct->data == NULL){
        warning_msg("Nepodarilo sa nacitat data", filename);
        if (fclose(fp) == EOF) {
            warning_msg("Nepodarilo sa zatvorit subor", filename);
        }
        ppm_free(ptr_struct);
        return NULL;
    }
    buff[0] = fgetc(fp);
    if(buff[0] != EOF){
        warning_msg("Zly format, subor nekonci EOF", filename);
        return NULL;
    }
    if (fclose(fp) == EOF) {
        warning_msg("Nepodarilo sa zatvorit subor", filename);
    }
    return ptr_struct;
}

void ppm_free(struct ppm *p){
    free(p);
}