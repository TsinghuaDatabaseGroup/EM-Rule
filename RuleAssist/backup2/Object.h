#pragma once
#include "jni.h"


#pragma comment(lib, "jvm.lib") 

class Object
{
public:
	static bool BeginJVM();
	static bool EndJVM();
	Object() {}
	virtual ~Object() {}
protected:
	static JNIEnv* env;
	static JavaVM* jvm;
};



