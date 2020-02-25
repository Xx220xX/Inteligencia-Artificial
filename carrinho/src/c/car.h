#include"../rng/fisica.c"
#include"../rng/RNG.H"
#include "constantes.h"


typedef struct {
	P centro;
	P ponta;
	int classe;
	int id;// index 
	int alive;
	double v;// velocidade 
	double av;// velocidade angular
	double fe,fd;
	double dist[5];
	double tempo_parado;
	double tempoTotal  ;
	double points;
	RNG rng;
}Carro;

void setComando(double *comando,Carro *c){// comando[0] frente roda esquerda , comando[2] frente roda direita  comando[1] tras roda esquerda, comando[3] tras roda direita
	int i=0;
	for(i=0;i<4;i++)comando[i] = comando[i]<0.4?0:comando[i];
	if(comando[0]>comando[1])c->fe = 1;
	else c->fe = comando[1]>0?1:0;
	if(comando[2]>comando[3])c->fd = 1;
	else c->fe = comando[3]>0?1:0;
	if(!c->fe&&!c->fd)	c->tempo_parado +=DT;
	else c->tempo_parado = 0;
}

/**
@param input : deve conter 7 posicoes que indicam o numero de sensores
 as 5 primeiras correspondem as 5 ultimas leituras de distancia
 a 6 correspode ao tempo que esta parado
 a 7 corresponde ao sensor de linha quando fica 3 cm de distancia da borda
*/
void getInput(Carro *c,Carro *c2,double input[7] ){
	int i =0 ;
	for(i=1;i<5;i++)c->dist[i-1] = c->dist[i];
	P liga = Psub(c->centro,c2->centro);
	P rt = Psub(c->ponta,c->centro);
	double dist = Pabs(liga);
	double angle = PmultInte(liga,rt)/(Pabs(rt)*dist);
	if(dabs(angle) <= atan2(LARGURA,COMPRIMENTO)){
		c->dist[4] = dist ;
	}else c->dist[4] = -1;
	
	for(i=0;i<5;i++)input[i] = c->dist[i];
	input[5] = c->tempo_parado;
	P centroCirculo = {c->centro.x - RAIO,c->centro.y- RAIO};
	if(Pabs(centroCirculo)>RAIO - BORDA){
		input[6] = 1;
	}
		
}
void chekAlive(Carro *c1,Carro *c2){
	if(c1->tempo_parado*TEMPO_MAXIMO_PARADO>=TEMPO_MAXIMO_PARADO){
		c1->alive =  0;
		c2->alive =  0;
		c1->points = c1->tempoTotal;
		c2->points = c1->tempoTotal+1;
		return;
	}
	if(c2->tempo_parado*TEMPO_MAXIMO_PARADO>=TEMPO_MAXIMO_PARADO){
		c1->alive =  0;
		c2->alive =  0;
		c1->points = c1->tempoTotal+1;
		c2->points = c1->tempoTotal;
		return;
	}
	
	P centroCirculo = {c1->centro.x - RAIO,c1->centro.y- RAIO};
	if(Pabs(centroCirculo)>RAIO){
		c1->alive =  0;
		c2->alive =  0;
		c1->points = c1->tempoTotal;
		c2->points = c1->tempoTotal+1;
		return;
	}
	centroCirculo.x = c2->centro.x-RAIO;
	centroCirculo.y = c2->centro.y-RAIO;
	if(Pabs(centroCirculo)>RAIO){
		c1->alive =  0;
		c2->alive =  0;
		c1->points = c1->tempoTotal+1;
		c2->points = c1->tempoTotal;	
	}
}

