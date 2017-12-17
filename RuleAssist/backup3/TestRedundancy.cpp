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



void testRedundancy(const string& trainFilename, const string&  ruleFilename, const vector<int>& partitions)
{
	AttrRuleManager arManager;
	TupleRuleManager trManager;
	initRule(ruleFilename, arManager, trManager);
	TrainData trainData;
	initTrain(trainFilename, trainData);
	UnARMNaive solver(arManager, trManager, trainData);

	int numOfSample = 5;
	
	int trainDataSize = trainData.getDataSize();
	for (unsigned i=0; i<partitions.size(); ++i)
	{
		int partition = partitions[i];
		assert (partition <= trainDataSize);
		cout << "Partition " << partition << endl;
		for (unsigned s=0; s<numOfSample; ++s)
		{
			cout << "Sample " << s+1 << endl;
			vector<int> nums;
			randomN(nums, trainDataSize);
			vector<int> M, D;
			for (unsigned j=0; j<partition; ++j)
			{
				if (trainData.isMatching(nums[j]))
					M.push_back(nums[j]);
				else
					D.push_back(nums[j]);
			}
			solver.setMappingTP(M);
			solver.setNonMappingTP(D);
			solver.testRedundancy();
		}
		cout << endl;
	}
}

#ifdef WIN32
int main3(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	string outputfile = "redundancy.exp";
	FILE* fp = freopen(outputfile.c_str(), "w", stdout);

	string trainFilename = "../../data/restaurant.format.train.input";
	string ruleFilename = "../../data/restaurant.rules";
	int partitions1[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
	//int partitions1[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
	testRedundancy(trainFilename, ruleFilename, vector<int>(partitions1, partitions1+sizeof(partitions1)/sizeof(int)));

	trainFilename = "../../data/cora.format.train.input";
	ruleFilename = "../../data/cora.rules";
	int partitions2[] = {20000, 40000, 60000, 80000, 100000, 120000, 140000, 160000, 180000};
	testRedundancy(trainFilename, ruleFilename, vector<int>(partitions2, partitions2+sizeof(partitions2)/sizeof(int)));

	/*trainFilename = "../../data/dbgen.format.train.input";
	ruleFilename = "../../data/dbgen.rules";
	int partitions3[] = {1000, 2000, 3000, 4000, 5000};
	testRedundancy(trainFilename, ruleFilename, vector<int>(partitions3, partitions3+sizeof(partitions3)/sizeof(int)));*/

	fclose(fp);
	return 0;
}
