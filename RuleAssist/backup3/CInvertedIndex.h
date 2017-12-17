#pragma once

#include <algorithm>
#include <map>
#include <vector>
#include "GlobFunc.h"
#include "CAttrRule.h"


using namespace std;

class ARCmp
{
public:
	bool operator()(const CAttrRule* a, const CAttrRule* b) const
	{
		//assert(a->getSimfuncs().size() == 1 && b->getSimfuncs().size() == 1);
		int fa = a->getSimFunc();
		int fb = b->getSimFunc();
		if (fa == fb)
			return a->getThreshold() > b->getThreshold();
		else
			return fa<fb;                                   
	}
};


class CInvertedIndex
{
public:
	typedef map<CAttrRule*, vector<int>, ARCmp> CIX;
	typedef CIX::iterator iterator;
private:
	CIX cix;
	int simFuncNum;
public:
	CInvertedIndex(void);
	void construct(const vector<CAttrRule*> cars,  const map< int, vector<int> >& allThresholds, const vector<int>& T);
	iterator begin() {return cix.begin();}
	void next(iterator& it) {++it;}
	iterator end() {return cix.end();}
	int size() {return cix.size();}
	int getSimFuncNum() {return simFuncNum;}
	int getInvertedListSize(CAttrRule* car) {return cix[car].size();}
	void erase(CAttrRule* car) {cix.erase(car);}
	void clear() {cix.clear();}
	vector<int>& getInvertedList(CAttrRule* car) {return cix[car];}
	~CInvertedIndex(void);
};


