#include "stdafx.h"
#include "monom.h"
#include <iterator>


monom::monom(int a, int b, int c, double k1)
{
	if (a >= p || b >= p || c >= p)
		throw 1;
	degs = getDegsInt(a, b, c);
	k = k1;
}

monom::monom(int d, double c)
{
	if (d >= p * p * p)
		throw 1;
	degs = d;
	k = c;
}

bool isCorrect(string s)
{
	string a = "xyzXYZ0123456789";
	for (size_t i = 0; i < a.size(); ++i)
	{
		
		if (a.find(a[i]) == string::npos)
		{
			return false;
		}
	}
	return true;
}

pair<int, string::iterator> getFirstNumber(string::iterator a, string::iterator b)
{
	string s = "0123456789";
	bool ok = false;
	int k = 1;
	for (; a != b && s.find(*a) != string::npos; ++a)
	{
		if (!ok)
		{
			ok = true;
			k = 0;
		}
		k = 10 * k -'0' + *a;
	}
	if (!ok && a != b)
		return pair<int, string::iterator>(k, a++);
	return pair<int, string::iterator>(k, a);
}


monom::monom(string s)
{
	int a = 0, b = 0, c = 0;
	pair<int, string::iterator> pr;
	if (s[0] == '-')
	{
		pr = getFirstNumber(s.begin() + 1, s.end());
		k = -pr.first;
	}
	else
	{
		 pr = getFirstNumber(s.begin(), s.end());
		k = pr.first;
	}
	
	for (string::iterator it = pr.second; it != s.end();)
	{
		if (*it == 'x' || *it == 'X')
		{
			pair<int, string::iterator> p = getFirstNumber(it + 1, s.end());
			a += p.first;
			it = p.second;
		}
		else if (*it == 'y' || *it == 'Y')
		{
			pair<int, string::iterator> p = getFirstNumber(it + 1, s.end());
			b += p.first;
			it = p.second;
		}
		else if (*it == 'z' || *it == 'Z')
		{
			pair<int, string::iterator> p = getFirstNumber(it + 1, s.end());
			c += p.first;
			it = p.second;
		}
		else
			throw 1;
	}
	degs = getDegsInt(a, b, c);
}

monom::monom(const monom &a)
{
	degs = a.degs;
	k = a.k;
}

string monom::toString()
{
	vector<int> kof = getDegsVec(degs);
	stringstream ans;
	ans << "";
	string vars = "xyz";
	if (k == 0)
		return ans.str();
	stringstream out;
	if (k != 1)
	{
		out << k;
		ans << out.str();
	}
	for (size_t i = 0; i < 3; ++i)
	{
		if (kof[i] != 0)
		{
			if (kof[i] == 1)
			{
				ans << vars[i];
			}
			else
			{
				ans << vars[i];
				ans << kof[i];
			}
		}
	}
	return ans.str();
}

monom monom::dfdx()
{
	monom a(0, 0);
	if (degs / p * p < 1)
	{
		return a;
	}
	int n = degs / p / p;
	a.k = k * n;
	a.degs = degs - p * p;
	return a;
}

monom monom::dfdy()
{
	monom a(0, 0);
	if ((degs / p) % p < 1)
	{
		return a;
	}
	int n = (degs / p) % p;
	a.k = k * n;
	a.degs = degs - p;
	return a;
}

monom monom::dfdz()
{
	monom a(0, 0);
	if (degs % p < 1)
	{
		return a;
	}
	int n = degs % p;
	a.k = k * n;
	a.degs = degs - 1;
	return a;
}

monom monom::dx()
{
	monom a(*this);
	int n = degs / p / p;
	a.k /= n + 1;
	a.degs += p * p;
	return a;
}

monom monom::dy()
{
	monom a(*this);
	int n = degs / p % p;
	a.k /= n + 1;
	a.degs += p;
	return a;
}

monom monom::dz()
{
	monom a(*this);
	int n = degs % p;
	a.k /= n + 1;
	a.degs += 1;
	return a;
}

monom monom::operator+=(const monom a)
{
	if (*this == a)
	{
		k += a.k;
	}
	else
	{
		throw 1;
	}
	return *this;
}

monom monom::operator+(const monom a)
{
	monom b(degs, k);
	b += a;
	return b;
}

monom monom::operator-=(const monom a)
{
	if (*this != a)
		throw 1;
	k -= a.k;
	return *this;
}

monom monom::operator-(const monom a)
{
	monom b(*this);
	b -= a;
	return b;
}

monom monom::operator-()
{
	k = -k;
	return *this;
}

monom monom::operator*(const monom a)
{
	monom b(*this);
	b *= a;
	return b;
}

monom monom::operator*=(const monom a)
{
	if (a.degs % p + degs % p >= p || a.degs / p % p + degs / p % p >= p || a.degs / p / p % p + degs / p / p % p >= p)
		throw 1;
	degs += a.degs;
	k *= a.k;
	return *this;
}

bool monom::operator<(const monom a)
{
	if (degs < a.degs)
		return true;
	return false;
}

bool monom::operator<=(const monom a)
{
	if (degs <= a.degs)
		return true;
	return false;
}

bool monom::operator>(const monom a)
{
	if (degs > a.degs)
		return true;
	return false;
}

bool monom::operator>=(const monom a)
{
	if (degs >= a.degs)
		return true;
	return false;
}

bool monom::operator==(const monom a)
{
	if (degs == a.degs)
		return true;
	return false;
}

bool monom::operator!=(const monom a)
{
	if (degs != a.degs)
		return true;
	return false;
}


monom::~monom()
{
}

int getDegsInt(int a, int b, int c)
{
	int ans = a;
	ans = ans * p + b;
	ans = ans * p + c;
	return ans;
}

vector<int> getDegsVec(int d)
{
	vector<int> ans(3);
	for (int i = 2; i >= 0; --i)
	{
		ans[i] = d % p;
		d /= p;
	}
	return ans;
}
