//
// Created by Xx220xX on 25/02/2020.
//

#ifndef LIB_RNG_TYPE_H
#define LIB_RNG_TYPE_H

typedef struct{
    double *dna;//pesos
    int dna_len;
    int *arquitetura;
    int arquitetura_len;

//    void *p;// usado para atribuir uma strutura para modelagem
//    int p_isdinamic;//se deve liberar p
    double pontuacao;
}RNG;
#endif //LIB_RNG_TYPE_H
