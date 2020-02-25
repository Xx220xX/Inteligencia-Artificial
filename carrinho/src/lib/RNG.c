//
// Created by PC on 24/02/2020.
//

#include "easyJava.h"
#include "RNG.h"
#include "../rng/RNG.h"
#include "stdio.h"
JNIEXPORT void JNICALL Java_RNG_init(JNIEnv *env, jobject this) {
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
    printf("init function has called with success");
}