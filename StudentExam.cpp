#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "StudentExam.h"


	//Конструктор по умолчанию
	StudentExam::StudentExam()
	{
		string subject = "";
		int mark = 2;
	}

	//Изменение структуры Student
	StudentExam StudentExam::ChangeStudentExam(StudentExam &result)
	{
		if (InputNumber(0, 1, "Do you want to change the subject " + result.subject + " (0 - no, 1 - yes)\nYour choice: ") == 1)
			result.subject = InputInformation("Enter the new subject: ");
		if (InputNumber(0, 1, "Do you want to change the mark " + to_string(result.mark) + " (0 - no, 1 - yes)\nYour choice: ") == 1)
			result.mark = InputNumber(2,5,"Enter the new group: ");

		return result;
	}

	//Перегруженный оператор присваивания для структуры Student
	StudentExam& StudentExam::operator = (StudentExam s)
	{
		subject = s.subject;
		mark = s.mark;

		return (*this);
	}
	
	//Запись экземпляра класса StudentExam в бинарный файл
	void StudentExam::StudentExamToFile(std::fstream *file) {
		StrToBin(file, this->subject);
		file->write(reinterpret_cast<char*>(&(this->mark)), sizeof(this->mark));
	}

//Загрузка экземпляра класса StudentExam из бинарного файла
StudentExam StudentExamFromFile(std::fstream *file, bool &ok) 
{
	StudentExam st_ex;
	st_ex.subject = StrFromBin(file);
	ok = (bool)file->read(reinterpret_cast<char*>(&(st_ex.mark)), sizeof(st_ex.mark));

	return st_ex;
}

//Функция ввода структуры Student с консоли
StudentExam InputScreenStudentExam()
{
	StudentExam s;

	s.subject = InputInformation("Enter the name of subject: ");
	s.mark = InputNumber(2,5,"Enter the mark (2-5): ");

	return s;
}

//Функция вывода структуры Student на консоль
void OutputScreenStudentExam(StudentExam st)
{
	/*cout << "Subject: " << st.subject << endl;
	cout << "Mark: " << st.mark << endl;*/
	cout << setw(1) << left << "|" << setw(20) << left << st.subject << "|" << setw(10) << left << st.mark << "|";
}

//Перевод структуры Student в строку
string ToString(StudentExam st, int i)
{
	string result = "Record - " + to_string(i) + "\n" + "Subject: " + st.subject + "\n" + "Mark: " + to_string(st.mark) + "\n";
	return result;
}

//Проверка на равенство двух экземпляров StudentExam
bool IsEqual(StudentExam st1, StudentExam st2)
{
	return 
		((st1.subject == st2.subject) &&
		(st1.mark == st2.mark));
}

//считывание структуры Student из строки
StudentExam ReadFromString(ifstream& input)
{
	StudentExam result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Subject: ";
			result.subject = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Mark: ";
			result.mark = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
	}
	catch (...)
	{
		cout << "Error writing to file!" << endl;
	}
	return result;
}
