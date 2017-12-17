#include "Simmetrics.h"

SimMetrics::SimMetrics(void)
{
	if (!Object::BeginJVM()){
		cerr << "JVM is not created" << endl;
		exit(-1);
	}
	MetricHandler = Object::env->FindClass("uk/ac/shef/wit/simmetrics/metrichandlers/MetricHandler");
	createMetric = Object::env->GetStaticMethodID(MetricHandler, "createMetric", "(Ljava/lang/String;)Luk/ac/shef/wit/simmetrics/similaritymetrics/AbstractStringMetric;");

	AbstractStringMetric = Object::env->FindClass("uk/ac/shef/wit/simmetrics/similaritymetrics/AbstractStringMetric");
	getSimilarity = Object::env->GetMethodID(AbstractStringMetric, "getSimilarity", "(Ljava/lang/String;Ljava/lang/String;)F");

	if (MetricHandler==NULL || createMetric==NULL || AbstractStringMetric == NULL || getSimilarity == NULL)
	{
		cerr << "Can't find simmetrics.jar" << endl;
		exit(-1); 
	}
}

SimMetrics::~SimMetrics(void)
{
	Object::EndJVM();
}

double SimMetrics::similarity(const string& s1, const string& s2, const string& simFuncName)
{
	jstring jstrSimFuncName = Object::env->NewStringUTF(simFuncName.c_str());	
	jobject metric = Object::env->CallStaticObjectMethod(MetricHandler, createMetric, jstrSimFuncName);	
	if (metric == NULL) // no function named simFuncName is found
	{
		cerr << "Can't find " << simFuncName << endl;
		assert(0);
		return -1.0;
	}

	jstring jstr1 = Object::env->NewStringUTF(s1.c_str());
	jstring jstr2 = Object::env->NewStringUTF(s2.c_str());

	jfloat simValue =Object::env->CallFloatMethod(metric,getSimilarity,jstr1, jstr2);
	Object::env->DeleteLocalRef(jstrSimFuncName);
	Object::env->DeleteLocalRef(jstr1);
	Object::env->DeleteLocalRef(jstr2);
	Object::env->DeleteLocalRef(metric);
	Object::env->DeleteLocalRef(metric);
	return double(simValue);
}
