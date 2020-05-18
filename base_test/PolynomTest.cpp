#include "gtest.h"
#include "monom.cpp"
#include "polynom.cpp"
#include "HashTable.h"
#include "AVLTree.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(monom, Test1)
{
	vector<int>a = getDegsVec(11001001);
	vector<int> b = { 11, 1 ,1 };
	EXPECT_EQ(b, a);
}

TEST(monom, Test2)
{
	int a = getDegsInt(1, 2, 3);
	EXPECT_EQ(1002003, a);
}

TEST(monom, Test3)
{
	monom a(1, 2, 3, 4);
	EXPECT_EQ(a.toString(), "4xy2z3");
}

TEST(monom, Test4)
{
	monom a(0, 0, 0, 4);
	EXPECT_EQ(a.toString(), "4");
}

TEST(monom, Test5)
{
	monom a(1, 2, 3, 0);
	EXPECT_EQ(a.toString(), "");

}

TEST(monom, Test6)
{
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 5);
	EXPECT_EQ(a == b, true);
}


TEST(monom, Test7)
{
	monom a("4y2z6x");
	EXPECT_EQ(a.toString(), "4xy2z6");
}


TEST(monom, Test8)
{
	monom a("0");
	EXPECT_EQ(a.toString(), "");
}


TEST(monom, Test9)
{
	monom a("123xzyxxxxx");
	EXPECT_EQ(a.toString(), "123x6yz");
}


TEST(monom, Test10)
{
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 5);
	EXPECT_EQ((a + b).toString(), "9xy2z3");
}

TEST(monom, Test11)
{
	monom a(1, 2, 3, 4);
	monom b(2, 3, 4, 1);
	EXPECT_ANY_THROW(a + b);
}

TEST(monom, Test12)
{
	monom a(1, 1, 2, 4);
	monom b(2, 3, 4, 1);
	EXPECT_EQ((a*b).toString(), "4x3y4z6");
}

TEST(monom, Test13)
{
	monom a(1, 1, 2, 4);
	monom b(2, 3, 4, 0);
	EXPECT_EQ((a*b).toString(), "");
}

TEST(monom, Test14)
{
	monom a(1, 2, 3, 4);
	monom b(2, 3, 4, 1);
	EXPECT_ANY_THROW(a - b);
}

TEST(monom, Test15)
{
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 1);
	EXPECT_EQ((a - b).toString(), "3xy2z3");
}

TEST(monom, Test16)
{
	monom a(1, 2, 3, 4);
	monom b(2, 2, 3, 1);
	EXPECT_EQ(a != b, true);
}

TEST(monom, Test17)
{
	monom a(1, 2, 3, 4);
	monom b(2, 2, 3, 1);
	EXPECT_EQ(a < b, true);
}

TEST(monom, Test18)
{
	monom a(1, 2, 3, 4);
	monom b(2, 0, 0, 1);
	EXPECT_EQ(b > a, true);
}

TEST(monom, Test19)
{
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 1);
	EXPECT_EQ(a <= b, true);
}

TEST(monom, Test20)
{
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 1);
	EXPECT_EQ(a >= b, true);
}

TEST(monom, Test21)
{
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.toString(), "99xy2z3");
}

TEST(monom, Test22)
{
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.dfdx().toString(), "99y2z3");
}

TEST(monom, Test23)
{
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.dfdy().toString(), "198xyz3");
}

TEST(monom, Test24)
{
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.dfdz().toString(), "297xy2z2");
}

TEST(monom, Test25)
{
	monom a(1, 2, 3, 24);
	EXPECT_EQ(a.dx().toString(), "12x2y2z3");
	EXPECT_EQ(a.dy().toString(), "8xy3z3");
	EXPECT_EQ(a.dz().toString(), "6xy2z4");
}

TEST(monom, Test26)
{
	monom a(0, 0, 0, 24);
	EXPECT_EQ(a.dfdx().toString(), "");
	EXPECT_EQ(a.dfdy().toString(), "");
	EXPECT_EQ(a.dfdz().toString(), "");
}

TEST(monom, Test27)
{
	monom a(0, 0, 0, 24);
	EXPECT_EQ(a.dx().toString(), "24x");
	EXPECT_EQ(a.dy().toString(), "24y");
	EXPECT_EQ(a.dz().toString(), "24z");
}

TEST(monom, Test28)
{
	monom a(0, 0, 0, 0);
	EXPECT_EQ(a.dx().toString(), "");
	EXPECT_EQ(a.dy().toString(), "");
	EXPECT_EQ(a.dz().toString(), "");
}

TEST(monom, Test29)
{
	ASSERT_ANY_THROW(monom a(0, p, 0, 0));
}

TEST(monom, Test30)
{
	ASSERT_ANY_THROW(monom a(p * p * p, 0));
}

TEST(monom, Test31)
{
	monom a(p / 2 + 1, 0, 0, 1);
	monom b(p / 2, 0, 0, 1);
	ASSERT_ANY_THROW(a * b);
}



TEST(Polynom, Test1)
{
	Polynom a("xyz + x2 + z2");
	EXPECT_EQ(a.ToString(), "x2 + xyz + z2");
}

TEST(Polynom, Test2)
{
	Polynom a("x99 + xy2z + z2 + 6 + xy");
	EXPECT_EQ(a.ToString(), "x99 + xy2z + xy + z2 + 6");
}

TEST(Polynom, Test3)
{
	Polynom a("x2 - x2");
	EXPECT_EQ(a.ToString(), "0");
}

TEST(Polynom, Test4)
{
	Polynom a("12355x12 - x12 + zyx7");
	EXPECT_EQ(a.ToString(), "12354x12 + x7yz");
}

TEST(Polynom, Test5)
{
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b = a;
	EXPECT_EQ(b.ToString(), "12354x12 + x7yz");
}

TEST(Polynom, Test6)
{
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b("x71");
	b = a;
	EXPECT_EQ(b.ToString(), "12354x12 + x7yz");
}

TEST(Polynom, Test7)
{
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b("x12 + z7xy - 12355x12 - x7yz");
	b.merge(a);
	EXPECT_EQ(b.ToString(), "xyz7");
	EXPECT_EQ(a.ToString(), "0");
}

TEST(Polynom, Test8)
{
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b("x12 + z7xy - 12355x12 - x7yz");
	a += b;
	EXPECT_EQ(b.ToString(), "-12354x12 - x7yz + xyz7");
	EXPECT_EQ(a.ToString(), "xyz7");
}

TEST(Polynom, Test9)
{
	Polynom b("x12 + z7xy - 12355x12 - x7yz");
	Polynom a = -b;
	EXPECT_EQ(b.ToString(), "-12354x12 - x7yz + xyz7");
	EXPECT_EQ(a.ToString(), "12354x12 + x7yz - xyz7");
}

TEST(Polynom, Test10)
{
	Polynom a("x2 + z2");
	Polynom b("y2");
	a -= b;
	EXPECT_EQ(a.ToString(), "x2 - y2 + z2");
	EXPECT_EQ(b.ToString(), "y2");
}

TEST(Polynom, Test11)
{
	Polynom a("x2 + z2");
	Polynom b("y2");
	EXPECT_EQ((a + b).ToString(), "x2 + y2 + z2");
	EXPECT_EQ(a.ToString(), "x2 + z2");
	EXPECT_EQ(b.ToString(), "y2");
}

TEST(Polynom, Test12)
{
	Polynom a("x2 + y2");
	Polynom b("y2 + x2");
	EXPECT_EQ((a - b).ToString(), "0");
	EXPECT_EQ(a.ToString(), "x2 + y2");
}

TEST(Polynom, Test13)
{
	Polynom a("x2 + y2");
	Polynom b("y2 + x2");
	a *= b;
	EXPECT_EQ(a.ToString(), "x4 + 2x2y2 + y4");
	EXPECT_EQ(b.ToString(), "x2 + y2");
}

TEST(Polynom, Test14)
{
	Polynom a("x2 + y2 + z2");
	Polynom b("x");
	a *= b;
	EXPECT_EQ(a.ToString(), "x3 + xy2 + xz2");
	EXPECT_EQ(b.ToString(), "x");
}

TEST(Polynom, Test15)
{
	Polynom a("x2 + y2 + z2");
	Polynom b("x + 6");
	Polynom c = a * b;
	EXPECT_EQ(c.ToString(), "x3 + 6x2 + xy2 + xz2 + 6y2 + 6z2");
	EXPECT_EQ(a.ToString(), "x2 + y2 + z2");
	EXPECT_EQ(b.ToString(), "x + 6");
}

TEST(Polynom, Test16)
{
	Polynom a("x3y + xy2 + z2 + 9");
	EXPECT_EQ(dfdz(a).ToString(), "2z");
	EXPECT_EQ(dx(a).ToString(), "0.25x4y + 0.5x2y2 + xz2 + 9x");
}


TEST(HashTable, Test1)
{
	HashTable<int> a;
	int c = 5;
	string name = "num1";
	a.insert(name, c);
	EXPECT_EQ(a.get(name), c);
}

TEST(HashTable, Test2)
{
	HashTable<int> a;
	int c = 5, d =6;
	string name = "num1";
	a.insert(name, c);
	a.update(name, d);
	EXPECT_EQ(a.get(name), d);
}

TEST(HashTable, Test3)
{
	HashTable<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	EXPECT_EQ(a.get(name), c);
}

TEST(HashTable, Test4)
{
	HashTable<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	a.del(name);
	ASSERT_ANY_THROW(a.get(name), c);
}

TEST(HashTable, Test5)
{
	HashTable<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	EXPECT_TRUE(a.find(name));
}

TEST(HashTable, Test6)
{
	HashTable<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	a.del(name);
	EXPECT_FALSE(a.find(name));
}

TEST(HashTable, Test7)
{
	HashTable<Polynom> a;
	Polynom c("x2");
	string name = "Polynom";
	a.update(name, c);
	a.del(name);
	EXPECT_FALSE(a.find(name));
}

TEST(HashTable, Test8)
{
	HashTable<Polynom> a;
	string name = "Polynom1";
	{
		Polynom c("x2");
		a.update(name, c);
	}
	EXPECT_EQ(a.get(name).ToString(), "x2");
}

TEST(HashTable, Test9)
{
	HashTable<Polynom> a;
	string name = "Polynom1";
	{
		Polynom c("x2");
		a.update(name, c);
	}
	EXPECT_EQ(a.get(name).ToString(), "x2");
}

TEST(HashTable, Test10)
{
	HashTable<int> a;
	vector<int>expected_ans;
	vector<string> names;
	string alp = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
	int n = alp.size();
	for (int i = 0; i < 10000; ++i)
	{
		int k = i;
		string name = "";
		while (k > 0)
		{
			name += alp[k % n];
			k /= n;
		}
		string name1 = a.insert(name, i);
		expected_ans.push_back(i);
		names.push_back(name1);
	}
	vector<int> ans;
	for (int i = 0; i < names.size(); ++i)
	{
		ans.push_back(a.get(names[i]));
	}
	
	EXPECT_EQ(ans, expected_ans);
}


TEST(AVLTree, Test1)
{
	AVLTree<int> a;
	int c = 5;
	string name = "num1";
	a.insert(name, c);
	EXPECT_EQ(a.get(name), c);
}

TEST(AVLTree, Test2)
{
	AVLTree<int> a;
	int c = 5, d = 6;
	string name = "num1";
	a.insert(name, c);
	a.update(name, d);
	EXPECT_EQ(a.get(name), d);
}

TEST(AVLTree, Test3)
{
	AVLTree<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	EXPECT_EQ(a.get(name), c);
}

TEST(AVLTree, Test4)
{
	AVLTree<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	a.del(name);
	ASSERT_ANY_THROW(a.get(name), c);
}

TEST(AVLTree, Test5)
{
	AVLTree<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	EXPECT_TRUE(a.find(name));
}

TEST(AVLTree, Test6)
{
	AVLTree<int> a;
	int c = 5;
	string name = "num1";
	a.update(name, c);
	a.del(name);
	EXPECT_FALSE(a.find(name));
}


TEST(AVLTree, Test7)
{
	AVLTree<Polynom> a;
	Polynom c("x2");
	string name = "Polynom";
	a.update(name, c);
	a.del(name);
	EXPECT_FALSE(a.find(name));
}

TEST(AVLTree, Test8)
{
	AVLTree<Polynom> a;
	string name = "Polynom1";
	{
		Polynom c("x2");
		a.update(name, c);
	}
	EXPECT_EQ(a.get(name).ToString(), "x2");
}

TEST(AVLTree, Test9)
{
	AVLTree<Polynom> a;
	string name = "Polynom1";
	{
		Polynom c("x2");
		a.update(name, c);
	}
	EXPECT_EQ(a.get(name).ToString(), "x2");
}

TEST(AVLTree, Test10)
{
	AVLTree<int> a;
	vector<int>expected_ans;
	vector<string> names;
	string alp = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
	int n = alp.size();
	for (int i = 0; i < 10000; ++i)
	{
		int k = i;
		string name = "";
		while (k > 0)
		{
			name += alp[k % n];
			k /= n;
		}
		string name1 = a.insert(name, i);
		expected_ans.push_back(i);
		names.push_back(name1);
	}
	vector<int> ans;
	for (int i = 0; i < names.size(); ++i)
	{
		ans.push_back(a.get(names[i]));
	}

	EXPECT_EQ(ans, expected_ans);
}