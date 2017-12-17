#pragma once
#include "AttrRule.h"
#include "CAttrRule.h"
#include "UAttrRule.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class AttrRuleManager
{
	//map<string,int> nameToPos;
	map<string, AttrRule*> labelToAR;
public:
	//AttrRuleManager(vector<string>& attrNames);
	AttrRuleManager();
	AttrRule* addUAttrRule(string label, string name, const vector<int>& simFuncs, int minThre, int maxThre)
	{
		labelToAR[label] = new UAttrRule(label,name,simFuncs,minThre,maxThre);
		return labelToAR[label];
	}
	AttrRule* addCAttrRule(string label, string name, int simFunc, int thre)
	{
		labelToAR[label] = new CAttrRule(label,name,simFunc,thre);
		return labelToAR[label];
	}
	AttrRule* getAttrRule(string label) {return labelToAR[label];}
	void getARSet(vector<AttrRule*>& ars);
	void getUARSet(vector<AttrRule*>& uars);
	~AttrRuleManager(void);
};
