#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

class StudentExam {
public:
	string subject;
	int mark;

	//Конструктор по умолчанию
	StudentExam();

	//Изменение структуры Student
	StudentExam ChangeStudentExam(StudentExam &result);

	//Перегруженный оператор присваивания для структуры Student
	StudentExam& operator = (StudentExam s);

	//Запись экземпляра класса StudentExam в бинарный файл
	void StudentExamToFile(std::fstream *file);
};

//Загрузка экземпляра класса StudentExam из бинарного файла
StudentExam StudentExamFromFile(std::fstream *file, bool &ok);

//Функция ввода структуры Student с консоли
StudentExam InputScreenStudentExam();

//Функция вывода структуры Student на консоль
void OutputScreenStudentExam(StudentExam st);

//Перевод структуры Student в строку
string ToString(StudentExam st, int i);

//Проверка на равенство двух экземпляров StudentExam
bool IsEqual(StudentExam st1, StudentExam st2);

//считывание структуры Student из строки
StudentExam ReadFromString(ifstream& input);