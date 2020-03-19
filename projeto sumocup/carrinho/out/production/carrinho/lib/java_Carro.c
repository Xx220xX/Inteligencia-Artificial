#include "java_Carro.h"
#include "stdio.h"
#include "../cpp/car.h"
#include "easyJava.h"

JNIEXPORT void JNICALL Java_java_Carro_update
  (JNIEnv *env, jclass thiscls, jobject jcar1, jobject jcar2){
        Carro c1 = {0}, c2 = {0};
        jobject tmp ;

        // centro de c1
        tmp  = easy_getObject(env,jcar1,"centro","L java.Carro.P");
        c1.centro.x = easy_getDouble(env,tmp,"x");
        c1.centro.y = easy_getDouble(env,tmp,"y");
        printf("from c (%g %g) \n",c1.centro.x,c1.centro.y);

  }