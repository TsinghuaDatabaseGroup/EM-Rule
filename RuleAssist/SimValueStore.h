#pragma once
#include "TrainData.h"
#include "SimFuncs.h"
#include "GlobFunc.h"
#include <map>
#include <vector>
using namespace std;
//#include "simFuncs.h"
class SimValueStore
{
	vector<map<int, vector<int> > > tableSimValues;  // attr --> sim --> tuple
	TrainData& trainData;
	int row,column;
public:
	SimValueStore(TrainData& _trainData)
		:trainData(_trainData)
	{
		row = _trainData.getDataSize();
		column = trainData.getAttrNum(); 
		tableSimValues.resize(column);
	}
	void compute(int pos, int simFunc);
	void computeColumn0(int pos, vector<int>& columnSimValues, double (*similarity)(const string& s1, const string& s2));
	void computeColumn1(int pos, vector<int>& columnSimValues, unsigned gramLen, double (*similarity)(const string& s1, const string& s2, unsigned gramLen));
	void computeColumn2(int pos, vector<int>& columnSimValues, const string& simFuncName, double (*similarity)(const string& s1, const string& s2, const string& simFuncName));
	const vector<int>& columnSimValues(int pos, int simFunc) {return tableSimValues[pos][simFunc];}
	const map<int, vector<int> > & columnAllSimValues(int pos) {return tableSimValues[pos];}
	~SimValueStore(void);
};
