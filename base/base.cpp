#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include "HashTable.h"
#include "AVLTree.h"
using namespace std;


void printmenu()
{
	cout << "Выберите действие: " <<endl ;
	cout << "1 - ввод полинома" << endl;
	cout << "2 - сложение" << endl;
	cout << "3 - умножение" << endl;
	cout << "4 - вычитание" << endl;
	cout << "5 - дифференцирование" << endl;
	cout << "6 - интегрирование" << endl;
	cout << "7 - удаление элемента из таблицы" << endl;
	cout << "8 - вывод таблицы" << endl;
	cout << "0 - выход" << endl;
}

pair<string, string> inputnames()
{
	pair<string, string> a;
	string s;
	cout << "Введите имя первого полинома:" << endl;
	cin >> a.first;
	cout << "Введите имя второго полинома:" << endl;
	cin >> a.second;
	return a;
}


pair<Polynom, string> input()
{
	pair<Polynom, string> ans;
	string poly;
	cout << "Введите имя полинома:" << endl;
	cin >> ans.second;
	cout << "Введите полином: (например x2y2 + z3)" << endl;
	cin.ignore();
	getline(cin, poly);
	Polynom a(poly);
	ans.first = a;
	return ans;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	AVLTree<Polynom> table;
	printmenu();
	cout << "Введите номер действия и нажмите Enter: (например, 1)" << endl;
	int a;
	cin >> a;
	while (a != 0)
	{
		if (a == 1)
		{
			pair<Polynom, string> b = input();
			string name = table.insert(b.second, b.first);
			if (name != b.second)
			{
				cout << "Ваш полином был успешно добавлен в ячейку таблицы с именем " << name << endl;
			}
			else
			{
				cout << "Ваш полином был успешно добавлен в ячейку таблицы" << endl;
			}
		}
		else if (a == 2)
		{
			pair<string, string> names = inputnames();
			if (!table.find(names.first) || !table.find(names.second))
			{
				cout << "Одно или несолько имен не найдены." << endl;
				table.print();
				cout << "Повторите ввод используя сущетсвующие имена:" << endl;
			}
			else
			{
				string name_res;
				cout << "Введите имя полинома для сохранения результата в таблицу: " << endl;
				cin >> name_res;
				Polynom c = table.get(names.first);
				Polynom d = table.get(names.second);
				c += d;
				table.update(name_res, c);
			}
		}
		else if (a == 3)
		{
			pair<string, string> names1 = inputnames();
			if (!table.find(names1.first) || !table.find(names1.second))
			{
				cout << "Одно или несолько имен не найдены." << endl;
				table.print();
				cout << "Повторите ввод используя сущетсвующие имена:" << endl;
			}
			else
			{
				string name_res;
				cout << "Введите имя полинома для сохранения результата в таблицу: " << endl;
				cin >> name_res;
				Polynom c = table.get(names1.first);
				Polynom d = table.get(names1.second);
				c *= d;
				table.update(name_res, c);
			}
		}
		else if (a == 4)
		{
			pair<string, string> names2 = inputnames();
			if (!table.find(names2.first) || !table.find(names2.second))
			{
				cout << "Одно или несолько имен не найдены." << endl;
				table.print();
				cout << "Повторите ввод используя сущетсвующие имена:" << endl;
			}
			else
			{
				string name_res;
				cout << "Введите имя полинома для сохранения результата в таблицу: " << endl;
				cin >> name_res;
				Polynom c = table.get(names2.first);
				Polynom d = table.get(names2.second);
				c -= d;
				table.update(name_res, c);
			}
		}
		else if (a == 5)
		{
			cout << "Введите имя полинома:" << endl;
			string name1;
			cin >> name1;
			if (!table.find(name1))
			{
				cout << "Имя не найдено. " << endl;
				table.print();
				cout << "Повторите ввод используя существующее имя:" << endl;
			}
			else
			{
				cout << "Выберите переменную для дифференцирования." << endl;
				cout << "1 - x" << endl;
				cout << "2 - y" << endl;
				cout << "3 - z" << endl;
				cout << "Введите число:" << endl;
				int a;
				cin >> a;
				Polynom c = table.get(name1);
				if (a == 1)
					c.dfdx();
				else if (a == 2)
					c.dfdy();
				else if (a == 3)
					c.dfdz();
				else
				{
					cout << "Ошибка. Повторите ввод:" << endl;
					break;
				}
				string name_res;
				cout << "Введите имя полинома для сохранения результата в таблицу: " << endl;
				cin >> name_res;
				table.update(name_res, c);
			}
		}
		else if (a == 6)
		{
			cout << "Введите имя полинома:" << endl;
			string name1;
			cin >> name1;
			if (!table.find(name1))
			{
				cout << "Имя не найдено. " << endl;
				table.print();
				cout << "Повторите ввод используя существующее имя:" << endl;
			}
			else
			{
				cout << "Выберите переменную для интегрирования." << endl;
				cout << "1 - x" << endl;
				cout << "2 - y" << endl;
				cout << "3 - z" << endl;
				cout << "Введите число:" << endl;
				int a;
				cin >> a;
				Polynom c = table.get(name1);
				if (a == 1)
					c.dx();
				else if (a == 2)
					c.dy();
				else if (a == 3)
					c.dz();
				else
				{
					cout << "Ошибка. Повторите ввод:" << endl;
					break;
				}
				string name_res;
				cout << "Введите имя полинома для сохранения результата в таблицу: " << endl;
				cin >> name_res;
				table.update(name_res, c);
			}
		}
		else if(a == 7)
		{
			string name;
			cout << "Введите имя полинома:" << endl;
			cin >> name;
			table.del(name);
			cout << "Элемент успешно удален" << endl;
		}
		else if (a == 8)
		{
			table.print();
		}
		string s;
		cout << "Нажмите Enter для продолжения" << endl;
		_getch();
		printmenu();
		cin >> a;
	}

}