//
// Created by Xx220xX on 25/02/2020.
//

#ifndef LIB_RNG_FILE_H
#define LIB_RNG_FILE_H

#include "RNG_type.h"
#include "memoria.h"
#include "macros_neural.h"
#include "RNG_free.h"
#include "stdio.h"



RNG loadRNG(const char *fileToload) {
    RNG r = {};
    FILE *f;
    if (fileToload && (f = fopen(fileToload, "rb"))) {
        fread(&r.arquitetura_len, sizeof(int), 1, f);
        fread(&r.dna_len, sizeof(int), 1, f);

        r.arquitetura = (int *) alocar(r.arquitetura_len, sizeof(int));
        r.dna = (double *) alocar(r.dna_len, sizeof(double));

        fread(r.arquitetura, r.arquitetura_len, sizeof(int), f);
        fread(r.dna, r.dna_len, sizeof(double), f);
    }
    return r;
}

void salveRNG(RNG r, const char *fileToSave) {
    FILE *f;
    if (fileToSave && (f = fopen(fileToSave, "wb"))) {
        fwrite(&r.arquitetura_len, sizeof(int), 1, f);
        fwrite(&r.dna_len, sizeof(int), 1, f);
        fwrite(r.arquitetura, r.arquitetura_len, sizeof(int), f);
        fwrite(r.dna, r.dna_len, sizeof(double), f);
    }
}


#endif //LIB_RNG_FILE_H
