#include "UnARMAdvanced.h"



UnARMAdvanced::~UnARMAdvanced(void)
{
}

void UnARMAdvanced::search(ResultSet& resultSet)
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

	
	resultMap.clear();
	search(uars, parsNon, 0,  trManager.getTRSet(), resultSet);
	for (unsigned i=0; i<pars.size(); ++i)
	{
		for (unsigned j=0; j<pars[i].size(); ++j)
			delete pars[i][j];
	}
}

void UnARMAdvanced::search(vector<UAttrRule*>& uars, vector<vector<CAttrRule*> >& pars, unsigned posVec, const vector<TupleRule>& trs, ResultSet& resultSet)
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
		vector<int> storeM = M;
		vector<int> storeD = D;
		int simFunc = -1;
		int dc=0, dw=0;
		for (unsigned i=0; i<par.size(); ++i)
		{
			if (par[i]->getSimFunc() != simFunc)
			{
				simFunc = par[i]->getSimFunc();
				dc = dw = 0;
				if (M.size() != storeM.size())
					M = storeM;
				if (D.size() != storeD.size())
					D = storeD;
			}
			resultMap[uar] = par[i];
			unsigned k=0;
			for (unsigned j=0; j<M.size(); ++j)
			{
				if (satisfy(trsc, M[j]))
					++dc;
				else
				{
					assert(k<=j);
					if (k!=j)
						M[k] = M[j];
					++k;
				}
			}
			if (k<M.size())
				M.erase(M.begin()+k, M.end());
			k = 0;
			for (unsigned j=0; j<D.size(); ++j)
			{
				if (satisfy(trsc, D[j]))
					++dw;
				else
				{
					assert(k<=j);
					if (k!=j)
						D[k] = D[j];
					++k;
				}
			}
			if (k<D.size())
				D.erase(D.begin()+k, D.end());
			c0 += dc; 
			w0 += dw;
			assert(storeM.size() == M.size()+dc);
			assert(storeD.size() == D.size()+dw);
			if (obfunc(c0+M.size(), w0)<=op)
			{
				while ( i<par.size() && par[i]->getSimFunc() == simFunc) ++i;
				--i;
			}
			else
				search(uars, pars, posVec+1, trsu, resultSet);
			c0 -= dc; 
			w0 -= dw;
		}

		M = storeM;
		D = storeD;
	}
	resultMap.erase(uar);
	//possibleMappingSet(uar, M, par);
	//eliminateRedundancy(uars[i], pars[posVec], M, D, par);
	//eliminateRedundancyOp(uars[i], pars[posVec], M, D, par);
	
	/*CInvertedIndex CIXM, CIXD;
	CIXM.construct(par, tableSimValues.columnAllSimValues(), M);
	CIXD.construct(par, tableSimValues.columnAllSimValues(), D);*/

}




