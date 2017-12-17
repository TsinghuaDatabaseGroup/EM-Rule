#pragma once
#include "UnARM.h"
class UnARMAdvanced : public UnARM
{
private:
	vector<int> M, D;
	int c0, w0;
private:
	void search(vector<UAttrRule*>& uars, vector<vector<CAttrRule*> >& pars, unsigned posVec, const vector<TupleRule>& trs, ResultSet& resultSet);
public:
	UnARMAdvanced(AttrRuleManager& _arManager, TupleRuleManager& _trManager, TrainData& _trainData)
		:UnARM(_arManager, _trManager, _trainData){
	}
	void search(ResultSet& resultSet);
	~UnARMAdvanced(void);
};
