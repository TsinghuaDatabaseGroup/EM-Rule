#include "TrainData.h"

TrainData::TrainData(void)
{
}

void TrainData::initAttrNames(vector<string>& attrNames)
{
	for (unsigned int i=0; i<attrNames.size(); ++i)
	{
		attrNameToPos[attrNames[i]] = i;
	}
}
void TrainData::addTuplePair(const TuplePair& tp)
{
	if (tp.type)
		M.push_back(data.size());
	else
	{
		assert(tp.type == 0);
		D.push_back(data.size());
	}
	data.push_back(tp);
	if (tp.tuple1.size() != attrNameToPos.size())
	{
	    cerr << tp.tuple1.size() << " " << attrNameToPos.size() << endl;
	    const vector<string>& vec = tp.tuple1;
	    for (unsigned i=0; i< vec.size(); ++i) cerr << vec[i] << endl;
	}
	assert(tp.tuple1.size() == attrNameToPos.size());
	assert(tp.tuple2.size() == attrNameToPos.size());
}
TrainData::~TrainData(void)
{
}
