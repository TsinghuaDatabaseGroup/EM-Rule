#include "Init.h"
#include "AttrRuleManager.h"
#include "TupleRuleManager.h"
#include "TrainData.h"
#include "UnARMNaive.h"
#include "UnARMAdvanced.h"
#include "UnARMAdvanced2.h"
#include "UnARMIterative.h"
#include "UnARMAdvancedQuality.h"
#include <fstream>
#include <algorithm>
using namespace std;

#ifdef WIN32
const char sep = '\\';
#else
const char sep = '/';
#endif


void testObFunc(const string& trainFilename, const string&  ruleFilename)
{
	AttrRuleManager arManager;
	TupleRuleManager trManager;
	initRule(ruleFilename, arManager, trManager);

	TrainData trainData;
	initTrain(trainFilename, trainData);

	//	UnARMAdvancedQuality solver(arManager, trManager, trainData);
	UnARMIterative solver(arManager, trManager, trainData);

	int trainDataSize = trainData.getDataSize();

	cout << "TrainFile : " << trainFilename << "\t" << "RuleFile: " << ruleFilename << endl; 
	for (unsigned nf=5; nf<=10; nf+=5)
	{
		cout << "FoldNum " << nf << endl;
		int nM = int(trainDataSize*1.0/nf);
		vector<int> nums;
		randomN(nums, trainDataSize);
		double alpha = 0.1;
		for (alpha=0.1; alpha<=0.91; alpha+=0.1)
		{
			cout << "Alpha " << alpha << endl;
			for (unsigned fid = 1; fid<=nf; ++fid)
			{
				cout << "FoldId " << fid << endl;
				vector<int> MTrain, DTrain;
				for (unsigned j=0; j<trainDataSize; ++j)
				{
					if (j>=nM*(fid-1) && j<nM*fid)
						continue;
					if (trainData.isMatching(nums[j]))
						MTrain.push_back(nums[j]);
					else
						DTrain.push_back(nums[j]);
				}
				solver.setMappingTP(MTrain);
				solver.setNonMappingTP(DTrain);			
				ResultSet trainResultSetOp, trainResultSetLocalOp;
				solver.searchTestObFunc(trainResultSetOp,alpha);
				solver.searchLocalOp(trainResultSetLocalOp, alpha);

				vector<int> MTest, DTest;
				for (unsigned j=nM*(fid-1); j<nM*fid&&j<trainDataSize; ++j)
				{
					if (trainData.isMatching(nums[j]))
						MTest.push_back(nums[j]);
					else
						DTest.push_back(nums[j]);
				}
				solver.setMappingTP(MTest);
				solver.setNonMappingTP(DTest);
				solver.testObFunc(trainResultSetOp, trainResultSetLocalOp, alpha);
			}
			cout << endl;
		}
	}
}
#ifdef WIN32
int main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	string outputfile = "obfunc.exp";
	//	FILE* fp = freopen(outputfile.c_str(), "w", stdout);

	//Restaurant
	string trainFilename = "../../data/restaurant.format.train.input";
	string ruleFilename = "../../data/restaurant.rules.accuracy";
	testObFunc(trainFilename, ruleFilename);

	//DBGen
	trainFilename = "../../data/dbgen.format.train.input";
	ruleFilename = "../../data/dbgen.rules.accuracy";
	testObFunc(trainFilename, ruleFilename);

	// Cora
	trainFilename = "../../data/cora.format.train.input.clean";
	ruleFilename = "../../data/cora.rules.accuracy";
	testObFunc(trainFilename, ruleFilename);



	//	fclose(fp);
	return 0;
}
