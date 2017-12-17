#include "UnARMIterative.h"

UnARMIterative::~UnARMIterative(void)
{
}

void UnARMIterative::initResultMap(vector<UAttrRule*>& uars, vector<vector<CAttrRule*> >& parsNon, vector<int>& M, vector<int>& D)
{
	for (unsigned i=0; i<uars.size(); ++i)
	{
		double maxOp = -1e9;
		CAttrRule* maxCar = NULL;
		vector<CAttrRule*>& parNon = parsNon[i];
		assert(parNon.size() > 0);
		for (unsigned j=0; j<parNon.size(); ++j)
		{
			int c = 0,  w = 0;
			for (unsigned k=0; k<M.size(); ++k)
			{
				if (satisfy(parNon[j], M[k]))
					++c;
			}
			for (unsigned k=0; k<D.size(); ++k)
			{
				if (satisfy(parNon[j], D[k]))
					++w;
			}
			double op = obfunc(c,w);
			if (op > maxOp)
			{
				maxOp = op;
				maxCar = parNon[j];
			}
		}
		resultMap[uars[i]] = maxCar;		
	}
}
void UnARMIterative::search(ResultSet& resultSet)
{
	bool optimazied1 = false;
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
		eliminateRedundancyOp(uars[i], pars[i], M, D, parsNon[i]);
	}
	sortByQuality(parsNon, M, D);
	resultMap.clear();
	initResultMap(uars, parsNon, M, D);
	const vector<TupleRule>& trs = trManager.getTRSet();
	int c=c0, w=w0;
	satisfy(trs, M, D, c,w);
	op = obfunc(c,w);
	double maxOp = op;
	UAttrRule* maxUar = NULL;
	CAttrRule* maxCar = NULL;
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
		}
		else
			break;
	}
	resultSet.clear();
	for (unsigned i=0; i<uars.size(); ++i) 
	{
		CAttrRule* car = resultMap[uars[i]];
		resultSet.push_back(Result(uars[i]->getLabel(), car->getName(), car->getSimFunc(), car->getThreshold()*1.0/PRECISION));
	}
}
