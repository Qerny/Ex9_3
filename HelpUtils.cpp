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
#include "HelpUtils.h"
using namespace std;

//Ввод текстовой информации
string InputInformation(string message)
{
	string a;
	cout << message;
	getline(cin,a);
	while(a == "")
	{
		cout << "Error" << endl;
		getline(cin, a);
	}
	return a;
}

//считывание строки из бинарного файла
std::string StrFromBin(std::fstream *f) {
	std::string result;
	_int32 len;
	if (!f->read(reinterpret_cast<char*>(&len), sizeof(len))) {
		return "";
	}
	char *buf = new char[len];
	if (!f->read(buf, len)) {
		return "";
	}
	result = buf;
	delete[] buf;
	return result;
}

//запись строки в бинарный файл
void StrToBin(std::fstream *f, std::string str) {
	_int32 len = str.length() + 1;
	f->write(reinterpret_cast<char*>(&len), sizeof(len));
	f->write(str.c_str(), len);
}

//перевод числа в строку с помощью потоков
std::string toString(int val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

//Вывести в консоль шапку таблицы студентов
void PrintHeadStudents()
{
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(10) << left << "Record" << "|" << setw(10) << left << "Course" << "|" << setw(10) << left << "Group" << "|" << setw(20) << left << "Surname" << "|" << setw(25) << left << "Number of record book" << "|" <<endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}

//Вывести в консоль шапку таблицы оценок конкретного студента
void PrintHeadMarks()
{
	cout << "--------------------------------------------" <<endl;
	cout << setw(1) << left << "|" << setw(10) << left <<"Record" << "|" << setw(20) << left << "Subject" << "|" << setw(10) << left << "Mark" << "|" << endl;
	cout << "--------------------------------------------" <<endl;
}