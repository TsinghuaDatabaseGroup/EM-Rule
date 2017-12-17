#pragma once
#include "AttrRule.h"

class UAttrRule: public AttrRule
{
protected:
	int minThre, maxThre;
	vector<int> simFuncs;
public:
	UAttrRule(string _name, const vector<int>& _simFuncs, int _minThre=1, int _maxThre=1)
		:AttrRule(_name), simFuncs(_simFuncs), minThre(_minThre), maxThre(_maxThre){}
	UAttrRule(string _label, string _name, const vector<int>& _simFuncs, int _minThre=1, int _maxThre=1)
		:AttrRule(_label, _name), simFuncs(_simFuncs), minThre(_minThre), maxThre(_maxThre){}
	~UAttrRule(void);
	bool isCertain() {return false;}
	const vector<int>& getSimFuncs() const { return simFuncs;}
	int getMinThreshold() const {return minThre;}
	int getMaxThreshold() const {return maxThre;}
};
