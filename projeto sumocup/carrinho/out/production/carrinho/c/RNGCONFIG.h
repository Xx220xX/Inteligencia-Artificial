#ifndef RNGCONFIG_H
#define RNGCONFIG_H
#include "stdlib.h"
#include "math.h"

long randomInt(){
	return rand();
}
double randomDouble(){
	return rand()/(double)RAND_MAX;
}
double pesoAleatorio(){
	return (rand())/(double)RAND_MAX *20 -10;
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
