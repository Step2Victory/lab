#pragma once
#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>
#include "Polynom.h"
using namespace std;

const int N = 100;//количество связных списков в хэш таблице
const int max_len_name_1 = 10;

template<typename T>
class HashTable
{
	struct Node
	{
		T value;
		string name;
		Node *pNext;
		Node(string _name, T& _value)
		{
			name = _name;
			value = _value;
			pNext = nullptr;
		}
	};
	Node** Lists;
	int Hash(string);
public:
	HashTable();
	bool find(string);
	string insert(string name, T& value);
	void update(string name, T& value);
	void del(string name);
	T& get(string name);
	void print();
	~HashTable();
};

template<typename T>
inline int HashTable<T>::Hash(string name)
{
	int p = 67; //простое число
	int key = 0;
	for (int i = 0; i < name.size(); ++i)
	{
		key += p * name[i];
		key %= N;
	}
	return key;
}

template<typename T>
inline bool HashTable<T>::find(string name)
{
	int key = Hash(name);
	Node *p = Lists[key];
	if (p == nullptr)
		return false;
	while (p != nullptr)
	{
		if (p->name == name)
			return true;
		p = p->pNext;
	}
	return false;
}



template<typename T>
inline HashTable<T>::HashTable()
{
	Lists = new Node*[N];
	for (int i = 0; i < N; ++i)
		Lists[i] = nullptr;
}

template<typename T>
inline string HashTable<T>::insert(string name, T & value)//добавляет значение в таблицу 
{//если элемент с таким именем уже есть в таблице, то создается новый элемент со сгенерированным именем
	if (find(name))
	{
		return insert(name + '1', value);
	}
	int key = Hash(name);
	if (Lists[key] == nullptr)
	{
		Lists[key] = new Node(name, value);
		return name;
	}
	Node *p1 = Lists[key];
	Node *p2 = new Node(name, value);
	Lists[key] = p2;
	p2->pNext = p1;
	return name;
}

template<typename T>
inline void HashTable<T>::update(string name, T & value)//добавляет значение в таблицу
{//если элемент с таким именем уже есть в таблице, то его значение обновляется
	int key = Hash(name);
	if (!find(name))
	{
		Node *p = Lists[key];
		Lists[key] = new Node(name, value);
		Lists[key]->pNext = p;
	}
	else
	{
		Node *p = Lists[key];
		while (p->name != name)
			p = p->pNext;
		p->value = value;
	}
}

template<typename T>
inline void HashTable<T>::del(string name)
{
	if (!find(name))
		return;
	int key = Hash(name);
	Node *p = Lists[key];
	if (Lists[key]->name == name)
	{
		Lists[key] = Lists[key]->pNext;
		delete p;
		return;
	}
	while (p->pNext->name != name)
		p = p->pNext;
	Node *tmp = p->pNext;
	p->pNext = tmp->pNext;
	delete tmp;
}

template<typename T>
inline T & HashTable<T>::get(string name)
{
	if (!find(name))
		throw "Object is not found";
	int key = Hash(name);
	Node* p = Lists[key];
	while (p->name != name)
		p=p->pNext;
	return p->value;
}

template<typename T>
inline void HashTable<T>::print()
{
	cout  << setw(max_len_name_1) <<left << "Name" << "|" << "Value" << endl;
	for (int i = 0; i < N; ++i)
	{
		Node *p = Lists[i];
		while (p != nullptr)
		{
			cout << setw(max_len_name_1) << p->name << "|" << p->value << endl;
			p = p->pNext;
		}
	}
}

template<typename T>
inline HashTable<T>::~HashTable()
{
	for (int i = 0; i < N; ++i)
	{
		Node* p = Lists[i];
		while (p != nullptr)
		{
			Node*tmp = p;
			p = p->pNext;
			delete tmp;
		}
	}
	delete[]Lists;
}

