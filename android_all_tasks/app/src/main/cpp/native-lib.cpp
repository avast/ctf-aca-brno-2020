#include <jni.h>
#include <string>
#include "secrets.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_avast_adventure_MainActivity_stringFromJNI(JNIEnv *env,jobject /* this */) {
    std::string JNI_API_KEY = ADVENTURE_KEY_FEATURE;
    return env->NewStringUTF(JNI_API_KEY.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_avast_adventure_AvastApplication_stringFromJNI(JNIEnv *env,jobject /* this */) {
    std::string JNI_API_KEY = ADVENTURE_KEY_PREFS;
    return env->NewStringUTF(JNI_API_KEY.c_str());
}