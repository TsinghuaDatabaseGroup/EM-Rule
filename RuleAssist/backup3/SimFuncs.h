#pragma once
#include <string> 
#include <set>
#include <vector>
#include <iostream>
#include <cmath>
#include "Simmetrics.h"

using namespace std;
const unsigned char PREFIXCHAR = 156; // pound
const unsigned char SUFFIXCHAR = 190; // yen
class SimFuncs{
	static SimMetrics simMetrics;
private:
	static void strToGrams(const string &s, set<string> &res, unsigned q, unsigned char st, unsigned char en);
	static void strToGrams(const string &s, set<string> &res, unsigned q);
	static void strToTokens(const string &s, set<string> &res, const string &delims=" ,");
public:
	static unsigned ed(const string &s1, const string &s2);
	static unsigned edSwap(const string &s1, const string &s2);
	static double equal(const string &s1, const string &s2);
	static double ned(const string &s1, const string &s2);
	static double nedSwap(const string &s1, const string &s2);
	static double cosineGram(const string &s1, const string &s2, unsigned gramLen);
	static double jaccardGram(const string &s1, const string &s2, unsigned gramLen);
	static double diceGram(const string &s1, const string &s2, unsigned gramLen);
	static double overlapGram(const string& s1, const string& s2, unsigned gramLen);
	static double cosineToken(const string &s1, const string &s2);
	static double jaccardToken(const string &s1, const string &s2);
	static double diceToken(const string &s1, const string &s2);
	static double overlapToken(const string& s1, const string& s2);
	static double similarityFuncName(const string& s1, const string& s2, const string& simFuncName);
};


