#pragma once
#include "AttrRuleManager.h"
#include "TupleRuleManager.h"
#include "TrainData.h"
#include "GlobFunc.h"
#include <sstream>
class Parser
{
public:
	Parser(void);
	void parseAttrNames(string line, TrainData& trainData);
	void parseAttrRule(string line, AttrRuleManager& arManager);
	void parseTupleRule(string line, AttrRuleManager& arManager, TupleRuleManager& trManager);
	void parseData(string line, vector<string>& tuple);
	~Parser(void);
};
