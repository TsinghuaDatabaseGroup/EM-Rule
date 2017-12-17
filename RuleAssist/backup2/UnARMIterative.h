#pragma once
#include "UnARM.h"
class UnARMIterative: public UnARM
{
private:
	void initResultMap(vector<UAttrRule*>& uars, vector<vector<CAttrRule*> >& parsNon, vector<int>& M, vector<int>& D);
public:
	UnARMIterative(AttrRuleManager& _arManager, TupleRuleManager& _trManager, TrainData& _trainData)
		:UnARM(_arManager, _trManager, _trainData){
	}
	void search(ResultSet& resultSet);
	~UnARMIterative(void);
};


