#include "ForwardIndex.h"



ForwardIndex::~ForwardIndex(void)
{
}

void ForwardIndex::add(CInvertedIndex& cix)
{
	for (CInvertedIndex::iterator it = cix.begin(); it!=cix.end(); cix.next(it))
	{
		vector<int>& tps = it->second;
		for (unsigned i=0; i<tps.size(); ++i)
		{
			fx[tps[i]].push_back(it->first);
		}
	}
}
