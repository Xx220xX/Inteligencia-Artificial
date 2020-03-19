//
// Created by PC on 25/02/2020.
//

#ifndef LIB_RNG_FREE_H
#define LIB_RNG_FREE_H

void freeRNG(RNG r) {
    liberar(r.dna);
    liberar(r.arquitetura);
    r.dna = 0;
    r.arquitetura = 0;
}

#endif //LIB_RNG_FREE_H
