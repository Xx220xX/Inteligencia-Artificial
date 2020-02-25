#include <stdio.h>
#include "car.h"
Carro newCarro(RNG r){
    Carro c={0};
    double  angle = randomDouble()*M_PI;
    c.centro.x = cos(angle)*(RAIO -LARGURA/2);
    c.centro.y = cos(angle)*(RAIO -COMPRIMENTO/2);
    c.centro.x = cos(angle)*(RAIO -LARGURA);
    c.centro.y = cos(angle)*(RAIO -COMPRIMENTO);
    c.rng = r;
}
int main() {
    P c1 = {1, 0},
            p1 = {8, 9},
            c2 = {9, 3},
            p2 = {19, 3};
    Solucao s = colidiuQuadrado(c1, p1, c2, p2, 10, 10);
    Carro car1,car2;
    int arquitetura[] = {7,3,4,4};
    car1 = newCarro(newRNG(arquitetura, 4));
    car2  = newCarro(newRNG(arquitetura, 4));
    printf("%d\n(%g,%g)\n", s.existe, s.ans.x, s.ans.y);
    return 0;
}
