#include "TupleRule.h"

TupleRule::TupleRule(void)
{
}

bool TupleRule::update(AttrRule* prevAr, AttrRule* nextAr)
{
	bool updated = false;
	for (unsigned j=0; j<tr.size(); ++j)
	{
		if (tr[j] == prevAr)
		{
			updated = true;
			tr[j] = nextAr;
		}
	}
	return updated;
}
TupleRule::~TupleRule(void)
{
}
