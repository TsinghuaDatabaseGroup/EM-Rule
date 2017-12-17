#pragma once
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include <iostream>
using namespace std;

struct TuplePair
{
	vector<string> tuple1;
	vector<string> tuple2;
	int type; // 1 is yes; 0 is no
};
class TrainData
{
	vector<TuplePair> data;
	map<string, int> attrNameToPos;
	vector<int> M, D;
public:
	TrainData(void);
	void initAttrNames(vector<string>& attrNames);
	void addTuplePair(const TuplePair& tp);
	int getAttrPos(string name) {return attrNameToPos[name];}
	int getDataSize() {return data.size();}
	int getMSize() {return M.size();}
	int getDSize() {return D.size();}
	int getAttrNum() {return attrNameToPos.size();}
	const TuplePair& getTuplePair(int row) const {return data[row];}
	const vector<int>& getMatchingTP() const {return M;}
	const vector<int>& getNonMatchingTP() const {return D;}
	~TrainData(void);
public:
	void setMappingTP(const vector<int>& _M) {M = _M;}
	void setNonMappingTP(const vector<int>& _D) {D = _D;}
	bool isMatching(int id) {return data[id].type == 1;}
};
