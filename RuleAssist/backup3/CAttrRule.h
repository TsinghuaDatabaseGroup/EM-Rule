#pragma once
#include "AttrRule.h"

class CAttrRule: public AttrRule
{
private:
	double quality;
private:
	int thre;
	int simFunc;
public:
	CAttrRule(string _label, string _name, int _attrPos, int _simFunc, int _thre)
		:AttrRule(_label, _name, _attrPos), simFunc(_simFunc),thre(_thre){}
	CAttrRule(string _label, string _name, int _simFunc, int _thre)
		:AttrRule(_label, _name), simFunc(_simFunc),thre(_thre){}
	CAttrRule(string _name, int _attrPos, int _simFunc, int _thre)
		:AttrRule( _name, _attrPos), simFunc(_simFunc),thre(_thre){}
	CAttrRule(string _name, int _simFunc, int _thre)
		:AttrRule(_name), simFunc(_simFunc),thre(_thre){}

	void setSimFunc(int _simFunc) {simFunc = _simFunc;}
	int getSimFunc() const {return simFunc;}
	void setThrehold(int _thre) {thre = _thre;}
	int getThreshold() const {return thre;}
	bool isCertain() {return true;}
	void setQuality(double _quality) {quality = _quality;}
	double getQuality() const { return quality;}
	~CAttrRule(void);
};
