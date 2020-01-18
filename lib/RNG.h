#ifndef RNG__H
#define RNG__H

#include "stdio.h"
#include "stdlib.h"
#include "memoria.h"
#include "macros_neural.h"
#include "RNGCONFIG.h"
  	
typedef struct{
	double *dna;//pesos
	int dna_len;
	int *arquitetura;
	int arquitetura_len;
	
	void *p;// usado para atribuir uma strutura para modelagem
	int p_isdinamic;//se deve liberar p
	double pontuacao;
}RNG;

RNG newRNG(int *arquitetura,int len){
	RNG r = {};
	FILE *f;
	int i;
	for(i=0;i<len-1;i++){
		r.dna_len+= (arquitetura[i]+1)*arquitetura[i+1];
	}
	r.arquitetura_len=len;
	r.arquitetura = (int *) alocar(r.arquitetura_len, sizeof(int));
	r.dna = (double *) alocar(r.dna_len, sizeof(double));
	
	COPIA_VETOR(r.arquitetura, arquitetura, r.arquitetura_len);
	
	for(i=0;i<r.dna_len;i++)
		r.dna[i] = pesoAleatorio();
	return r;
	
	
}

RNG loadRNG(const char * fileToload){
	RNG r={};
	FILE *f;
	if(fileToload && (f = fopen(fileToload, "rb")) ){
		fread(&r.arquitetura_len, sizeof(int), 1, f);
		fread(&r.dna_len, sizeof(int), 1, f);
		
		r.arquitetura = (int *) alocar(r.arquitetura_len, sizeof(int));
		r.dna = (double *) alocar(r.dna_len, sizeof(double));
	
		fread(r.arquitetura, r.arquitetura_len, sizeof(int), f);
		fread(r.dna, r.dna_len, sizeof(double), f);
	}
	return r;
}

void salveRNG(RNG r,const char * fileToSave){
	FILE *f;
	if(fileToSave && (f = fopen(fileToSave, "wb")) ){
		fwrite(&r.arquitetura_len, sizeof(int), 1, f);
		fwrite(&r.dna_len, sizeof(int), 1, f);
		fwrite(r.arquitetura, r.arquitetura_len, sizeof(int), f);
		fwrite(r.dna, r.dna_len, sizeof(double), f);
	}
}

void freeRNG(RNG r){
	liberar(r.dna);
	liberar(r.arquitetura);
	if (r.p_isdinamic)liberar(r.p);
}

void eval(RNG r,double *input,double *output){
	double *o=0,*inp=0;
	double soma;
	int i,j,k=0,a;

	inp = (double *)alocar(r.arquitetura[0]+1,sizeof(double));
	inp = inp+1;COPIA_VETOR(inp, input, r.arquitetura[0]);inp=inp-1;
	inp[0] = 1;
	
	for(a=0;a<r.arquitetura_len-2;a++){
		liberar(o);
		o = (double *) alocar(r.arquitetura[a+1], sizeof(double));
		for(j=0;j<r.arquitetura[a+1];j++){// neuronios camada a+1
			for(i=0;i<r.arquitetura[a]+1;i++){//neuronios da camada a
				o[j] += inp[i]*r.dna[k+j+i*r.arquitetura[a+1]];
			}
			if(a==r.arquitetura_len-2)
			   o[j] = funcaoAtivacaoSaida(o[j]);
			else
			   o[j] = funcaoAtivacaoEscondida(o[j]);
			
		}
		liberar(inp);
		inp = (double *)alocar(r.arquitetura[a+1]+1,sizeof(double));
		inp = inp+1;COPIA_VETOR(inp, o, r.arquitetura[a+1]);inp=inp-1;
		inp[0] = 1;
		
		k+= (r.arquitetura[a]+1)*r.arquitetura[a+1];
	}
	liberar(inp);
	COPIA_VETOR(output, o, r.arquitetura[r.arquitetura_len-1]);
	liberar(o);
}

void randomMutation(RNG *redes,int len,double *rangeMutation){
	/**
	Esta funcao supoe que todas as redes possui mesma arquitetura
	Encontrar a melhor rede e clona-la
	aplicar mutacoes randomicas
	*/
	
	RNG *melhor =redes;
	double media =0;
	int tipo,indice,numeroMutacao;
	
	// achar a media da pontuacao
	//FORI(iter,0,len,media += redes[iter].pontuacao);
	//media /= len;
	
	//achar o melhor
	FORI(iter,1,len,if(redes[iter].pontuacao>melhor->pontuacao)melhor = redes+iter);
	// copiar dna
	FORI(i,0,len,COPIA_VETOR(redes[i].dna,melhor->dna,melhor->dna_len));
	//mutacao aa partir do 2 dna mantendo intacto o melhor anterior
	
	FORI(i,1,len,
		numeroMutacao = (randomInt()%(int)*rangeMutation)+1;
		FORI(k,0,numeroMutacao,
			tipo = randomInt()%3;
			indice = randomInt()%redes[i].dna_len;
			switch(tipo){
				case 0:// mudar peso
					redes[i].dna[indice] = pesoAleatorio();break;
				case 1:// multiplicacao aleatoria
					redes[i].dna[indice] *= randomDouble()+0.5;break;
                case 2:// Soma aleatoria
                	redes[i].dna[indice] += randomDouble();break;
			}
		);
	);
	*rangeMutation = *rangeMutation *0.99;
	if(*rangeMutation<20) *rangeMutation=20;
}

#endif
