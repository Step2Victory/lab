#pragma once
#include "monom.h"
#include <iostream>
#include <algorithm>

struct Node
{
	monom m;
	Node* pNext;
};

class Polynom
{
	Node *pFirst;
public:
	Polynom();
	Polynom(string s);
	Polynom(vector<monom> a);
	Polynom(Node *p);
	Polynom(const Polynom& a);
	Polynom& operator=(const Polynom& a);
	void delZeros();
	Polynom& merge(Polynom& a);
	Polynom merge(vector<Polynom>a);
	Polynom operator-();
	Polynom& operator+=(Polynom& a);
	Polynom operator+(Polynom& a);
	Polynom& operator-=(Polynom& a);
	Polynom operator-(Polynom& a);
	Polynom& operator*= (monom a);
	Polynom operator*(monom a);
	Polynom& operator*=(Polynom& a);
	Polynom operator*(Polynom& a);
	Polynom dfdx();
	Polynom dfdy();
	Polynom dfdz();
	Polynom dx();
	Polynom dy();
	Polynom dz();
	string ToString();
	~Polynom();
};

ostream& operator<<(ostream&, Polynom&);

Polynom dfdx(Polynom a);
Polynom dfdy(Polynom a);
Polynom dfdz(Polynom a);
Polynom dx(Polynom a);
Polynom dy(Polynom a);
Polynom dz(Polynom a);