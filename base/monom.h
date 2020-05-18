#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int p = 1000;

class monom
{
	int degs;
	double k;
public:
	monom(int a, int b, int c, double k1);
	monom(int d = -1, double c = 0);
	monom(string a);
	monom(const monom &a);
	string toString();
	monom dfdx();
	monom dfdy();
	monom dfdz();
	monom dx();
	monom dy();
	monom dz();
	monom operator+=(const monom);
	monom operator+(const monom);
	monom operator-=(const monom);
	monom operator-(const monom);
	monom operator-();
	monom operator*(const monom);
	monom operator*=(const monom);
	bool operator<(const monom);
	bool operator<=(const monom);
	bool operator>(const monom);
	bool operator>=(const monom);
	bool operator==(const monom);
	bool operator!=(const monom);
	bool operator<(const double a)
	{
		return k < a;
	}
	bool operator<=(const double a)
	{
		return k <= a;
	}
	bool operator>(const double a)
	{
		return k > a;
	}
	bool operator>=(const double a)
	{
		return k >= a;
	}
	bool operator==(const double a)
	{
		return k == a;
	}
	bool operator!=(const double a)
	{
		return k != a;
	}
	monom abs()
	{
		monom a = *this;
		if (a.k < 0)
			a.k = -k;
		return a;
	}
	~monom();
};

int getDegsInt(int a, int b, int c);
vector<int> getDegsVec(int d);
