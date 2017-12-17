#include "UnARMIterative.h"

UnARMIterative::~UnARMIterative(void)
{
}

void UnARMIterative::search(ResultSet& resultSet)
{
	bool optimazied1 = true;
	op = -1e9;
	vector<UAttrRule*> uars;
	trManager.getUARSet(uars);
	/*for (unsigned i=0; i<uars.size(); ++i)
	{
		optimalResultMap.push_back(pair<UAttrRule,CAttrRule>(*uars[i], CAttrRule(uars[i]->getName(), uars[i]->getAttrPos(),0 ,1)));
	}*/
	vector<vector<CAttrRule*> > pars(uars.size());
	vector<vector<CAttrRule*> > parsNon(uars.size());
	vector<int> M = trainData.getMatchingTP();
	vector<int> D= trainData.getNonMatchingTP();
	

	int c0 = 0, w0=0;
	if (optimazied1)
	{
		eliminateSatisfiedTP(M, D, c0, w0);
		eliminateDissatisfiedTP(M, D);
	}
	for (unsigned i=0; i<uars.size(); ++i)
	{
		possibleMappingSet(uars[i], M, pars[i]);
		//eliminateRedundancy(uars[i], pars[i], M, D, parsNon[i]);
		if (elim)
			eliminateRedundancyOp(uars[i], pars[i], M, D, parsNon[i]);
		else
			parsNon[i]=pars[i];
	}

	sortByQuality(parsNon, M, D);
	resultMap.clear();
	for (unsigned i=0; i<uars.size(); ++i)
	{
		resultMap[uars[i]] = parsNon[i][0];	
	}
	const vector<TupleRule>& trs = trManager.getTRSet();
	int c=c0, w=w0;
	satisfy(trs, M, D, c,w);
	op = obfunc(c,w);
	double maxOp = op;
	UAttrRule* maxUar = NULL;
	CAttrRule* maxCar = NULL;
	int niterate = 0;
	while (true)
	{
		double maxOp = op;
		UAttrRule* maxUar = NULL;
		CAttrRule* maxCar = NULL;
		for (unsigned i=0; i<uars.size(); ++i)
		{
			vector<CAttrRule*>& parNon = parsNon[i];
			CAttrRule* lastCar = resultMap[uars[i]];
			for (unsigned j=0; j<parNon.size(); ++j)
			{
				if (parNon[j] == lastCar)
					continue;
				resultMap[uars[i]] = parNon[j];
				c = c0;
				w = w0;
				satisfy(trs, M, D, c,w);
				double tmpOp = obfunc(c,w);
				if (tmpOp > maxOp || (tmpOp == maxOp && maxUar!=NULL && parNon[j]->getQuality() > maxCar->getQuality()))
				{
					maxCar = parNon[j];
					maxUar = uars[i];
					maxOp = tmpOp;
				}
			}
			resultMap[uars[i]] = lastCar;
		}
		if (maxUar != NULL)
		{
			resultMap[maxUar] = maxCar;
			op = maxOp;
			++niterate;
		}
		else
			break;
	}
	cout << "iteratenum " << niterate << "\t";
	resultSet.clear();
	for (unsigned i=0; i<uars.size(); ++i) 
	{
		CAttrRule* car = resultMap[uars[i]];
		resultSet.push_back(Result(uars[i]->getLabel(), car->getName(), car->getSimFunc(), car->getThreshold()*1.0/PRECISION));
	}
}


void UnARMIterative::searchTestObFunc(ResultSet& resultSet, double alpha)
{
	bool optimazied1 = true;
	op = -1e9;
	vector<UAttrRule*> uars;
	trManager.getUARSet(uars);
	/*for (unsigned i=0; i<uars.size(); ++i)
	{
		optimalResultMap.push_back(pair<UAttrRule,CAttrRule>(*uars[i], CAttrRule(uars[i]->getName(), uars[i]->getAttrPos(),0 ,1)));
	}*/
	vector<vector<CAttrRule*> > pars(uars.size());
	vector<vector<CAttrRule*> > parsNon(uars.size());
	vector<int> M = trainData.getMatchingTP();
	vector<int> D= trainData.getNonMatchingTP();
	

	int c0 = 0, w0=0;
	if (optimazied1)
	{
		eliminateSatisfiedTP(M, D, c0, w0);
		eliminateDissatisfiedTP(M, D);
	}
	for (unsigned i=0; i<uars.size(); ++i)
	{
		possibleMappingSet(uars[i], M, pars[i]);
		//eliminateRedundancy(uars[i], pars[i], M, D, parsNon[i]);
		if (elim)
			eliminateRedundancyOp(uars[i], pars[i], M, D, parsNon[i]);
		else
			parsNon[i]=pars[i];
	}

	sortByQuality(parsNon, M, D, alpha);
	resultMap.clear();
	for (unsigned i=0; i<uars.size(); ++i)
	{
		resultMap[uars[i]] = parsNon[i][0];	
	}
	const vector<TupleRule>& trs = trManager.getTRSet();
	int c=c0, w=w0;
	satisfy(trs, M, D, c,w);
	op = obfunc(c,w, alpha);
	double maxOp = op;
	UAttrRule* maxUar = NULL;
	CAttrRule* maxCar = NULL;
	int niterate = 0;
	while (true)
	{
		double maxOp = op;
		UAttrRule* maxUar = NULL;
		CAttrRule* maxCar = NULL;
		for (unsigned i=0; i<uars.size(); ++i)
		{
			vector<CAttrRule*>& parNon = parsNon[i];
			CAttrRule* lastCar = resultMap[uars[i]];
			for (unsigned j=0; j<parNon.size(); ++j)
			{
				if (parNon[j] == lastCar)
					continue;
				resultMap[uars[i]] = parNon[j];
				c = c0;
				w = w0;
				satisfy(trs, M, D, c,w);
				double tmpOp = obfunc(c,w, alpha);
				if (tmpOp > maxOp || (tmpOp == maxOp && maxUar!=NULL && parNon[j]->getQuality() > maxCar->getQuality()))
				{
					maxCar = parNon[j];
					maxUar = uars[i];
					maxOp = tmpOp;
				}
			}
			resultMap[uars[i]] = lastCar;
		}
		if (maxUar != NULL)
		{
			resultMap[maxUar] = maxCar;
			op = maxOp;
			++niterate;
		}
		else
			break;
	}
	//cout << "iteratenum " << niterate << "\t";
	resultSet.clear();
	for (unsigned i=0; i<uars.size(); ++i) 
	{
		CAttrRule* car = resultMap[uars[i]];
		resultSet.push_back(Result(uars[i]->getLabel(), car->getName(), car->getSimFunc(), car->getThreshold()*1.0/PRECISION));
	}
}