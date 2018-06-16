#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cstring>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

template <class Type>
//Вспомогательная функция для ввода числа в указанном интервале
Type InputNumber(Type min, Type max, string message)
{
	Type n;
	do
	{
		cout << message;
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cin.clear();  // восстанавливает поток если он в ошибочном сосотянии
			cin.sync();   // очищает поток от имеющихся символов
			cout << message;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} 
	} while ((n < min) || (n > max));
	return n;
}

//Ввод текстовой информации
string InputInformation(string message);

//считывание строки из бинарного файла
std::string StrFromBin(std::fstream *f);

//запись строки в бинарный файл
void StrToBin(std::fstream *f, std::string str);

//перевод числа в строку с помощью потоков
std::string toString(int val);

//Вывести в консоль шапку таблицы студентов
void PrintHeadStudents();

//Вывести в консоль шапку таблицы оценок конкретного студента
void PrintHeadMarks();