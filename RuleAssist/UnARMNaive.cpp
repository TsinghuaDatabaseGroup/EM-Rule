#include "UnARMNaive.h"


UnARMNaive::~UnARMNaive(void)
{
}


void UnARMNaive::search(ResultSet& resultSet)
{
	op = -1e9;
	vector<UAttrRule*> uars;
	trManager.getUARSet(uars);
	/*for (unsigned i=0; i<uars.size(); ++i)
	{
		optimalResultMap.push_back(pair<UAttrRule,CAttrRule>(*uars[i], CAttrRule(uars[i]->getName(), uars[i]->getAttrPos(),0 ,1)));
	}*/
	M = trainData.getMatchingTP();
	D= trainData.getNonMatchingTP();
	c0 = 0, w0=0;
	//eliminateSatisfiedTP(M, D, c0, w0);
	//eliminateDissatisfiedTP(M, D);
	vector<vector<CAttrRule*> > pars(uars.size());
	vector<vector<CAttrRule*> > parsNon(uars.size());
	for (unsigned i=0; i<uars.size(); ++i)
	{
		possibleMappingSet(uars[i], M, pars[i]);
		//eliminateRedundancy(uars[i], pars[i], trainData.getMatchingTP(), trainData.getNonMatchingTP(), parsNon[i]);
		clock_t begin = clock();
		eliminateRedundancyOp(uars[i], pars[i], M, D, parsNon[i]);
		cout << (clock()-begin)*1.0/CLOCKS_PER_SEC << endl;
		cout << pars[i].size() << " " << parsNon[i].size() << endl;
		outputPar(pars[i]);
		outputPar(parsNon[i]);
	}
	sortByQuality(parsNon, M, D);
	for (unsigned i=0; i<uars.size(); ++i)
	{
		possibleMappingSet(uars[i], M, pars[i]);
		//eliminateRedundancy(uars[i], pars[i], trainData.getMatchingTP(), trainData.getNonMatchingTP(), parsNon[i]);
		parsNon[i].clear();
		clock_t begin = clock();
		eliminateRedundancy(uars[i], pars[i], trainData.getMatchingTP(), trainData.getNonMatchingTP(), parsNon[i]);
		cout << (clock()-begin)*1.0/CLOCKS_PER_SEC << endl;
		cout << pars[i].size() << " " << parsNon[i].size() << endl;
		outputPar(pars[i]);
		outputPar(parsNon[i]);
	}
	sortByQuality(parsNon, M, D);
	resultMap.clear();
	search(uars, parsNon, 0, resultSet);
	for (unsigned i=0; i<pars.size(); ++i)
	{
		for (unsigned j=0; j<pars[i].size(); ++j)
			delete pars[i][j];
	}
}

void UnARMNaive::search(vector<UAttrRule*>& uars, vector<vector<CAttrRule*> >& pars, unsigned posVec, ResultSet& resultSet)
{
	if (posVec >= uars.size())
	{
		int c=c0, w=w0;
		satisfy(trManager.getTRSet(), M, D, c,w);

		if (obfunc(c,w)>op)
		{
			op = obfunc(c,w);
			resultSet.clear();
			for (unsigned i=0; i<uars.size(); ++i) 
			{
				CAttrRule* car = resultMap[uars[i]];
				resultSet.push_back(Result(uars[i]->getLabel(), car->getName(), car->getSimFunc(), car->getThreshold()*1.0/PRECISION));
			}
		}
		return;
	}
	UAttrRule* uar = uars[posVec];
	const vector<CAttrRule*>& par = pars[posVec];

	for (unsigned i=0; i<par.size(); ++i)
	{
		resultMap[uar] = par[i];
		//trManager.update(lastAr, par[i]);
		search(uars, pars, posVec+1, resultSet);
	}
	//trManager.update(lastAr, uar);
	//uars[posVec] = uar;

}


