#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "HelpUtils.h"
using namespace std;

template <class Type>
class Task {
private:
	//Сортировка по заданному критерию, Compare - функция, сравнивающая два элемента  
	void Sort(int n, int type_search, int(*Compare)(Type, Type, int))
	{
		int i, j, step;
		Type tmp;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				tmp = vect[i];
				for (j = i; j >= step; j -= step)
				{
					if ((Compare(tmp, vect[j - step], type_search) == -1))
						vect[j] = vect[j - step];
					else
						break;
				}
				vect[j] = tmp;
			}

	}
	//Бинарный поиск, Compare - функция, сравнивающая два элемента 
	int BinarySearchElement(int left, int right, int type_search, Type d, int(*Compare)(Type, Type, int))
	{
		int mid = 0;
		while (1)
		{
			mid = (left + right) / 2;

			if (Compare(d, vect[mid], type_search) == -1)
				right = mid - 1;				
			else if (Compare(d, vect[mid], type_search) == 1) 
				left = mid + 1;					
			else                      
				return mid;          

			if (left > right)
				return -1;
		}
	}
public:
	vector<Type> vect; //сам контейнер
	
	//Удаление элемента
	void Remove(int numb)
	{
		if (numb != 0)
			vect.erase(vect.begin() + numb - 1);
	}

	//Добавление элемента
	void Add(Type &elem)
	{
		for (int i = 0; i < vect.size(); i++)
		{
			if (IsEqual(elem, vect[i]))
			{
				if (InputNumber(0, 1, "\nDo you want to replace the record (0 - no, 1 - yes)\nYour choice: ") == 1)
				{
					vect[i] = elem;
					cout << "record replaced";
					return;
				}
				else
				{
					cout << "record is not replaced";
					return;
				}
			}
		}
		
		vect.push_back(elem);
	}

	//Размер вектора
	int size()
	{
		return vect.size();
	}

	//Проверка на пустоту
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	//Вывод в файл, f - функция, записывающая одну структуру в файл  
	void OutputFile(vector<Type> items, string(*f)(Type, int))
	{
		string newfname = InputFileName();
		ofstream fout(newfname);
		if (fout)
		{
			vector<Type>::const_iterator pos;
			int count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos, count) << ' ';
				count++;
			}
			cout << endl << "File is filled" << endl;
			fout.close();
		}
		else
		{
			cout << "File is not filled" << endl;
		}
	}

	//Вывод на экран, f - функция, которая выводит одну структуру на экран  
	void OutputScreen(vector<Type> items, void(*f) (Type))
	{
		vector<Type>::const_iterator pos;
		int count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(10) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "Vector is empty" << endl;
	}

	//Ввод из файла, f - функция, которая считывает одну структуру из файла 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		std::ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "Could not open file" << endl;
			return false;
		}
		else
		{
			while (!input.eof())
			{
				vect.push_back(f(input));
			}
			vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	//Ввод с экрана, f - функция, которая вводит одну структуру с консоли
	void ReadFromScreen(Type(*f)())
	{
		int n;
		Type elem;
		do
		{
			Add(f());
			n = InputNumber(0, 1, "\nDo you want to add an element? (1 - yes, 0 - no)\nYour choice: ");
		} while (n != 0);
	}

	//Линейный поиск, Equal - функция, проверяющая равенство эл-та с текущим по type_search
	vector<Type> LineSearch(Type search_elem, bool(*Equal)(Type, Type, int), int type_search)
	{
		vector<Type> NewVect;
		for (auto iter = vect.begin(); iter != vect.end(); iter++)
		{
			if (Equal(search_elem, *iter, type_search))
				NewVect.push_back(*iter);
		}

		return NewVect;
	}

	//Бинарный поиск, Compare - функция, сравнивающая два элемента по type_search, Equal - функция, проверяющая равенство искомого эл-та с текущим по type_search
	vector<Type> BinarySearch(int type_search, Type find_element, int(*Compare)(Type, Type, int), bool(*Equal)(Type, Type, int))
	{
		vector<Type> NewVect;
		Sort(vect.size(), type_search, Compare);
		int left = 0;
		int right = vect.size();
		int index;
		if ((index = BinarySearchElement(left, right - 1, type_search, find_element, Compare)) != -1)
		{
			NewVect.push_back(vect[index]);
			int first_index = index;
			while ((++index<right) && Equal(vect[index], find_element, type_search))
				NewVect.push_back(vect[index]);
			while ((--first_index >= 0) && Equal(vect[first_index], find_element, type_search))
				NewVect.push_back(vect[first_index]);
		}
		return NewVect;
	}
};
