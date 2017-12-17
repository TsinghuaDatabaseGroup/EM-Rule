#include "UnARMAdvanced2.h"



UnARMAdvanced2::~UnARMAdvanced2(void)
{
}

void UnARMAdvanced2::search(ResultSet& resultSet)
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
	eliminateSatisfiedTP(M, D, c0, w0);
	eliminateDissatisfiedTP(M, D);
	resultMap.clear();
	search(uars, 0,  trManager.getTRSet(), resultSet);

}

void UnARMAdvanced2::search(vector<UAttrRule*>& uars, unsigned posVec, const vector<TupleRule>& trs, ResultSet& resultSet)
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
	vector<CAttrRule*>  par;
	vector<CAttrRule*>  parNon;
	possibleMappingSet(uar, M, par);
	//eliminateRedundancy(uar, pars[posVec], M, D, par);
	eliminateRedundancyOp(uar, par, M, D, parNon);
	
	vector<TupleRule> trsc, trsu;
	resultMap[uar] = NULL;
	
	trsSplit(trs, trsc, trsu);
	if (trsc.size() == 0)
	{
		for (unsigned i=0; i<parNon.size(); ++i)
		{
			resultMap[uar] = parNon[i];
			//trManager.update(lastAr, par[i]);
			search(uars, posVec+1, trs, resultSet);
		}
	}
	else
	{
		vector<int> storeM = M;
		vector<int> storeD = D;
		int simFunc = -1;
		int dc=0, dw=0;
		for (unsigned i=0; i<parNon.size(); ++i)
		{
			if (parNon[i]->getSimFunc() != simFunc)
			{
				simFunc = parNon[i]->getSimFunc();
				dc = dw = 0;
				if (M.size() != storeM.size())
					M = storeM;
				if (D.size() != storeD.size())
					D = storeD;
			}
			resultMap[uar] = parNon[i];
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
				while ( i<parNon.size() && parNon[i]->getSimFunc() == simFunc) ++i;
				--i;
			}
			else
				search(uars, posVec+1, trsu, resultSet);
			c0 -= dc; 
			w0 -= dw;
		}

		M = storeM;
		D = storeD;
	}
	resultMap.erase(uar);
	for (unsigned i=0; i<parNon.size(); ++i)
			delete parNon[i];
}



