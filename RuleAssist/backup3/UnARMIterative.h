#pragma once
#include "UnARM.h"
class UnARMIterative: public UnARM
{
public:
	UnARMIterative(AttrRuleManager& _arManager, TupleRuleManager& _trManager, TrainData& _trainData)
		:UnARM(_arManager, _trManager, _trainData){
	}
	void search(ResultSet& resultSet);
	void searchTestObFunc(ResultSet& resultSet, double alpha);
	~UnARMIterative(void);
};


