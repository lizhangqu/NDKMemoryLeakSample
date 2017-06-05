//
// Created by 李樟取 on 2017/6/4.
//

#include "native.h"
#include "MemoryTrace.hpp"
#include <fstream>

class MemoryTest {

};

void test(JNIEnv *env, jobject thiz) {
    leaktracer::MemoryTrace::GetInstance().startMonitoringAllThreads();
    MemoryTest *memoryTest = new MemoryTest;
//    delete memoryTest;
    leaktracer::MemoryTrace::GetInstance().stopAllMonitoring();

    std::ofstream out;
    out.open("/sdcard/leaks.out", std::ios_base::out);
    if (out.is_open()) {
        leaktracer::MemoryTrace::GetInstance().writeLeaks(out);
    } else {
        ALOGE("Failed to write to \"leaks.out\"\n");
    }
}

static const JNINativeMethod sMethods[] = {
        {
                const_cast<char *>("test"),
                const_cast<char *>("()V"),
                reinterpret_cast<void *>(test)
        },

};

int registerNativeMethods(JNIEnv *env, const char *className, const JNINativeMethod *methods,
                          const int numMethods) {
    jclass clazz = env->FindClass(className);
    if (!clazz) {
        ALOGE("Native registration unable to find class '%s'\n", className);
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, methods, numMethods) != 0) {
        ALOGE("RegisterNatives failed for '%s'\n", className);
        env->DeleteLocalRef(clazz);
        return JNI_FALSE;
    }
    env->DeleteLocalRef(clazz);
    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    registerNativeMethods(env, CLASSNAME, sMethods, NELEM(sMethods));
    return JNI_VERSION_1_6;
}
