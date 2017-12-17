#include "TupleRuleManager.h"

TupleRuleManager::TupleRuleManager(void)
{
}

void TupleRuleManager::addAttrRule(string label, AttrRule* ar)
{
	if (!labelToId.count(label))
	{
		labelToId[label] = trs.size();
		trs.push_back(TupleRule());
	}
	int id = labelToId[label];
	trs[id].addAttrRule(ar);
}
void TupleRuleManager::getARSet(vector<AttrRule*>& ars)
{
	set<AttrRule*> uniqueAr;
	for (unsigned i=0; i<trs.size(); ++i)
	{
		const vector<AttrRule*>& tr = trs[i].getTupleRule();
		for (unsigned j=0; j<tr.size(); ++j)
		{
			AttrRule* ar = tr[j];
			if (!uniqueAr.count(ar))
			{
				ars.push_back(ar);
				uniqueAr.insert(ar);
			}
		}
	}
}

void TupleRuleManager::getUARSet(vector<UAttrRule*>& uars)
{
	vector<AttrRule*> ars;
	getARSet(ars);
	for (unsigned i=0; i<ars.size(); ++i)
	{
		if (!ars[i]->isCertain())
			uars.push_back((UAttrRule*)ars[i]);
	}
}

bool TupleRuleManager::update(AttrRule* prevAr, AttrRule* nextAr)
{
	bool updated = false;
	for (unsigned i=0; i<trs.size(); ++i)
	{
		if (trs[i].update(prevAr, nextAr))
			updated = true;	
	}
	assert(updated);
	return updated;
}
TupleRuleManager::~TupleRuleManager(void)
{
}
