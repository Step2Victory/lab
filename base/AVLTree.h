#pragma once
#include <string>
#include <stack>
using namespace std;

const int max_len_name_2 = 10;

template<typename T>
class AVLTree
{
	struct Node
	{
		Node* pLeft;
		Node* pRight;
		T value;
		int key;
		string name;
		char height;
		Node(int key,T& value, string name, Node* pLeft = nullptr, Node* pRight = nullptr)
		{
			this->key = key;
			this->value = value;
			this->name = name;
			this->pLeft = pLeft;
			this->pRight = pRight;
			this->height = 1;
		}
		int balance(Node* p)
		{
			return int(getHeight(p->pRight)) - int(getHeight(p->pLeft));
		}
		char getHeight(Node* p)
		{
			if (p == nullptr)
				return 0;
			return p->height;
		}
		void updateHeight(Node* p)
		{
			p->height = max(getHeight(p->pLeft), getHeight(p->pRight)) + 1;
		}
		Node* leftRotate(Node* p)
		{
			Node* p1 = p->pRight;
			p->pRight = p1->pLeft;
			p1->pLeft = p;
			updateHeight(p);
			updateHeight(p1);
			return p1;
		}
		Node* rightRotate(Node* p)
		{
			Node* p1 = p->pLeft;
			p->pLeft = p1->pRight;
			p1->pRight = p;
			updateHeight(p);
			updateHeight(p1);
			return p1;
		}
		Node* doBalance(Node* p)
		{
			if (balance(p) == 2)
			{
				if (balance(p->pRight) < 0)
				{
					p->pRight = rightRotate(p->pRight);
				}
				return leftRotate(p);
			}
			else if (balance(p) == -2)
			{
				if (balance(p->pLeft) > 0)
				{
					p->pLeft = leftRotate(p->pLeft);
				}
				return rightRotate(p);
			}
			return p;
		}
		Node* del(Node*cur, int key)
		{
			if (key > cur->key)
			{
				cur->pRight = del(cur->pRight, key);
			}
			else if (key < cur->key)
			{
				cur->pLeft = del(cur->pLeft, key);
			}
			else
			{
				if (cur->pRight == nullptr && cur->pLeft == nullptr)
				{
					delete cur;
					return nullptr;
				}
				if (cur->pRight == nullptr)
				{
					Node* ret = cur->pLeft;
					delete cur;
					return ret;
				}
				if (cur->pLeft == nullptr)
				{
					Node* ret = cur->pRight;
					delete cur;
					return ret;
				}
				Node* p1 = cur->pLeft;
				while (p1->pLeft != nullptr)
				{
					p1 = p1->pLeft;
				}
				Node* p2 = new Node(p1->key, p1->value, p1->name);
				p2->pLeft = del(p2->pLeft, p2->key);
				p2->pRight = cur->pRight;
				delete cur;
				updateHeight(p2);
				return doBalance(p2);
			}
			updateHeight(cur);
			return doBalance(cur);
		}
		Node* ins(Node *cur, Node *p)
		{
			if (cur == nullptr)
				return p;
			if (p->key > cur->key)
				cur->pRight = ins(cur->pRight, p);
			else
				cur->pLeft = ins(cur->pLeft, p);
			updateHeight(cur);
			return doBalance(cur);
		}
	};
	Node* root;
	int Hash(string);
public:
	AVLTree();
	bool find(string);
	string insert(string name, T&);
	void update(string name, T&);
	T get(string name);
	void print();
	void del(string name);
	~AVLTree();
};


template<typename T>
inline int AVLTree<T>::Hash(string name)//полиномиальный хэш
{
	int mod = 1000000007;
	int p = 257;
	long long ans = 0;
	for (auto a : name)
	{
		ans *= p;
		ans += a;
		ans %= mod;
	}
	return int(ans);
}


template<typename T>
inline bool AVLTree<T>::find(string name)
{
	int key = Hash(name);
	Node* p = root;
	while (p != nullptr && p->key != key)
	{

		if (key > p->key)
			p = p->pRight;
		else
			p = p->pLeft;
	}
	if (p == nullptr)
		return false;
	if (p != nullptr && p->name != name)
		cout << "It is a collision " + name + " | " + p->name << key << " "<< p->key;
	return true;
}



template<typename T>
inline AVLTree<T>::AVLTree()
{
	root = nullptr;
}

template<typename T>
inline string AVLTree<T>::insert(string name, T& value)
{
	int key = Hash(name);
	if (find(name))
	{
		return insert(name + '1', value);
	}
	Node* p = new Node(key, value, name);
	root = root->ins(root, p);
	return name;
}

template<typename T>
inline void AVLTree<T>::update(string name, T& value)
{
	if (!find(name))
	{
		insert(name, value);
		return;
	}
	int key = Hash(name);
	Node* p = root;
	while (p->key != key)
	{
		if (key > p->key)
		{
			p = p->pRight;
		}
		else
		{
			p = p->pLeft;
		}
	}
	p->value = value;
}

template<typename T>
inline T AVLTree<T>::get(string name)
{
	if (!find(name))
		throw "Object is not found";
	else
	{
		int key = Hash(name);
		Node* p = root;
		while (p->key != key)
		{
			if (key > p->key)
			{
				p = p->pRight;
			}
			else
			{
				p = p->pLeft;
			}
		}
		return p->value;
	}
}

template<typename T>
inline void AVLTree<T>::print()
{
	cout << setw(max_len_name_2) << left << "Name" << "|" << "Value" << endl;
	Node* p = root;
	stack<Node*>st;
	st.push(root);
	while (!st.empty())
	{
		if (st.top() == nullptr)
		{
			st.pop();
		}
		else
		{
			Node * p = st.top();
			st.pop();
			st.push(p->pRight);
			st.push(p->pLeft);
			cout << setw(max_len_name_2) << p->name << "|" << p->value << endl;
		}
	}
}




template<typename T>
inline void AVLTree<T>::del(string name)
{
	if (!find(name))
		return;
	int key = Hash(name);
	root = root->del(root, key);
}



template<typename T>
inline AVLTree<T>::~AVLTree()
{
	stack<Node*>st;
	st.push(root);
	while (!st.empty())
	{
		Node* p = st.top();
		st.pop();
		if (p != nullptr)
		{
			st.push(p->pRight);
			st.push(p->pLeft);
		}
		delete p;
	}
}
