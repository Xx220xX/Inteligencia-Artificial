//
// Created by Xx220xX on 25/02/2020.
//

#ifndef LIB_RNG_CONSTRUCTOR_H
#define LIB_RNG_CONSTRUCTOR_H

#include "RNG_type.h"
#include "memoria.h"
#include "macros_neural.h"
#include "RNGCONFIG.h"
#include "RNG_free.h"

RNG newRNG(int *arquitetura, int len) {
    RNG r = {};
    FILE *f;
    int i;
    for (i = 0; i < len - 1; i++) {
        r.dna_len += (arquitetura[i] + 1) * arquitetura[i + 1];
    }
    r.arquitetura_len = len;
    r.arquitetura = (int *) alocar(r.arquitetura_len, sizeof(int));
    r.dna = (double *) alocar(r.dna_len, sizeof(double));

    COPIA_VETOR(r.arquitetura, arquitetura, r.arquitetura_len);

    for (i = 0; i < r.dna_len; i++)
        r.dna[i] = pesoAleatorio();
    return r;


}


#endif //LIB_RNG_CONSTRUCTOR_H
