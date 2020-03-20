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
    FILE *f;
    while (!(f = fopen("../../../stream/init.car", append ? "a" : "w")));

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
    FILE *f;
    while (!(f = fopen("../../../stream/update.car", append ? "a" : "w")));
//    printf("save\n");
    fprintf(f, "ca[%d].update(createVector(%lf,%lf),createVector(%lf,%lf),%s);\n", id, c1->centro.x, c1->centro.y,
            c1->ponta.x, c1->ponta.y, c1->alive ? "true" : "false");
    fprintf(f, "cb[%d].update(createVector(%lf,%lf),createVector(%lf,%lf),%s)\n", id, c2->centro.x, c2->centro.y,
            c2->ponta.x, c2->ponta.y, c2->alive ? "true" : "false");

    fclose(f);
}

#include "string.h"

#define  EQ(x) all || !strcmp(esc,x)


void evalue(Carro *c1, Carro *c2) {
    char esc[250];
    int all = 0;
    Carro *c = c1;
    for (;;) {
        scanf("%s", esc);
        if (EQ("break"))break;
        if (EQ("c1"))c = c1;
        if (EQ("c2"))c = c2;
        if (EQ("getposition")) {
            printf("c =(%.4lf,%.4lf) p =(%.4lf,%.4lf)", c->centro.x, c->centro.y, c->ponta.x, c->ponta.y);
        }
        if (EQ("setposition")) {
            printf("c.x,c.y = ");
            scanf("%lf,%lf", &c->centro.x, &c->centro.y);
            printf("p.x,p.y = ");
            scanf("%lf,%lf", &c->ponta.x, &c->ponta.y);
        }
        if (EQ("setAlive"))c->alive = !c->alive;
        if (EQ("update"))printCar(c1, c2, 0, 0);

    }
}

int main_debug() {
    int arquitetura[] = {NUMERO_DE_ENTRADAS, 6, 5, 4, NUMERO_DE_SAIDAS};
    RNG r[2] = {newRNG(arquitetura, 5), newRNG(arquitetura, 5)};
    Carro c1 = newCarro(r), c2 = newCarro(r + 1);
    initprintCar(&c1, &c2, 0, 0);

    char esc[250] = {0};
    double input[NUMERO_DE_ENTRADAS * 2];
    double output[NUMERO_DE_SAIDAS * 2];
    clock_t t0;
    int all;
    for (;;) {
        printf("opcoes:[evalue, entrada, eval, comando, fisica, vivo, update, break]\nescolha: ");
        scanf("%s", esc);
        t0 = clock();
        all = 0;
        if (EQ("break"))break;
        if (EQ("evalue"))evalue(&c1, &c2);
        if (EQ("all")) all = 1;

        if (EQ("entrada")) {
            getInput(&c1, &c2, input);
            getInput(&c2, &c1, input + NUMERO_DE_ENTRADAS);
        }
        if (EQ("eval")) {
            eval(r[0], input, output);
            eval(r[1], input + NUMERO_DE_ENTRADAS, output + NUMERO_DE_SAIDAS);
        }
        if (EQ("comando")) {
            setComando(output, &c1);
            setComando(output + NUMERO_DE_SAIDAS, &c2);
        }
        if (EQ("fisica")) {
            aplicarFisica(&c1, &c2);
        }
        if (EQ("vivo")) chekAlive(&c1, &c2);

        if (EQ("update")) printCar(&c1, &c2, 0, 0);
        printf("Tempo para operacao: %ld ms\n\n", clock() - t0);
    }

    freeRNG(r[0]);
    freeRNG(r[1]);
    return 0;
}

#include <windows.h>

DWORD WINAPI ThreadFunc(void *data) {
    int *run = data;
    for (; *run;) {
        scanf("%d", run);
    }
    return 0;
}


int main_run() {
    int arquitetura[] = {NUMERO_DE_ENTRADAS, 6, 5, 4, NUMERO_DE_SAIDAS};
    RNG r[2] = {newRNG(arquitetura, 5), newRNG(arquitetura, 5)};
    Carro c1 = newCarro(r), c2 = newCarro(r + 1);
    initprintCar(&c1, &c2, 0, 0);
    int run = 1;
    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, &run, 0, NULL);
    for (; run;) {
        double input[NUMERO_DE_ENTRADAS * 2];
        double output[NUMERO_DE_SAIDAS * 2];
        getInput(&c1, &c2, input);
        getInput(&c2, &c1, input + NUMERO_DE_ENTRADAS);
        eval(r[0], input, output);
        eval(r[1], input + NUMERO_DE_ENTRADAS, output + NUMERO_DE_SAIDAS);
        setComando(output, &c1);
        setComando(output + NUMERO_DE_SAIDAS, &c2);
        aplicarFisica(&c1, &c2);
        chekAlive(&c1, &c2);
        c1 = newCarro(r);
        c2 = newCarro(r+1);
        printCar(&c1, &c2, 0, 0);

    }
}

int main() {
    main_run();
    return 0;
}