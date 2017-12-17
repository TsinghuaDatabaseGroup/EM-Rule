#include "Object.h"



JNIEnv* Object::env=NULL;
JavaVM* Object::jvm=NULL;


bool Object::BeginJVM()
{
	JavaVMOption options[3];
	JavaVMInitArgs vm_args;

	//parameters
	options[0].optionString="-Xmx128m";
	options[1].optionString="-Verbose:gc";
	options[2].optionString="-Djava.class.path=simmetrics.jar";

	vm_args.version=JNI_VERSION_1_4;
	vm_args.options=options;
	vm_args.nOptions=3;
	 vm_args.ignoreUnrecognized = JNI_TRUE;

	int res = JNI_CreateJavaVM(&jvm,(void **)&env, &vm_args);
	return res>=0? true: false;
}

bool Object::EndJVM()
{
	//close JVM
	jvm->DestroyJavaVM();
	env =NULL;
	jvm = NULL;
	return true;
}
