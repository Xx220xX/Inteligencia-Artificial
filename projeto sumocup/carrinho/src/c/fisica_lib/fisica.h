#ifndef FISICA_LIB_H
#define FISICA_LIB_H

#define copyVet(vetBuff, vetStream, begin, end) do{ int var000001;for(var000001=begin;var000001<end;var000001++)vetBuff[var000001] = vetStream[var000001];}while(0)
#define DISTANCE(a, b) Pabs(Psub(a,b))

typedef struct {
    double x, y;
} P;
typedef struct {
    P ans;
    double t, s;
    int existe;
} Solucao;

void plotClear();

double PmultInte(P u, P v);

void plotLine(double x0, double y0, double x1, double y1);

void plotShow();

double dabs(double n);

P Padd(P p1, P p2);

P PmulEsc(P p, double escalar);

double Pangle(P p);

P PbyAngle(double radAngle);

double Pabs(P p);

P PsetMag(P p, double mag);

double retaParalelas(P d1, P d2);

double distanciaPontoReta(P q, P d, P p);

double distanciaRetas(P d1, P p1, P d2, P p2);

Solucao encontroDeRetas(P d1, P p1, P d2, P p2);

P ProtEixo(P p, double radAngle);

void getConers(P coners[4], P c1, P p1, double larg, double comp);

Solucao colidiuQuadrado(P c1, P p1, P c2, P p2, double largura, double comprimento);


#include"fisica.c"

#endif
