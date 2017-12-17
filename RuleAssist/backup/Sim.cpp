#include "SimValueStore.h"

void SimValueStore::computeColumn0(int pos, vector<int>& columnSimValues, double (*similarity)(const string& s1, const string& s2))
{
	for (unsigned int i=0; i<columnSimValues.size(); ++i)
	{
		const TuplePair& tp = trainData.getTuplePair(i);
		const string& s1 = tp.tuple1[pos];
		const string& s2 = tp.tuple2[pos];
		if (s1 == s2)
		    columnSimValues[i] = PRECISION;
		else if (s1=="" || s2=="")
		    columnSimValues[i]= 0;
		else
			columnSimValues[i] = int(similarity(s1,s2)*PRECISION);
		assert(columnSimValues[i]>=0);
		//cout << columnSimValues[i] << "*" << s1 << " " << s2 << endl;
	}
}
void SimValueStore::computeColumn1(int pos, vector<int>& columnSimValues, unsigned gramLen, double (*similarity)(const string& s1, const string& s2, unsigned gramLen))
{
	for (unsigned int i=0; i<columnSimValues.size(); ++i)
	{
		const TuplePair& tp = trainData.getTuplePair(i);
		const string& s1 = tp.tuple1[pos];
		const string& s2 = tp.tuple2[pos];
                if (s1 == s2)
                    columnSimValues[i] = PRECISION;
                else if (s1=="" || s2=="")
                    columnSimValues[i]= 0;
		else
			columnSimValues[i] = int(similarity(s1,s2, gramLen)*PRECISION);
		assert(columnSimValues[i]>=0);
		//cout << columnSimValues[i] << "*" << s1 << " " << s2 << endl;
	}
}

void SimValueStore::computeColumn2(int pos, vector<int>& columnSimValues, const string& simFuncName, double (*similarity)(const string& s1, const string& s2, const string& simFuncName))
{
	for (unsigned int i=0; i<columnSimValues.size(); ++i)
	{
		const TuplePair& tp = trainData.getTuplePair(i);
		const string& s1 = tp.tuple1[pos];
		const string& s2 = tp.tuple2[pos];
                if (s1 == s2)
                    columnSimValues[i] = PRECISION;
                else if (s1=="" || s2=="")
                    columnSimValues[i]= 0;
		else
			columnSimValues[i] = int(similarity(s1,s2, simFuncName)*PRECISION);
		if (columnSimValues[i]<0)
		{
		    cerr << s1 << endl;
		    cerr << s2 << endl;
		    cerr << simFuncName << endl;
		    cerr << i << " " << pos << endl;
		    cerr << columnSimValues[i] << endl;
		}
		else
		    assert(columnSimValues[i]>=0);
		//cout << columnSimValues[i] << "*" << s1 << " " << s2 << endl;
	}
}
void SimValueStore::compute(int pos, int simFunc)
{
	vector<int>& columnSimValues = tableSimValues[pos][simFunc];
	columnSimValues.resize(row);
	switch (simFunc){
		case 0: computeColumn0(pos, columnSimValues, SimFuncs::equal); break;
		case 1: computeColumn0(pos, columnSimValues, SimFuncs::ned); break;

		case 2: computeColumn0(pos, columnSimValues, SimFuncs::cosineToken); break;
		case 3: computeColumn0(pos, columnSimValues, SimFuncs::diceToken); break;
		case 4: computeColumn0(pos, columnSimValues, SimFuncs::overlapToken); break;
		case 5: computeColumn0(pos, columnSimValues, SimFuncs::jaccardToken); break;

		case 6: computeColumn1(pos, columnSimValues, 2, SimFuncs::cosineGram); break;
		case 7: computeColumn1(pos, columnSimValues, 2, SimFuncs::diceGram); break;
		case 8: computeColumn1(pos, columnSimValues, 2, SimFuncs::overlapGram); break;
		case 9: computeColumn1(pos, columnSimValues, 2, SimFuncs::jaccardGram); break;

		case 10: computeColumn1(pos, columnSimValues, 3, SimFuncs::cosineGram); break;
		case 11: computeColumn1(pos, columnSimValues, 3, SimFuncs::diceGram); break;
		case 12: computeColumn1(pos, columnSimValues, 3, SimFuncs::overlapGram); break;
		case 13: computeColumn1(pos, columnSimValues, 3, SimFuncs::jaccardGram); break;

		case 1001: computeColumn2(pos, columnSimValues, string("BlockDistance"), SimFuncs::similarityFuncName); break;
		case 1002: computeColumn2(pos, columnSimValues, string("ChapmanLengthDeviation"), SimFuncs::similarityFuncName); break;
		case 1003: computeColumn2(pos, columnSimValues, string("ChapmanMatchingSoundex"), SimFuncs::similarityFuncName); break;
		case 1004: computeColumn2(pos, columnSimValues, string("ChapmanMeanLength"), SimFuncs::similarityFuncName); break;
		case 1005: computeColumn2(pos, columnSimValues, string("ChapmanOrderedNameCompoundSimilarity"), SimFuncs::similarityFuncName); break;
		case 1006: computeColumn2(pos, columnSimValues, string("EuclideanDistance"), SimFuncs::similarityFuncName); break;
		case 1007: computeColumn2(pos, columnSimValues, string("Jaro"), SimFuncs::similarityFuncName); break;
		case 1008: computeColumn2(pos, columnSimValues, string("JaroWinkler"), SimFuncs::similarityFuncName); break;
		case 1009: computeColumn2(pos, columnSimValues, string("MatchingCoefficient"), SimFuncs::similarityFuncName); break;
		case 1010: computeColumn2(pos, columnSimValues, string("MongeElkan"), SimFuncs::similarityFuncName); break;
		case 1011: computeColumn2(pos, columnSimValues, string("NeedlemanWunch"), SimFuncs::similarityFuncName); break;
		case 1012: computeColumn2(pos, columnSimValues, string("SmithWaterman"), SimFuncs::similarityFuncName); break;
		case 1013: computeColumn2(pos, columnSimValues, string("SmithWatermanGotoh"), SimFuncs::similarityFuncName); break;
		case 1014: computeColumn2(pos, columnSimValues, string("SmithWatermanGotohWindowedAffine"), SimFuncs::similarityFuncName); break;
		case 1015: computeColumn2(pos, columnSimValues, string("Soundex"), SimFuncs::similarityFuncName); break;
		default:break;
	}	
}
SimValueStore::~SimValueStore(void)
{
}

