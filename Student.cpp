#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "VectorOperations.h"
#include "StudentExam.h"
#include "Student.h"

	//Конструктор по умолчанию
	Student::Student()
	{
		int course = 1;
		string group = "";
		string surname = "";
		string numberRecordBook = "";
		Task<StudentExam> marks;
	}

	//Изменение структуры Student
	Student Student::ChangeStudent(Student &result)
	{
		if (InputNumber(0, 1, "Do you want to change the course " + to_string(result.course) + " (0 - no, 1 - yes)\nYour choice: ") == 1)
			result.course = InputNumber(1, 6, "Enter the new course: ");
		if (InputNumber(0, 1, "Do you want to change the group " + result.group + " (0 - no, 1 - yes)\nYour choice: ") == 1)
			result.group = InputInformation("Enter the new group: ");
		if (InputNumber(0, 1, "Do you want to change the surname " + result.surname + " (0 - no, 1 - yes)\nYour choice: ") == 1)
			result.surname = InputInformation("Enter the new surname: ");
		if (InputNumber(0, 1, "Do you want to change the number of record book " + result.numberRecordBook + " (0 - no, 1 - yes)\nYour choice: ") == 1)
			result.numberRecordBook = InputInformation("Enter the new number: ");

		return result;
	}
	
	//Перегруженный оператор == для Student
	bool Student::operator == (Student st)
	{
		return ((course == st.course) &&
			(group == st.group) &&
			(surname == st.surname) &&
			(numberRecordBook == st.numberRecordBook));
	}
	
	//Запись Student в бинарный файл
	void Student::StudentToFile(std::fstream *file) {
		file->write(reinterpret_cast<char*>(&(this->course)), sizeof(this->course));
		StrToBin(file, this->group);
		StrToBin(file, this->surname);
		StrToBin(file, this->numberRecordBook);
	}

//Загрузка Student из бинарного файла
Student StudentFromFile(std::fstream *file, bool &ok) {
	Student st;
	ok = (bool)file->read(reinterpret_cast<char*>(&(st.course)), sizeof(st.course));
	if (ok)
	{
		st.group = StrFromBin(file);
		st.surname = StrFromBin(file);
		st.numberRecordBook = StrFromBin(file);
	}

	return st;
}

//Функция ввода структуры Student с консоли
Student InputScreenStudent()
{
	Student st;

	st.course = InputNumber(1, 6, "Enter the course (1-6): ");
	st.group = InputInformation("Enter the group: ");
	st.surname = InputInformation("Enter the surname: ");
	st.numberRecordBook = InputInformation("Enter the number of record book: ");

	return st;
}

//Функция вывода структуры Student на консоль
void OutputScreenStudent(Student st)
{
	cout << setw(1) << "|" << setw(10) << left << st.course << "|" << setw(10) << left << st.group << "|" << setw(20) << left << st.surname << "|" << setw(25) << left << st.numberRecordBook << "|";
}

//Перевод структуры Student в строку
string ToString(Student st, int i)
{
	string result = "Record - " + to_string(i) + "\n" + "Course: " + to_string(st.course) + "\n" + "Group: " + st.group + "\n" + "Surname: " + st.surname + "\n" + "Number of record book: " + st.numberRecordBook + "\n";
	return result;
}

//Проверка на равенство двух экземпляров Student
bool IsEqual(Student st1, Student st2)
{
	return ((st1.course == st2.course) &&
		(st1.group == st2.group) &&
		(st1.surname == st2.surname) &&
		(st1.numberRecordBook == st2.numberRecordBook));
}

//считывание структуры Student из строки
Student ReadFromStringSudent(ifstream& input)
{
	Student result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s);
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Course: ";
			result.course = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Group: ";
			result.group = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Surname: ";
			result.surname = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Number of record book: ";
			result.numberRecordBook = s.substr(wrd.length(), s.length());
		}
	}
	catch (...)
	{
		cout << "Error writing to file!" << endl;
	}
	return result;
}

/*Поиск равного элемента по выбранному критерию
type_search - тип поиска:
1 - по группе
2 - по курсу
3 - по номеру зачетной книжки
4 - по фамилии*/
bool SearchElement(Student a, Student b, int type_search)
{
	switch (type_search)
	{
	case 1:
		return (a.group == b.group);
	case 2:
		return (a.course == b.course);
	case 3:
		return (a.numberRecordBook == b.numberRecordBook);
	case 4:
		return (a.surname == b.surname);
	default:
		return false;
	}
}

/*Ввод критерия поиска в зависимости от выбранного типа
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
Student InputChangeTypeSearchStudent(int type_search)
{
	Student result;
	switch (type_search)
	{
	case 1:
		result.group = InputInformation("Enter the group: ");
		return result;
	case 2:
		result.course = InputNumber(1, 6, "Enter the course: ");
		return result;
	case 3:
		result.numberRecordBook = InputInformation("Enter the number of record book: ");
		return result;
	case 4:
		result.surname = InputInformation("Enter the surname: ");
		return result;
	default:
		return result;
	}
}

/*Сравнение структур по выбранного полю
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
int Sorte(Student a, Student b, int type_search)
{
	switch (type_search)
	{
	case 1:
		if (a.group > b.group) return 1;
		else if (a.group < b.group) return -1;
		else return 0;
	case 2:
		if (a.course > b.course) return 1;
		else if (a.course < b.course) return -1;
		else return 0;
	case 3:
		if (a.numberRecordBook > b.numberRecordBook) return 1;
		else if (a.numberRecordBook < b.numberRecordBook) return -1;
		else return 0;
	case 4:
		if (a.surname > b.surname) return 1;
		else if (a.surname < b.surname) return -1;
		else return 0;
	default:
		return -2;
	}
}

//Вычисление среднего балла студента по всем предметам
double AverageScope(Student st)
{
	double res = 0;
	int count = 0;
	for (int i = 0; i < st.marks.size(); i++)
	{
		res += st.marks.vect[i].mark;
		count++;
	}
	if (count == 0) return 0;
	else
		return res / count;
}



