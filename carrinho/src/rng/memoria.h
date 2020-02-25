#ifndef MEMORIA_H_RNG
#define MEMORIA_H_RNG
#include "stdlib.h"

int alocados =0;
void * alocar(int n,int sizen){
	alocados++;
	void *p = calloc(n, sizen);
	if(!p && n*sizen ){
		printf("memoria de %d bytes nao foi alocada\n",n*sizen);
		exit(-1);
	}
	return p;
}
void liberar(void *p){
	if(p){
		free(p);
		alocados--;
	}
}
void MEMORIA_STATE(){
	printf("EXISTEM %d alocacoes ate agr\n",alocados);
}
#endif
