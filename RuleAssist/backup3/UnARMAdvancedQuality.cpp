#include "UnARMAdvancedQuality.h"



UnARMAdvancedQuality::~UnARMAdvancedQuality(void)
{
}

void UnARMAdvancedQuality::search(ResultSet& resultSet)
{
	op = -1e9;
	vector<UAttrRule*> uars;
	trManager.getUARSet(uars);
	/*for (unsigned i=0; i<uars.size(); ++i)
	{
		optimalResultMap.push_back(pair<UAttrRule,CAttrRule>(*uars[i], CAttrRule(uars[i]->getName(), uars[i]->getAttrPos(),0 ,1)));
	}*/

	vector<vector<CAttrRule*> > pars(uars.size());
	vector<vector<CAttrRule*> > parsNon(uars.size());
	M = trainData.getMatchingTP();
	D= trainData.getNonMatchingTP();
	c0 = 0, w0=0;
	eliminateSatisfiedTP(M, D, c0, w0);
	eliminateDissatisfiedTP(M, D);
	for (unsigned i=0; i<uars.size(); ++i)
	{
		possibleMappingSet(uars[i], M, pars[i]);
		//eliminateRedundancy(uars[i], pars[i], M, D, parsNon[i]);
		eliminateRedundancyOp(uars[i], pars[i], M, D, parsNon[i]);
	}
	sortByQuality(parsNon, M, D);
	resultMap.clear();
	search(uars, parsNon, 0,  trManager.getTRSet(), resultSet);
	for (unsigned i=0; i<pars.size(); ++i)
	{
		for (unsigned j=0; j<pars[i].size(); ++j)
			delete pars[i][j];
	}
}

void UnARMAdvancedQuality::search(vector<UAttrRule*>& uars, vector<vector<CAttrRule*> >& pars, unsigned posVec, const vector<TupleRule>& trs, ResultSet& resultSet)
{
	if (posVec >= uars.size())
	{
		int c=c0, w=w0;
		satisfy(trs, M, D, c,w);
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
	
	vector<TupleRule> trsc, trsu;
	resultMap[uar] = NULL;
	
	trsSplit(trs, trsc, trsu);
	if (trsc.size() == 0)
	{
		for (unsigned i=0; i<par.size(); ++i)
		{
			resultMap[uar] = par[i];
			//trManager.update(lastAr, par[i]);
			search(uars, pars, posVec+1, trs, resultSet);
		}
	}
	else
	{
		for (unsigned i=0; i<par.size(); ++i)
		{
			resultMap[uar] = par[i];
			vector<int> storeM = M;
			vector<int> storeD = D;
			int dc=0, dw=0;
			unsigned k=0;
			bool flag = true;
			for (unsigned j=0; j<storeM.size(); ++j)
			{
				if (flag&&exactSatisfy(par[i],storeM[j]))
					flag = false;
				if (satisfy(trsc, storeM[j]))
				{
					++dc;
				}
				else
				{
					assert(k<=j);
					if (k!=j)
						storeM[k] = storeM[j];
					++k;
				}
			}
			if (flag&&i!=0)
				continue;
			if (k<storeM.size())
				storeM.erase(storeM.begin()+k, storeM.end());
			k = 0;
			for (unsigned j=0; j<storeD.size(); ++j)
			{
				if (satisfy(trsc, storeD[j]))
					++dw;
				else
				{
					assert(k<=j);
					if (k!=j)
						storeD[k] = storeD[j];
					++k;
				}
			}
			if (k<storeD.size())
				storeD.erase(storeD.begin()+k, storeD.end());
			c0 += dc; 
			w0 += dw;
			assert(M.size() == storeM.size()+dc);
			assert(D.size() == storeD.size()+dw);
			if (obfunc(c0+M.size(), w0)>op)
				search(uars, pars, posVec+1, trsu, resultSet);
			c0 -= dc; 
			w0 -= dw;
		}
	}
	resultMap.erase(uar);
}




