#include <jni.h>
#include "react-native-memcachejsi.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_reactnativememcachejsi_MemcachejsiModule_nativeMultiply(JNIEnv *env, jclass type, jint a, jint b) {
    return memcachejsi::multiply(a, b);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativememcachejsi_MemcachejsiModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi) {
    auto runtime = reinterpret_cast<facebook::jsi::Runtime *>(jsi);
    if (runtime)
    memcachejsi::install(*runtime);
}
