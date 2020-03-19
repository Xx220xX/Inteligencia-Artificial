#include"../rng/fisica.c"
#include"../rng_otimize/RNG.H"
#include "constantes.h"
// help https://www.math10.com/en/geometry/geogebra/fullscreen.html

typedef struct {
    P centro;
    P ponta;
    int classe;
    int id;// index
    int alive;
    double v;// velocidade
    double av;// velocidade angular
    double fe, fd;
    double dist[5];
    double tempo_parado;
    double tempoTotal;
    double points;
    RNG *rng;
} Carro;

void setComando(double *comando,
                Carro *c) {// comando[0] frente roda esquerda , comando[2] frente roda direita  comando[1] tras roda esquerda, comando[3] tras roda direita
    int i = 0;
    for (i = 0; i < 4; i++)comando[i] = comando[i] < 0.4 ? 0 : comando[i];
    if (comando[0] > comando[1])c->fe = 1;
    else c->fe = comando[1] > 0 ? 1 : 0;
    if (comando[2] > comando[3])c->fd = 1;
    else c->fe = comando[3] > 0 ? 1 : 0;
    if (!c->fe && !c->fd) c->tempo_parado += DT;
    else c->tempo_parado = 0;
}

/**
@param input : deve conter 7 posicoes que indicam o numero de sensores
 as 5 primeiras correspondem as 5 ultimas leituras de distancia
 a 6 correspode ao tempo que esta parado
 a 7 corresponde ao sensor de linha quando fica 3 cm de distancia da borda
*/
void getInput(Carro *c, Carro *c2, double input[7]) {
    int i = 0;
    for (i = 1; i < 5; i++)c->dist[i - 1] = c->dist[i];
    P liga = Psub(c->centro, c2->centro);
    P rt = Psub(c->ponta, c->centro);
    double dist = Pabs(liga);
    double angle = PmultInte(liga, rt) / (Pabs(rt) * dist);
    if (dabs(angle) <= atan2(LARGURA, COMPRIMENTO)) {
        c->dist[4] = dist;
    } else c->dist[4] = -1;

    for (i = 0; i < 5; i++)input[i] = c->dist[i];
    input[5] = c->tempo_parado;
    P centroCirculo = {c->centro.x - RAIO, c->centro.y - RAIO};
    if (Pabs(centroCirculo) > RAIO - BORDA) {
        input[6] = 1;
    }

}

void chekAlive(Carro *c1, Carro *c2) {
    c1->rng->pontuacao = c2->rng->pontuacao = c1->points = c2->points = c1->tempoTotal;
    if (c1->tempo_parado * TEMPO_MAXIMO_PARADO >= TEMPO_MAXIMO_PARADO) {
        c1->alive = c2->alive = 0;
        c1->points = c1->tempoTotal;
        c2->points = c1->tempoTotal + 1;
        return;
    }
    if (c2->tempo_parado * TEMPO_MAXIMO_PARADO >= TEMPO_MAXIMO_PARADO) {
        c1->alive = c2->alive = 0;
        c1->points = c1->tempoTotal + 1;
        c2->points = c1->tempoTotal;
        return;
    }

    P centroCirculo = {c1->centro.x - RAIO, c1->centro.y - RAIO};
    if (Pabs(centroCirculo) > RAIO) {
        c1->alive = 0;
        c2->alive = 0;
        c1->points = c1->tempoTotal;
        c2->points = c1->tempoTotal + 1;
        return;
    }
    centroCirculo.x = c2->centro.x - RAIO;
    centroCirculo.y = c2->centro.y - RAIO;
    if (Pabs(centroCirculo) > RAIO) {
        c1->alive = 0;
        c2->alive = 0;
        c1->points = c1->tempoTotal + 1;
        c2->points = c1->tempoTotal;
    }
}



Solucao encontrodeRetaCirculo(P cC,double R,P p1,P p2){


}
/**
 * \Representação
 * \n
 *  ___ p1 ___\n
 * |..................|\n
 * |..................|\n
 * |......c1........|\n
 * |..................|\n
 * |_________|\n\n
 * da ________\n
 * |..................|\n
 * |..................|\n
 * |..................|\n
 * |..................|\n
 * pa________db\n
 * 
 * @param c1 centro do quadrado 1 
 * @param p1 ponto acima do centro 
 * @param c2 
 * @param p2 
 * @param largura 
 * @param comprimento 
 * @return 
 */
Solucao colidiuQuadrado2(P c1, P p1, P c2, P p2, double largura, double comprimento) {
    double dist = Pabs(Psub(c1,c2));// caso distancia seja menor que o comprimento eles colidiram
    Solucao  s = {0};
    if( dist >sqrt(comprimento*comprimento+largura*largura))return s;
     Reta  car1 = RetaByPoints(c1,p1);
     Reta  car2 = RetaByPoints(c2,p2);
     double  angle = (RetaAngle(car1)-M_PI_2)*180.0/M_PI;
     if(angle >)

}
Solucao colidiuQuadrado1(P c1, P p1, P c2, P p2, double largura, double comprimento) {
    P corners[8], // vetor contendo as pontas de ambos quadrados
            vetor2Origem; // vetor para transladar para referencia de PA
    double angle;
    int i;
    P atual;
    Solucao  s={0};
    //find conners
    getCorners(corners, c1, p1, largura, comprimento);
    getCorners(corners + 4, c2, p2, largura, comprimento);
    vetor2Origem = corners[2];
    angle = -Pangle(Psub(corners[1], corners[2]));
    // mudar coordenadas
    for (i = 0; i < 8; i++)corners[i] = ProtEixo(Psub(corners[i], vetor2Origem), angle);
    for(i=0;i<4;i++){
        atual = corners[i+4];
        if(atual.x>largura||atual.x<0)continue;//fora no eixo x;
        if(atual.y>comprimento||atual.y<0)continue;//fora no eixo y;
        // esta dentro
//        encontrodeRetaCirculo()


    }
    return (Solucao) {0};
}
void fisica (Carro *c1,Carro *c2){
    Solucao  s = colidiuQuadrado2(c1->centro,c1->ponta,c1.)
}
void mover(Carro *c1, Carro *c2) {


}

void play(Carro *c1, Carro *c2) {
    if (!c1->alive)return;
    double input[2 * NUMERO_DE_ENTRADAS];
    double output[2 * NUMERO_DE_SAIDAS];
    getInput(c1, c2, input);
    getInput(c2, c1, input + NUMERO_DE_ENTRADAS);
    eval(*c1->rng, input, output);
    eval(*c2->rng, input + NUMERO_DE_ENTRADAS, output + NUMERO_DE_SAIDAS);
    setComando(output, c1);
    setComando(output + NUMERO_DE_SAIDAS, c2);
    fisica(c1,c2);
    mover(c1, c2);
    chekAlive(c1, c2);
}
