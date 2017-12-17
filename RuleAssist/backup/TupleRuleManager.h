#pragma once
#include "TupleRule.h"
#include <map>
#include <set>
#include <cassert>
using namespace std;

class TupleRuleManager
{
	map<string,int> labelToId;
	vector<TupleRule> trs;
	vector<vector<int> > arIndex;
public:
	TupleRuleManager(void);
	bool update(AttrRule* prevAr, AttrRule* nextAr);
	void addAttrRule(string label, AttrRule* ar);
	void getARSet(vector<AttrRule*>& ars);
	void getUARSet(vector<UAttrRule*>& uars);
	const vector<TupleRule>& getTRSet() const {return trs;}
	~TupleRuleManager(void);
};
