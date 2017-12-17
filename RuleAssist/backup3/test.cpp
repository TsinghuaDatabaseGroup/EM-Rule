#include "Init.h"
#include "AttrRuleManager.h"
#include "TupleRuleManager.h"
#include "TrainData.h"
#include "UnARMNaive.h"
#include "UnARMAdvanced.h"
#include "UnARMAdvanced2.h"
#include "UnARMIterative.h"
#include <fstream>

using namespace std;

int main()
{
	string ruleFilename = "../../data/dbgen/dbgen.rules";	
	//string ruleFilename = "../../data/rules.txt";	
	AttrRuleManager arManager;
	TupleRuleManager trManager;
	initRule(ruleFilename, arManager, trManager);

	string trainFilename = "../../data/dbgen/dbgen.format.train.input";
	//string trainFilename = "../../data/train.txt";
	TrainData trainData;
	initTrain(trainFilename, trainData);

	//UnARMNaive solver(arManager, trManager, trainData);


	ResultSet resultSet;
	UnARMNaive solver1(arManager, trManager, trainData);
	solver1.search(resultSet);
	cout << "UnARMNaive " << solver1.getOp() << endl;

	UnARMAdvanced solver2(arManager, trManager, trainData);
	solver2.search(resultSet);
	cout << "UnARMAdvanced " << solver2.getOp() << endl;

	UnARMAdvanced solver3(arManager, trManager, trainData);
	solver3.search(resultSet);
	cout << "UnARMAdvanced " << solver3.getOp() << endl;
	
	UnARMIterative solver4(arManager, trManager, trainData);
	solver4.search(resultSet);
	cout << "UnARMIterative " << solver4.getOp() << endl;
	return 0;
}