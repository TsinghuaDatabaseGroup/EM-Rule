#pragma once
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
using namespace std;

class AttrRule
{
protected:
	string label;
	int attrPos;
	string name;
public:
	AttrRule(string _name)
		:label(""), name(_name),attrPos(-1) {}
	AttrRule(string _name, int _attrPos)
		:label(""), name(_name), attrPos(_attrPos){}
	AttrRule(string _label, string _name)
		:label(_label), name(_name),attrPos(-1) {}
	AttrRule(string _label, string _name, int _attrPos)
		:label(_label), name(_name), attrPos(_attrPos){}
	virtual bool isCertain() = 0; 
	void setAttrPos(int _attrPos) {attrPos = _attrPos;}
	int getAttrPos() {return attrPos;}
	string getName() {return name;}
	string setName(string _name) { name = _name;}
	string getLabel() {return label;}
	virtual ~AttrRule(void);
};
