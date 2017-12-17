#pragma once
#include "TupleRuleManager.h"
#include "AttrRuleManager.h"
#include "TrainData.h"
#include "SimValueStore.h"
#include "GlobFunc.h"
#include "CInvertedIndex.h"
#include "ForwardIndex.h"
#include <ctime>
#include <algorithm>
struct Result
{
	string label;
	string name;
	int simfunc;
	double threshold;
	Result(const string& _label, const string& _name, int _simfunc, double _threshold)
		:label(_label), name(_name), simfunc(_simfunc), threshold(_threshold)
	{

	}
};

typedef vector<Result > ResultSet;
using namespace std;
class UnARM
{
protected:
	map<UAttrRule*,CAttrRule*> resultMap;
protected:
	int MSize, DSize;
	double op;
	TupleRuleManager& trManager;
	AttrRuleManager& arManager;
	TrainData& trainData;
	SimValueStore tableSimValues;
private:
	void PreprocessTable(CInvertedIndex& CIX, ForwardIndex& FX, map<CAttrRule*, vector<CAttrRule*> >& TL);
protected:
	//double obfunc(int c, int w) {return c-w;}
	double obfunc(int c, int w) {
		if (c+w == 0 || MSize == 0)
			return 0;
		double p = c*1.0/(c+w);
		double r = c*1.0/MSize;
		return 2/(1/p+1/r);
	}
	void preStoreSimValue();
	void possibleMappingSet(UAttrRule* uar, const vector<int>& M, vector<CAttrRule*>& par);
	bool satisfy(const TupleRule& trs, int id);
	bool satisfy(CAttrRule* ar, int id);
	bool exactSatisfy(CAttrRule* ar, int id);
	void satisfy(const vector<TupleRule>& trs, const vector<int>& M, const vector<int>&D,  int& c, int& w);
	void satisfy(CAttrRule* ar, const vector<int>& M, const vector<int>&D,  int& c, int& w);
	bool satisfy(const vector<TupleRule>& trs, int id);
	bool mustSatisfy(const vector<TupleRule>& trs, int id);
	bool mustDisSatisfy(const vector<TupleRule>& trs, int id);
	void eliminateRedundancy(UAttrRule* uar, vector<CAttrRule*>& par, const vector<int>& M, const vector<int>& D, vector<CAttrRule*>& parNon, bool verbose = false);
	void eliminateRedundancyOp(UAttrRule* uar, vector<CAttrRule*>& par, const vector<int>& M, const vector<int>& D, vector<CAttrRule*>& parNon, bool verbose = false);
	int eliminateSatisfiedTP(vector<int>& M, vector<int>& D, int& c, int& w);
	int eliminateDissatisfiedTP(vector<int>& M, vector<int>& D);
	void trsSplit(const vector<TupleRule>& trs,  vector<TupleRule>& trsc,  vector<TupleRule>& trsu);
	void sortByQuality(vector<vector<CAttrRule*> >& parsNon, vector<int>& M, vector<int>& D);
	void initResultMap(ResultSet& resultSet);
	void outputPar(const vector<CAttrRule*>& pars);
public:
	UnARM(AttrRuleManager& _arManager, TupleRuleManager& _trManager, TrainData& _trainData)
		:arManager(_arManager), trManager(_trManager), trainData(_trainData), tableSimValues(trainData), 
		MSize(_trainData.getMSize()), DSize(_trainData.getDSize()){
			preStoreSimValue();
	}
	void setMappingTP(const vector<int>& _M) {trainData.setMappingTP(_M); MSize = _M.size();}
	void setNonMappingTP(const vector<int>& _D) {trainData.setNonMappingTP(_D); DSize = _D.size();}
	virtual void search(ResultSet& resultSet) = 0;
	double getOp() {return op;}
	virtual ~UnARM(void);
	/***********   Test *****************/
public:
	void testRedundancy();
	void testAccuracy(ResultSet& resultSet);
	void satisfyVerbose(const vector<TupleRule>& trs, const vector<int>& M, const vector<int>&D,  int& c, int& w);
	void ouputTP(const TuplePair& tp);
};
