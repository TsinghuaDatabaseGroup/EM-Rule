#include "Init.h"

void initRule(string ruleFilename, AttrRuleManager& arManager, TupleRuleManager& trManager)
{
	ifstream fin(ruleFilename.c_str());
	if (fin.fail())
	{
		cerr << "Can't open " << ruleFilename << endl;
		exit(-1);
	}
	Parser parser;
	string line;
	while (getline(fin,line,'\n')!=NULL)
	{
		unsigned int i = 0;
		while (i<line.size() && line[i] == ' ') ++i;
		if (line[i] =='#' || line[i] == '\n' || line[i] == 0)
			continue;
		if (line == "<Begin:AR>")
		{
			while (getline(fin,line,'\n')!=NULL)
			{
				if (line == "<End:AR>") 
					break;
				parser.parseAttrRule(line, arManager);
			}
		}
		else if (line == "<Begin:TR>")
		{
			while (getline(fin,line,'\n')!=NULL)
			{
				if (line == "<End:TR>") 
					break;
				parser.parseTupleRule(line, arManager, trManager);
			}
		}
	}
	fin.close();
}
void initTrain(string trainFilename, TrainData& trainData)
{
	ifstream fin(trainFilename.c_str());
	if (fin.fail())
	{
		cerr << "Can't open " << trainFilename << endl;
		exit(-1);
	}
	Parser parser;
	string line;
	getline(fin, line, '\n');
	parser.parseAttrNames(line, trainData);
	int n = 0;
	while (fin >> line)
	{
		if (line == "#")
			break;
		TuplePair tp;
		tp.type = (line == "+" ? 1 : 0);
		while (fin.get() == '\n');
		fin.unget();
		getline(fin, line, '\n');
		parser.parseData(line, tp.tuple1);
		while (fin.get() == '\n');
		fin.unget();
		getline(fin, line, '\n');
		parser.parseData(line, tp.tuple2);


		trainData.addTuplePair(tp);
//		if (++n == 10000)
//			break;
	}

	fin.close();
}
