#include "Parser.h"

Parser::Parser(void)
{
}

void Parser::parseAttrNames(string line, TrainData& trainData)
{
	stringstream sin(line);
	string str;
	vector<string> attrNames;
	while (sin >> str)
		attrNames.push_back(str);
	trainData.initAttrNames(attrNames);
}
void Parser::parseAttrRule(string line, AttrRuleManager& arManager)
{
	stringstream sin(line);
	string label, name;
	vector<int> simFuncs;
	double minThre, maxThre;
	sin >> label;
	sin >> name;
	int simId;
	while (sin >> simId)
	{
		if (simId == -1)
			break;
		simFuncs.push_back(simId);
	}
	if (simFuncs.size() == 0)
		simFuncs.push_back(0);
	sin >> minThre;
	if (!(sin >> maxThre))
		maxThre = minThre;

	if (simFuncs.size() == 1 && equalThreshold(maxThre, minThre))
		arManager.addCAttrRule(label,name,simFuncs[0],int(minThre*PRECISION));
	else
		arManager.addUAttrRule(label,name,simFuncs,int(minThre*PRECISION),int(maxThre*PRECISION));
}
void Parser::parseTupleRule(string line, AttrRuleManager& arManager, TupleRuleManager& trManager)
{
	stringstream sin(line);
	string trLabel;
	sin >> trLabel;
	string arLabel;

	while (sin >> arLabel)
	{
		trManager.addAttrRule(trLabel, arManager.getAttrRule(arLabel));
	}

}
void Parser::parseData(string line, vector<string>& tuple)
{
	stringstream sin(line);
	string value;
	while (getline(sin, value, '\t')!=NULL)
	{
		tuple.push_back(value);
	}
}
Parser::~Parser(void)
{
}
