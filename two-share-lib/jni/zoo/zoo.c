#include "bar.h"
#include <jni.h>

int something(void)
{
    return bar(42);
}

jint Java_com_example_twosharelib_MainActivity_callZooMoudle
  (JNIEnv * env, jobject thiz) 
{
	return something();  
}
