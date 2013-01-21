/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <assert.h>

jstring stringFromJNI( JNIEnv* env,jobject thiz );

/**
* Table of methods associated with a single class.
*/
static JNINativeMethod gMethods[] = {
        { "stringFromJNI", "()Ljava/lang/String;", (void*)stringFromJNI },//°ó¶¨
};



void callJavaMethod(JNIEnv* env,jobject thiz) {

	jclass class =  (*env)->FindClass(env,"com/example/hellojni/HelloJni");
	jmethodID  method = (*env)->GetMethodID(env,class, "callMeFromJni","()V");
	(*env)->CallVoidMethod(env,thiz, method);

}


/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
jstring stringFromJNI( JNIEnv* env,jobject thiz )
{
	callJavaMethod(env,thiz);
    return (*env)->NewStringUTF(env, "Hello from JNI !");
}

static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
        jclass clazz;
        clazz = (*env)->FindClass(env, className);
        if (clazz == NULL) {
                return JNI_FALSE;
        }
        if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
                return JNI_FALSE;
        }

        return JNI_TRUE;
}

/*
* Register native methods for all classes we know about.
*/
static int registerNatives(JNIEnv* env)
{
        if (!registerNativeMethods(env, "com/example/hellojni/HelloJni", gMethods,
                                 sizeof(gMethods) / sizeof(gMethods[0])))
                return JNI_FALSE;

        return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	 __android_log_print(ANDROID_LOG_DEBUG,"hello-jni","call java jni_onload")  ;

	 JNIEnv* env = NULL;
	 if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
	      return -1;
	  }
	  assert(env != NULL);
	  if (!registerNatives(env)) {//×¢²á
	      return -1;
	  }
	 //And one more thing. Am using Java SE6. so should i put JNI_VERSION_1_6
	 //or JNI_VERSION_1_2 will work
	return JNI_VERSION_1_6;
}

