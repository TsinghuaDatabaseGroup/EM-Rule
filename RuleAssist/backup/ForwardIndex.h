#pragma once
#include"CAttrRule.h"
#include "CInvertedIndex.h"

class ForwardIndex
{
	vector<vector<CAttrRule*> > fx;
public:
	ForwardIndex(int size) {fx.resize(size);}
	void add(CInvertedIndex& cix);
	vector<CAttrRule*>& getCARs(unsigned id) {assert(id < fx.size());return fx[id];}
	~ForwardIndex(void);
};
