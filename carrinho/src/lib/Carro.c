
#include "Carro.h"
#include "stdio.h"
#include "../c/car.h"
#include "easyJava.h"

RNG j2cRNG(JNIEnv *env, jobject rng) {
    RNG temp_rng = {0};
    // dna
    //printf("\nvou ler o array aqui man\n");
    jdoubleArray d_ar = easy_getObject(env, rng, "dna", "[D");
    temp_rng.dna_len = (*env)->GetArrayLength(env, d_ar);
    temp_rng.dna = (*env)->GetDoubleArrayElements(env, d_ar, NULL);
//
    // arquitetura

    jintArray d_arint = easy_getObject(env, rng, "arquitetura", "[I");
    temp_rng.arquitetura_len = (*env)->GetArrayLength(env, d_arint);
    temp_rng.arquitetura = (*env)->GetIntArrayElements(env, d_arint, NULL);
    return temp_rng;
}

Carro j2cCarro(JNIEnv *env, jobject carro) {
    Carro c = {0};
    jobject tmp;
    // centro
    tmp = easy_getObject(env, carro, "centro", "LCarro$P;");
    c.centro.x = easy_getDouble(env, tmp, "x");
    c.centro.y = easy_getDouble(env, tmp, "y");
    //ponta
    tmp = easy_getObject(env, carro, "ponta", "LCarro$P;");
    c.ponta.x = easy_getDouble(env, tmp, "x");
    c.ponta.y = easy_getDouble(env, tmp, "y");
    c.id = easy_getInt(env, carro, "id");
    c.v = easy_getDouble(env, carro, "v");
    c.av = easy_getDouble(env, carro, "av");
    c.fe = easy_getDouble(env, carro, "fe");
    c.fd = easy_getDouble(env, carro, "fd");
    c.tempo_parado = easy_getDouble(env, carro, "tempo_parado");
    c.tempoTotal = easy_getDouble(env, carro, "tempoTotal");

    // pegar distancias
    jdoubleArray d_ar = easy_getObject(env, carro, "dist", "[D");
    double *arr = (*env)->GetDoubleArrayElements(env, d_ar, NULL);
    int i;
    for (i = 0; i < 5; i++)c.dist[i] = arr[i];
    // pegar RNG
    tmp = easy_getObject(env, carro,"rng", "LRNG;");
    c.rng = j2cRNG(env,tmp);
    return c;
}

/*
 * Class:     Carro
 * Method:    update
 * Signature: (LCarro;LCarro;J)J
 */
JNIEXPORT jlong JNICALL Java_Carro_update(JNIEnv *env, jclass tcls, jobject jcar1, jobject jcar2,jlong seed ){
    initRandom(seed);
    Carro c1 = j2cCarro(env,jcar1), c2 = j2cCarro(env,jcar2);
    return getRandom();
}