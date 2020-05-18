#include "stdafx.h"
#include "Polynom.h"


Polynom::Polynom()
{
	monom a;
	pFirst = new Node;
	pFirst->m = a;
	pFirst->pNext = pFirst;
}

Polynom::Polynom(string s)
{
	stringstream ss;
	ss << s;
	string word, lastword = "+";
	monom data(-1, 0);
	vector<monom> v;
	while (ss >> word)
	{
		if ((lastword == "+" || lastword == "-") && (word == "+" || word == "-") || 
			(lastword != "+" && lastword != "-") && (word != "+" && word != "-"))
		{
			throw 1;
		}
		else
		{
			if (word != "+" && word != "-")
			{
				monom a(word);
				if (lastword == "-")
				{
					a = -a;
				}
				v.push_back(a);
			}
			lastword = word;
		}
	}
	sort(v.rbegin(), v.rend());
	pFirst = new Node;
	Node *p = pFirst;
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] != p->m)
		{

			Node*cur = new Node;
			cur->m = v[i];
			p->pNext = cur;
			p = p->pNext;
		}
		else
		{
			p->m += v[i];
		}

	}
	p->pNext=pFirst;
	delZeros();
}

Polynom::Polynom(vector<monom> a)
{
}

Polynom::Polynom(Node * p)
{
	pFirst = p;
}

Polynom::Polynom(const Polynom & a)
{
	pFirst = new Node;
	Node *p1 = pFirst, *p2 = a.pFirst->pNext;
	while (p2 != a.pFirst)
	{
		Node *cur = new Node;;
		cur->m = p2->m;
		p1->pNext = cur;
		p1 = p1->pNext;
		p2=p2->pNext;
	}
	p1->pNext = pFirst;
}

Polynom& Polynom::operator=(const Polynom& a)
{
	if (pFirst == a.pFirst)
		return *this;
	while (pFirst->pNext != pFirst)
	{
		Node *tmp = pFirst->pNext;
		pFirst->pNext = pFirst->pNext->pNext;
		delete tmp;
	}

	Node *p = a.pFirst->pNext, *p1 = pFirst;
	while (p!= a.pFirst)
	{
		Node* cur = new Node;
		cur->m = p->m;
		p1->pNext = cur;
		p1 = p1->pNext;
		p = p->pNext;
	}
	p1->pNext = pFirst;
	return *this;
}

void Polynom::delZeros()
{
	Node*p = pFirst;
	while (p->pNext != pFirst)
	{
		if (p->pNext->m == 0)
		{
			Node *tmp = p->pNext;
			p ->pNext = p->pNext->pNext;
			delete tmp;
		}
		else
		{
			p = p->pNext;
		}
	}
}

Polynom & Polynom::merge(Polynom & a)
{
	Node *pFirst0 = new Node;
	Node *p1 = pFirst->pNext, *p2 = a.pFirst->pNext, *p = pFirst0;
	while (p1 != pFirst || p2 != a.pFirst)
	{
		if (p1->m <= p2->m)
		{
			if (p2->m == p->m)
			{
				p->m += p2->m;
				Node *tmp = p2;
				p2 = p2->pNext;
				delete tmp;
			}
			else
			{
				p->pNext = p2;
				p = p2;
				p2 = p2->pNext;
			}
		}
		else
		{
			if (p1->m == p->m)
			{
				p->m += p1->m;
				Node *tmp = p1;
				p1 = p1->pNext;
				delete tmp;
			}
			else
			{
				p->pNext = p1;
				p = p1;
				p1 = p1->pNext;
				
			}
		}
	}
	pFirst = pFirst0;
	p->pNext = pFirst;
	a.pFirst->pNext = a.pFirst;
	delZeros();
	return *this;
}

Polynom Polynom::merge(vector<Polynom> a)
{	
	vector<Polynom> b = a;
	while (b.size() > 1)
	{
		a = {};
		for (int i = 0; i < b.size(); i+=2)
		{
			if (i + 1 < b.size())
				a.push_back(b[i].merge(b[i + 1]));
			else
				a.push_back(b[i]);
		}
		b = a;
	}
	return b[0];
}

Polynom Polynom::operator-()
{
	Polynom a(*this);
	Node*p = a.pFirst->pNext;
	while (p != a.pFirst)
	{
		p->m = -(p->m);
		p = p->pNext;
	}
	return a;
}

Polynom& Polynom::operator+=(Polynom & a)
{
	Polynom b(a);
	merge(b);
	return *this;
}

Polynom Polynom::operator+(Polynom& a)
{
	Polynom b(*this);
	b += a;
	return b;
}

Polynom& Polynom::operator-=(Polynom & a)
{
	Polynom b(-a);
	merge(b);
	return *this;
}

Polynom Polynom::operator-(Polynom& a)
{
	Polynom b(*this);
	b -= a;
	return b;
}

Polynom& Polynom::operator*=(monom a)
{
	Node*p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m *= a;
		p = p->pNext;
	}
	return *this;
}

Polynom Polynom::operator*(monom a)
{
	Polynom c(*this);
	c *= a;
	return c;
}

Polynom & Polynom::operator*=(Polynom & a)
{
	vector<Polynom>b;
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		
		b.push_back(a * (p->m));
		p = p->pNext;
	}
	if (b.size() == 0)
	{
		Polynom h;
		return h;
	}
	return *this = merge(b);
}

Polynom Polynom::operator*(Polynom &a)
{
	Polynom c(*this);
	c *= a;
	return c;
}

Polynom Polynom::dfdx()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m = p->m.dfdx();
		p = p->pNext;
	}
	delZeros();
	return *this;
}

Polynom Polynom::dfdy()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m = p->m.dfdy();
		p = p->pNext;
	}
	delZeros();
	return *this;
}

Polynom Polynom::dfdz()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m = p->m.dfdz();
		p = p->pNext;
	}
	delZeros();
	return *this;
}

Polynom Polynom::dx()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m = p->m.dx();
		p = p->pNext;
	}
	delZeros();
	return *this;
}

Polynom Polynom::dy()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m = p->m.dy();
		p = p->pNext;
	}
	delZeros();
	return *this;
}

Polynom Polynom::dz()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		p->m = p->m.dz();
		p = p->pNext;
	}
	delZeros();
	return *this;
}

string Polynom::ToString()
{
	Node *p = pFirst;
	string ans = "";
	if (p->pNext == pFirst)
		return "0";
	if (p->pNext->m > 0)
		ans += p->pNext->m.toString();
	else
		ans += "-" + p->pNext->m.abs().toString();
	p = p->pNext;
	while (p->pNext != pFirst)
	{
		if (p->pNext->m < 0)
			ans += " - ";
		else
			ans += " + ";
		ans += (p->pNext->m).abs().toString();
		p=p->pNext;
	}
	return ans;
}

Polynom::~Polynom()
{
	Node*p = pFirst->pNext;
	while (p != pFirst)
	{
		Node* tmp = p;
		p = p->pNext;
		delete tmp;
	}
	delete pFirst;
}

ostream& operator<<(ostream& out, Polynom& a)
{
	out << a.ToString();
	return out;
}


Polynom dfdx(Polynom a)
{
	Polynom b(a);
	b.dfdx();
	return b;
}

Polynom dfdy(Polynom a)
{
	Polynom b(a);
	b.dfdy();
	return b;
}

Polynom dfdz(Polynom a)
{
	Polynom b(a);
	b.dfdz();
	return b;
}

Polynom dx(Polynom a)
{
	Polynom b(a);
	b.dx();
	return b;
}

Polynom dy(Polynom a)
{
	Polynom b(a);
	b.dy();
	return b;
}

Polynom dz(Polynom a)
{
	Polynom b(a);
	b.dz();
	return b;
}
