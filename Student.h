#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

class Student {
public:
	int course;
	string group;
	string surname;
	string numberRecordBook;
	Task<StudentExam> marks;

	//Конструктор по умолчанию
	Student();

	//Изменение структуры Student
	Student ChangeStudent(Student &result);

	//Перегруженный оператор == для Student
	bool operator == (Student st);

	//Запись Student в бинарный файл
	void StudentToFile(std::fstream *file);
};

//Загрузка Student из бинарного файла
Student StudentFromFile(std::fstream *file, bool &ok);

//Функция ввода структуры Student с консоли
Student InputScreenStudent();

//Функция вывода структуры Student на консоль
void OutputScreenStudent(Student st);

//Перевод структуры Student в строку
string ToString(Student st, int i);

//Проверка на равенство двух экземпляров Student
bool IsEqual(Student st1, Student st2);

//считывание структуры Student из строки
Student ReadFromStringSudent(ifstream& input);

/*Поиск равного элемента по выбранному критерию
type_search - тип поиска:
1 - по группе
2 - по курсу
3 - по номеру зачетной книжки
4 - по фамилии*/
bool SearchElement(Student a, Student b, int type_search);

/*Ввод критерия поиска в зависимости от выбранного типа
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
Student InputChangeTypeSearchStudent(int type_search);

/*Сравнение структур по выбранного полю
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
int Sorte(Student a, Student b, int type_search);

//Вычисление среднего балла студента по всем предметам
double AverageScope(Student st);



