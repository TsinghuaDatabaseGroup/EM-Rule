#include "CInvertedIndex.h"

CInvertedIndex::CInvertedIndex(void)
{
}

CInvertedIndex::~CInvertedIndex(void)
{
}

void CInvertedIndex::construct(const vector<CAttrRule*> cars,   const map< int, vector<int> >& allThresholds, const vector<int>& T)
{
	for (unsigned i=0; i<cars.size(); ++i)
	{
		cix[cars[i]] = vector<int>();
	}
	vector<int> simFuncs;
	for (iterator it = cix.begin(); it!=cix.end(); ++it)
	{
		int simFunc = it->first->getSimFunc();
		if (simFuncs.size() == 0 || simFunc!=simFuncs.back())
			simFuncs.push_back(it->first->getSimFunc());
	}
	simFuncNum = simFuncs.size();
	CAttrRule* searchCAR = new CAttrRule("",0,1);

	for (unsigned i=0; i<simFuncs.size(); ++i)
	{
		int simFunc = simFuncs[i];
		searchCAR->setSimFunc(simFunc);
		const vector<int>& thresholds = allThresholds.find(simFunc)->second;
		for (unsigned j=0; j<T.size(); ++j)
		{
			searchCAR->setThrehold(thresholds[T[j]]);
			CIX::iterator it = cix.lower_bound(searchCAR);
			if (it!= cix.end() && it->first->getSimFunc() == simFunc)
			{
				it->second.push_back(T[j]);
			}
		}
	}
}
