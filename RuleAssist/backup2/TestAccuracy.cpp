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


void testAccuracy(const string& trainFilename, const string&  ruleFilename, int maxFold)
{
	AttrRuleManager arManager;
	TupleRuleManager trManager;
	initRule(ruleFilename, arManager, trManager);

	TrainData trainData;
	initTrain(trainFilename, trainData);

//	UnARMAdvancedQuality solver(arManager, trManager, trainData);
UnARMIterative solver(arManager, trManager, trainData);

	int trainDataSize = trainData.getDataSize();

	for (unsigned nf=2; nf<=maxFold; ++nf)
	{
		cout << "FoldNum " << nf << endl;
		int nM = int(trainDataSize*1.0/nf);
		vector<int> nums;
		randomN(nums, trainDataSize);
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
			ResultSet resultSet;
			solver.search(resultSet);

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
			solver.testAccuracy(resultSet);
		}
		cout << endl;
	}
}
#ifdef WIN32
int main2(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	string outputfile = "accuracy.exp";
	FILE* fp = freopen(outputfile.c_str(), "w", stdout);
	int maxfold = 10;

	//Restaurant
	string trainFilename = "../../data/restaurant.format.train.input";
	string ruleFilename = "../../data/restaurant.rules.accuracy";
	testAccuracy(trainFilename, ruleFilename, maxfold);
return 0;

	// Cora
	trainFilename = "../../data/cora.format.train.input";
	ruleFilename = "../../data/cora.rules";
	testAccuracy(trainFilename, ruleFilename, maxfold);

	//DBGen
	trainFilename = "../../data/dbgen.format.train.input";
	ruleFilename = "../../data/dbgen.rules";
	testAccuracy(trainFilename, ruleFilename, maxfold);


	//fclose(fp);
	return 0;
}
