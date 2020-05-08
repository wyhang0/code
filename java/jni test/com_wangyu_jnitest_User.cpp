#include "com_wangyu_jnitest_User.h"
#include <string.h>

JNIEXPORT jint JNICALL Java_com_wangyu_jnitest_User_getAge(JNIEnv *env, jclass obj, jint base)
{
    return base + 10;
}

JNIEXPORT jstring JNICALL Java_com_wangyu_jnitest_User_getName(JNIEnv *env, jclass obj, jstring name)
{
    const char* str = env->GetStringUTFChars(name, 0);
    char cap[128];
    strcpy(cap, str);
    env->ReleaseStringChars(name, 0);
    return env->NewStringUTF(cap);
}

JNIEXPORT jstring JNICALL Java_com_wangyu_jnitest_User_getAddress(JNIEnv *env, jclass obj, jstring address)
{
    const char* str = env->GetStringUTFChars(address, 0);
    char cap[128];
    strcpy(cap, str);
    env->ReleaseStringChars(address, 0);
    return env->NewStringUTF(cap);
}
