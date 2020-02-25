//
// Created by PC on 24/02/2020.
//

#include "easyJava.h"
#include "RNG.h"
#include "../rng_otimize/RNG_constructor.h"
/*
 * Class:     RNG
 * Method:    init
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_RNG_init(JNIEnv *env, jobject this, jlong seed){
    initRandom(seed);
    jintArray iarr0 = easy_getObject(env, this, "arquitetura", "[I");
    int arquitetura_len = (*env)->GetArrayLength(env, iarr0);
    int *arquitetura = (*env)->GetIntArrayElements(env, iarr0, NULL);
    RNG tempo_rng= newRNG(arquitetura,arquitetura_len);
     jdoubleArray darr0 = (*env)->NewDoubleArray(env,tempo_rng.dna_len);//array de doubles para dna
    (*env)->SetDoubleArrayRegion(env, darr0, 0, tempo_rng.dna_len, tempo_rng.dna);
    jclass mycls = (*env)->GetObjectClass(env, this);
    jfieldID fid  = (*env)->GetFieldID(env,mycls,"dna","[D");
    (*env)->SetObjectField(env, this, fid, darr0);
    freeRNG(tempo_rng);
    return getRandom();
}