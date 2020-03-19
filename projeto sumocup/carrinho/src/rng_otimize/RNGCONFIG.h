#ifndef RNGCONFIG_H
#define RNGCONFIG_H
#include "stdlib.h"
#include "math.h"

typedef
unsigned long long int Bytes8;
typedef struct { Bytes8 a, c, m, rand_max, atual; }LCG;
static LCG  lcg={0x5DEECE66DULL,11ULL,1ULL<<48,(1ULL<<48)-1,(long long int)M_PI*(10<<6)};

void semente(LCG * r, Bytes8 seed) {
// constantes do POSIX [de]rand48, glibc [de]rand48[_r]
// ULL transforma a constante ’int’ em ’unsigned long long int’
    r->a = 0x5DEECE66DULL;
    r->c = 11ULL;
    r->m = (1ULL << 48);
    r->rand_max = r->m - 1;
    r->atual = seed;
}




/**
 * Gera numero aleatorio decimal
 * @return um numero randomico E [0,1)
 */




void initRandom(long long int seed){
    semente(&lcg,seed);
}

Bytes8 lcg_rand(LCG * r) {
    r->atual = (r->a * r->atual + r->c) % r->m;
    return r->atual;
}
double lcg_rand_01(LCG * r) {
    return ((double) lcg_rand(r))/(r->rand_max);
}

void updateRand(long long lastN){
    lcg.atual = lastN;
}
long long int getRandom(){
    return lcg.atual;
}
int randomInt() {
    return lcg_rand(&lcg)%(1<<28);
}

/**
 * Gera numero aleatorio decimal
 * @return um numero randomico E [0,1)
 */
double randomDouble(){
	return lcg_rand_01(&lcg);
}

double pesoAleatorio(){
	return randomDouble()*2-1;
}

double funcaoAtivacaoSaida(double x){
	if (x<0)return 0 ;
	return x;
	//return tanh(x);
}
double funcaoAtivacaoEscondida(double x){
	return tanh(x);
}

#endif
