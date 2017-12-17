#pragma once
#include "AttrRule.h"
#include "UAttrRule.h"
#include "CAttrRule.h"

using namespace std;
class TupleRule
{
private:
	vector<AttrRule*> tr;
public:
	TupleRule(void);
	void addAttrRule(AttrRule* ar) {tr.push_back(ar);}
	const vector<AttrRule*>&  getTupleRule() const {return tr;}
	bool update(AttrRule* prevAr, AttrRule* nextAr);
	~TupleRule(void);
};
