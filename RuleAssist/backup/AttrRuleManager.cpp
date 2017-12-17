#include "AttrRuleManager.h"

AttrRuleManager::AttrRuleManager()
{

}

/*AttrRuleManager::AttrRuleManager(vector<string>& attrNames)
{
	for (unsigned int i=0; i<attrNames.size(); ++i)
	{
		nameToPos[attrNames[i]] = i;
	}
}

inline AttrRule* AttrRuleManager::addAttrRule(string label, string name, const vector<int>& simFuncs, double minThre, double maxThre)
{
	//int pos = nameToPos[name];
	//labelToAR[label] = new AttrRule(name,pos,simFuncs,minThre,maxThre);

}*/
AttrRuleManager::~AttrRuleManager(void)
{
	map<string,AttrRule*>::iterator it;
	for (it = labelToAR.begin(); it != labelToAR.end(); ++it)
	{
		delete it->second;
	}
}

void AttrRuleManager::getARSet(vector<AttrRule*>& ars)
{
	map<string,AttrRule*>::iterator it;
	for (it = labelToAR.begin(); it != labelToAR.end(); ++it)
	{
		ars.push_back(it->second);
	}
}


void AttrRuleManager::getUARSet(vector<AttrRule*>& uars)
{
	map<string,AttrRule*>::iterator it;
	for (it = labelToAR.begin(); it != labelToAR.end(); ++it)
	{
		if (!it->second->isCertain())
			uars.push_back(it->second);
	}
}