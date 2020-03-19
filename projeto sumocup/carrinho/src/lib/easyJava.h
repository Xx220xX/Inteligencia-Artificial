#ifndef EASY_JAVA
#define EASY_JAVA
#include<jni.h>
int easy_getInt(JNIEnv *env, jclass obj,const char *varName){
    int ans = 0;
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid  = (*env)->GetFieldID(env,cls,varName,"I");
    ans = (*env)->GetIntField(env,obj,fid);
    return ans;
}
double easy_getDouble(JNIEnv *env, jobject obj,const char* varName){
           double ans = 0;
           jclass cls = (*env)->GetObjectClass(env, obj);
           jfieldID fid  = (*env)->GetFieldID(env,cls,varName,"D");
           ans = (*env)->GetDoubleField(env,obj,fid);
           return ans;
}
/**
@param fullClassName adicione 'L ' antes do nome da classe
*/
jobject easy_getObject(JNIEnv *env, jobject obj,const char *varName, const char* fullClassName){
    jobject ans;
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid  = (*env)->GetFieldID(env,cls,varName,fullClassName);
    ans = (*env)->GetObjectField(env,obj,fid);
    return ans;
}



#endif