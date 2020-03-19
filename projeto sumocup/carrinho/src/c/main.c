#include <stdio.h>
#include "car.h"
#include "time.h"

Carro newCarro(RNG *r) {
    Carro c = {0};
    double angle = randomDouble() * 2 * M_PI;
    c.centro.x = cos(angle);
    c.centro.y = sin(angle);
    c.ponta.x = cos(angle);
    c.ponta.y = sin(angle);
    c.centro = Padd(PmulEsc(c.centro, RAIO - COMPRIMENTO / 2), (P) {RAIO, RAIO});
    c.ponta = Padd(PmulEsc(c.ponta, RAIO - COMPRIMENTO), (P) {RAIO, RAIO});
    c.rng = r;
    return c;
}

/** função para mostrar os carros na web (debub é implementada em java no projeto)*/
void initprintCar(Carro *c1, Carro *c2, int id, int append) {
    FILE *f = fopen("../../../stream/init.car", append ? "a" : "w");
    fprintf(f, "ca[%d] = new Carro(createVector(%lf,%lf),createVector(%lf,%lf));\n", id, c1->centro.x, c1->centro.y,
            c1->ponta.x, c1->ponta.y);
    fprintf(f, "cb[%d] = new Carro(createVector(%lf,%lf),createVector(%lf,%lf))\n", id, c2->centro.x, c2->centro.y,
            c2->ponta.x, c2->ponta.y);
//    fprintf(f, "a,%d,%lf,%lf,%lf,%lf\n", id, c1->centro.x, c1->centro.y, c1->ponta.x, c1->ponta.y, c1->alive);
//    fprintf(f, "b,%d,%lf,%lf,%lf,%lf\n", id, c2->centro.x, c2->centro.y, c2->ponta.x, c2->ponta.y, c2->alive);
    fclose(f);
}

/** função para mostrar os carros na web (debub é implementada em java no projeto)*/
void printCar(Carro *c1, Carro *c2, int id, int append) {
    FILE *f = fopen("../../../stream/update.car", append ? "a" : "w");
    if (!f)
        return;
    fprintf(f, "ca[%d].update(createVector(%lf,%lf),createVector(%lf,%lf),%s);\n", id, c1->centro.x, c1->centro.y,
            c1->ponta.x, c1->ponta.y, c1->alive ? "true" : "false");
    fprintf(f, "cb[%d].update(createVector(%lf,%lf),createVector(%lf,%lf),%s)\n", id, c2->centro.x, c2->centro.y,
            c2->ponta.x, c2->ponta.y, c2->alive ? "true" : "false");

    fclose(f);
}

typedef struct {
    Carro c1;
    Carro c2;
    int id;
} Duplas;


int loop(Duplas *d, int n) {
    int i;
    static int iteracao = 100000;
    int mortos = 0;
    for (i = 0; i < n; i++) {
        play(&d[i].c1, &d[i].c2);
        if (!d[i].c1.alive)mortos++;
        printCar(&d[i].c1, &d[i].c2, i, i != 0);
    }
    if (mortos == n)return 0;
    return --iteracao;
}

#define N 40

int main2() {
    int arquitetura[4] = {7, 5, 4, 4};
    RNG rng[2] = {newRNG(arquitetura, 4), newRNG(arquitetura, 4)};
    Duplas d = {newCarro(rng), newCarro(rng + 1), 0};
    colidiuQuadrado1(d.c1.centro, d.c1.ponta, d.c2.centro, d.c2.ponta, LARGURA, COMPRIMENTO);
    freeRNG(rng[0]);
    freeRNG(rng[1]);
}

int main() {
    Duplas duplas[N] = {0};
    int i, arquitetura[4] = {7, 5, 4, 4};
    RNG redesa[N], redesb[N];
    initRandom(time(0));

    for (i = 0; i < N; i++) {
        redesa[i] = newRNG(arquitetura, 4);
        redesb[i] = newRNG(arquitetura, 4);;
        duplas[i].c1 = newCarro(redesa + i);
        duplas[i].c2 = newCarro(redesb + i);
    }
    printf("inicializado carros\n");
    for (i = 0; i < N; i++) {
        initprintCar(&duplas[i].c1, &duplas[i].c2, i, i != 0);
    }
    printf("salvado\n");


    double r1 = 90, r2 = 90;
    for (i = 0; i < 10000; i++) {
        while (loop(duplas, N));
        printf("loop %d\n", i);
        randomMutation(redesa, N, &r1);
        randomMutation(redesb, N, &r2);
    }

    printf("liberar");
    for (i = 0; i < N; i++) {
        freeRNG(redesa[i]);
        freeRNG(redesb[i]);
    }
    printf("liberado\n");
    return 0;
}
