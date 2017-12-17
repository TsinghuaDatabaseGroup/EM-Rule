
#include "SimFuncs.h"

SimMetrics SimFuncs::simMetrics;


void SimFuncs::strToGrams(const string &s, set<string> &res, unsigned q, unsigned char st, unsigned char en)
{
	const string sPad = string(q - 1, st) + s + string(q - 1, en);
	for (unsigned i = 0; i < s.length() + q - 1; i++)
		res.insert(sPad.substr(i, q));  
}
void SimFuncs::strToGrams(const string &s, set<string> &res, unsigned q)
{
	if (s.length() < q)
	{
		strToGrams(s, res, q, PREFIXCHAR, SUFFIXCHAR);
		return;
		cerr << "string length (" << s.length()
			<< ") less than q (" << q << ")" << endl;
		exit(1);
	}
	for (unsigned i = 0; i < s.length() - q + 1; i++)
	{
		res.insert(s.substr(i, q));  
	}
}
void SimFuncs::strToTokens(const string &s, set<string> &res, const string &delims) 
{
	string::size_type begIdx, endIdx;
	begIdx = s.find_first_not_of(delims);
	while (begIdx != string::npos) 
	{
		endIdx = s.find_first_of(delims, begIdx);
		if (endIdx == string::npos)
		{
			endIdx = s.length();
		}
		res.insert(s.substr(begIdx, endIdx - begIdx));
		begIdx = s.find_first_not_of(delims, endIdx);
	}
}

unsigned SimFuncs::ed(const string &s1, const string &s2)
{ 
	unsigned i, iCrt, iPre, j;
	unsigned n = s1.length(), m = s2.length();
	if (n == 0)
		return m;
	if (m == 0)
		return n;
	unsigned* d[2];
	d[0] = new unsigned[m+1];
	d[1] = new unsigned[m+1];

	for (j = 0; j <= m; j++)
	{
		d[0][j] = j;
		iCrt = 1;
		iPre = 0;
		for (i = 1; i <= n; i++) 
		{
			d[iCrt][0] = i;
			for (j = 1; j <= m; j++)
			{
				d[iCrt][j] = min(min(d[iPre][j] + 1, d[iCrt][j - 1] + 1), d[iPre][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
			}
			iPre = !iPre;
			iCrt = !iCrt;
		}
	}
	unsigned dis = d[iPre][m];
	delete [] d[0];
	delete [] d[1];
	return dis;
}



unsigned SimFuncs::edSwap(const string &s1, const string &s2)
{ 
	unsigned i, iCrt, iPre, j;
	unsigned n = s1.length(), m = s2.length();
	unsigned* d[2];
	d[0] = new unsigned[m+1];
	d[1] = new unsigned[m+1];

	for (j = 0; j <= m; j++)
		d[0][j] = j;

	iCrt = 1;
	iPre = 0;
	for (i = 1; i <= n; i++) 
	{
		d[iCrt][0] = i;
		for (j = 1; j <= m; j++)
		{
			d[iCrt][j] = min(min(d[iPre][j] + 1, d[iCrt][j - 1] + 1), (d[iPre][j - 1] + ((s1[i - 1] == s2[j - 1] || 
                                          (i > 1 && j > 1 && s1[i - 1] == s2[j - 2]  &&  s1[i - 2] == s2[j - 1])) ? 0 : 1)));
		}
		iPre = !iPre;
		iCrt = !iCrt;
	}
	unsigned dis = d[iPre][m];
	delete [] d[0];
	delete [] d[1];
	return dis;
}

double SimFuncs::equal(const string &s1, const string &s2)
{ 
	if (s1 == s2)
		return 1;
	else
		return 0;
}

double SimFuncs::ned(const string &s1, const string &s2)
{ 
	if (s1.size() == 0 || s2.size() == 0)
		return 0;
	unsigned distance = ed(s1,s2);
	if (s1.size()<s2.size())
		return (1-distance*1.0/s2.size());
	else
		return (1-distance*1.0/s1.size());
}

double SimFuncs::nedSwap(const string &s1, const string &s2)
{ 
	unsigned distance = edSwap(s1,s2);
	if (s1.size()<s2.size())
		return (1-distance*1.0/s2.size());
	else
		return (1-distance*1.0/s1.size());

}


double SimFuncs::cosineGram(const string &s1, const string &s2, unsigned gramLen)
{
	set<string> gramSet1;
	strToGrams(s1, gramSet1, gramLen);
	set<string> gramSet2;
	strToGrams(s2, gramSet2, gramLen);

	unsigned news1Size = gramSet1.size();
	unsigned news2Size = gramSet2.size();
	gramSet1.insert(gramSet2.begin(), gramSet2.end());
	unsigned unionSize = gramSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/sqrt(news1Size*news2Size*1.0);
}

double SimFuncs::cosineToken(const string &s1, const string &s2)
{
	set<string> tokenSet1;
	strToTokens(s1, tokenSet1);
	set<string> tokenSet2;
	strToTokens(s2, tokenSet2);

	unsigned news1Size = tokenSet1.size();
	unsigned news2Size = tokenSet2.size();
	tokenSet1.insert(tokenSet2.begin(),tokenSet2.end());
	unsigned unionSize = tokenSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/sqrt(news1Size*news2Size*1.0);
}

double SimFuncs::jaccardGram(const string &s1, const string &s2, unsigned gramLen)
{
	set<string> gramSet1;
	strToGrams(s1, gramSet1, gramLen);
	set<string> gramSet2;
	strToGrams(s2, gramSet2, gramLen);

	unsigned news1Size = gramSet1.size();
	unsigned news2Size = gramSet2.size();
	gramSet1.insert(gramSet2.begin(), gramSet2.end());
	unsigned unionSize = gramSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/unionSize;
}


double SimFuncs::jaccardToken(const string &s1, const string &s2)
{
	set<string> tokenSet1;
	strToTokens(s1, tokenSet1);
	set<string> tokenSet2;
	strToTokens(s2, tokenSet2);

	unsigned news1Size = tokenSet1.size();
	unsigned news2Size = tokenSet2.size();
	tokenSet1.insert(tokenSet2.begin(),tokenSet2.end());
	unsigned unionSize = tokenSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/unionSize;
}

double SimFuncs::diceGram(const string &s1, const string &s2, unsigned gramLen)
{
	set<string> gramSet1;
	strToGrams(s1, gramSet1, gramLen);
	set<string> gramSet2;
	strToGrams(s2, gramSet2, gramLen);

	unsigned news1Size = gramSet1.size();
	unsigned news2Size = gramSet2.size();
	gramSet1.insert(gramSet2.begin(), gramSet2.end());
	unsigned unionSize = gramSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/unionSize;
}

double SimFuncs::diceToken(const string &s1, const string &s2)
{
	set<string> tokenSet1;
	strToTokens(s1, tokenSet1);
	set<string> tokenSet2;
	strToTokens(s2, tokenSet2);

	unsigned news1Size = tokenSet1.size();
	unsigned news2Size = tokenSet2.size();
	tokenSet1.insert(tokenSet2.begin(),tokenSet2.end());
	unsigned unionSize = tokenSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*2.0/(news1Size+news2Size);
}

double SimFuncs::overlapGram(const string& s1, const string& s2, unsigned gramLen)
{
	set<string> gramSet1;
	strToGrams(s1, gramSet1, gramLen);
	set<string> gramSet2;
	strToGrams(s2, gramSet2, gramLen);

	unsigned news1Size = gramSet1.size();
	unsigned news2Size = gramSet2.size();
	gramSet1.insert(gramSet2.begin(), gramSet2.end());
	unsigned unionSize = gramSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/min(news1Size, news2Size);
}

double SimFuncs::overlapToken(const string& s1, const string& s2)
{
	set<string> tokenSet1;
	strToTokens(s1, tokenSet1);
	set<string> tokenSet2;
	strToTokens(s2, tokenSet2);

	unsigned news1Size = tokenSet1.size();
	unsigned news2Size = tokenSet2.size();
	tokenSet1.insert(tokenSet2.begin(),tokenSet2.end());
	unsigned unionSize = tokenSet1.size();
	unsigned intersectionSize = news1Size+news2Size-unionSize;
	return intersectionSize*1.0/min(news1Size,news2Size);
}

double SimFuncs::similarityFuncName(const string& s1, const string& s2, const string& simFuncName)
{
	return simMetrics.similarity(s1,s2,simFuncName);
}


