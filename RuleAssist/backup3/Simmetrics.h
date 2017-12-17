#pragma once
#include "Object.h"
#include <iostream>
#include <string>
#include <cassert>
using std::string;
using std::cerr;
using std::endl;
class SimMetrics: public Object
{
public:
	jclass MetricHandler;
	jclass AbstractStringMetric;
	jmethodID createMetric;
	jmethodID getSimilarity;
public:
	SimMetrics(void);
	~SimMetrics(void);
	double similarity(const string& s1, const string& s2, const string& simFuncName);
};
