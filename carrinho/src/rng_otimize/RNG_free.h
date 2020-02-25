//
// Created by PC on 25/02/2020.
//

#ifndef LIB_RNG_FREE_H
#define LIB_RNG_FREE_H

void freeRNG(RNG r) {
    liberar(r.dna);
    liberar(r.arquitetura);
//    if (r.p_isdinamic)liberar(r.p);
}

#endif //LIB_RNG_FREE_H
