#pragma once
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const int PRECISION = 1000;

inline bool equalThreshold(double a, double b)
{
	return fabs(a-b)*PRECISION<1.0;
}
// 0,1,2,...,nM+nD; assign nM numbers to M and assign the rest to D
inline void randomN(vector<int>& nums, int n)
{
	nums.reserve(n);
	for (int i=0; i<n; ++i)
		nums.push_back(i);
	random_shuffle(nums.begin(), nums.end()) ;
}
/*
inline bool nosmallerThreshold(double a, double b) 
{
	return a-b>=-eps;
}
inline bool nolargerThreshold(double a, double b) 
{
	return a-b<=eps;
}

inline bool largerThreshold(double a, double b) 
{
	bool flag;
	if (equalThreshold(a,0.8)&&equalThreshold(b,0.8))
	{
		flag =  a-b>eps;
		flag = (a-b>eps) && (b-a>eps);
	}
	return a-b>eps;
}
inline bool smallerThreshold(double a, double b) 
{
	return a-b<-eps;
}*/