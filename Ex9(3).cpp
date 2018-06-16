/*
Реализовать справочник деканата. Реализовать управление списком студентов (поступление, обновление данных и отчисление). 
Предусмотреть вывод результатов сессии с группировкой по заданному критерию (например, курс, группа, дисциплина и т.п.). 
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "HelpUtils.h"
#include "VectorOperations.h"
#include "StudentExam.h"
#include "Student.h"
using namespace std;

//сохранение студентов в файл
void SaveStudentsToFile(std::string fileName, Task<Student> students) {
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (!file.is_open())
		throw "file is not open";
	int i;
	for (i = 0; i < students.size(); ++i) {
		students.vect[i].StudentToFile(&file);
	}
	file.close();
}

//Сохранение оценок студента в файл
void SaveStudentMarksToFile(std::string fileName, Student student) {
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (!file.is_open())
		throw "file is not open";
	
	student.StudentToFile(&file);
	for (int i = 0; i < student.marks.size(); ++i) {
		student.marks.vect[i].StudentExamToFile(&file);
	}
	file.close();
}

//Загрузка студентов из файла
void LoadStudentsFromFile(std::string fileName, Task<Student> &students) {
	std::fstream file;
	file.open(fileName, std::ios::binary | std::ios::in);
	if (!file.is_open())
		return;
	
	bool ok;
	while(!file.eof())
	{
		Student st = StudentFromFile(&file, ok);
		if (ok)
			students.Add(st);
	}
	file.close();
}

//Загрузка оценок конкретного студента из файла
void LoadStudentMarksFromFile(std::string fileName, Task<Student> &students) {
	std::fstream file;
	file.open(fileName, std::ios::binary | std::ios::in);
	if (!file.is_open())
		throw "file is not open";

	Student st;
	bool ok;

	st = StudentFromFile(&file,ok);
	for (int i = 0; i < students.size();i++) {
		if (IsEqual(st, students.vect[i]))
		{
			bool ok = true;
			while (!file.eof())
			{
				StudentExam st_ex = StudentExamFromFile(&file, ok);
				if (ok)
					students.vect[i].marks.Add(st_ex);
			}
		}
	}
	file.close();
}

void main()
{
	Task<Student> students;
	LoadStudentsFromFile("Students.dat", students);
	for (int i = 0; i < students.size(); i++)
	{
		LoadStudentMarksFromFile("Student" + toString(i) + ".dat", students);
	}

	cout << "Select the operating mode: " << endl;
	cout << "1 - Student" << endl;
	cout << "2 - Dean's office" << endl;
	cout << "0 - Exit" << endl << endl;
	int mode = InputNumber(0, 2, "Your choice: ");
	switch (mode)
	{
	case 1:
	{
		bool IsExist = false;
		string numbRecBook;
		int i;
		do
		{
			numbRecBook = InputInformation("Input your Number of the record book: ");
			for (i = 0; i < students.size(); i++)
			{
				if (students.vect[i].numberRecordBook == numbRecBook)
				{
					IsExist = true;
					break;
				}
			}
		} while (!IsExist);

		while (1)
		{
			cout << endl;
			cout << "1 - Output marks" << endl;
			cout << "2 - Calculate average score" << endl;
			cout << "0 - Exit" << endl;
			int changemenu = InputNumber(0, 4, "Your choice: ");

			switch (changemenu)
			{
			case 1:
			{
				PrintHeadMarks();
				students.vect[i].marks.OutputScreen(students.vect[i].marks.vect, OutputScreenStudentExam);
				break;
			}
			case 2:
			{
				cout <<"Your average scope: " << AverageScope(students.vect[i]) << endl;
				break;
			}
			}
		}
		break;
	}
	case 2:
	{
		while (1)
		{
			cout << endl;
			cout << "1 - Add the student" << endl;
			cout << "2 - Update student data" << endl;
			cout << "3 - Delete the student" << endl;
			cout << "4 - Output the session results" << endl;
			cout << "5 - Output students" << endl;
			cout << "0 - Exit" << endl << endl;
			int changemenu = InputNumber(0, 5, "Your choice: ");

			switch (changemenu)
			{
			case 1:
			{
				students.Add(InputScreenStudent());
				break;
			}
			case 2:
			{
				cout << "1 - Change student information" << endl;
				cout << "2 - Add student mark" << endl;
				cout << "3 - Change student mark" << endl;
				cout << "4 - Remove student mark" << endl << endl;
				int a = InputNumber(1, 4, "Your choice: ");
				switch (a)
				{
				case 1:
				{
					cout << endl;
					PrintHeadStudents();
					students.OutputScreen(students.vect, OutputScreenStudent);
					int numb = InputNumber(0, students.size(), "Enter the number of the element to be changed (0 - if you change your mind): ");

					Student elem;

					if (numb != 0)
					{
						students.vect[numb - 1] = elem.ChangeStudent(students.vect[numb - 1]);
					}
					break;
				}
				case 2:
				{
					PrintHeadStudents();
					students.OutputScreen(students.vect, OutputScreenStudent);
					int numb = InputNumber(0, students.size(), "Enter the number of the element to be changed (0 - if you change your mind): ");

					if (numb != 0)
						do
						{
							students.vect[numb - 1].marks.Add(InputScreenStudentExam());
						} while (InputNumber(0, 1, "\nDo you want to add an element? (1 - yes, 0 - no)\nYour choice: ") == 1);
						break;
				}
				case 3:
				{
					//Вывод студентов для выбора
					PrintHeadStudents();
					students.OutputScreen(students.vect, OutputScreenStudent);
					int numb = InputNumber(0, students.size(), "Enter the number of the student to be changed (0 - if you change your mind): ");

					//Вывод оценок выбранного студента для выбора
					if (numb != 0) 
					{
						PrintHeadMarks();
						students.vect[numb - 1].marks.OutputScreen(students.vect[numb - 1].marks.vect, OutputScreenStudentExam);
					}

					int numb_mark = InputNumber(0, students.size(), "Enter the number of the mark to be changed (0 - if you change your mind): ");
					StudentExam elem;

					if (numb_mark != 0)
					{
						students.vect[numb - 1].marks.vect[numb_mark - 1] = elem.ChangeStudentExam(students.vect[numb - 1].marks.vect[numb - 1]);
					}
					break;
				}
				case 4:
				{
					PrintHeadStudents();
					students.OutputScreen(students.vect, OutputScreenStudent);
					int numb = InputNumber(0, students.size(), "Enter the number of the student to be changed (0 - if you change your mind): ");

					if (numb != 0) {
						PrintHeadMarks();
						students.vect[numb - 1].marks.OutputScreen(students.vect[numb - 1].marks.vect, OutputScreenStudentExam);
					}

					students.vect[numb - 1].marks.Remove(InputNumber(0, students.vect[numb - 1].marks.size(), "Enter the number of the mark to remove (0 - if you change your mind to delete): "));
					break;
				}
				}
				break;
			}
			case 3:
			{
				PrintHeadStudents();
				students.OutputScreen(students.vect, OutputScreenStudent);
				students.Remove(InputNumber(0, students.size(), "Enter the number of the student to remove (0 - if you change your mind to delete): "));
				break;
			}
			case 4:
			{
				Student elem;
				vector<Student> subset;
				Student search_elem;
				int numb = InputNumber(1, 4, "Choose the type of search:\n 1 - by group\n 2 - by course\n 3 - by number of record book\n 4 - by surname\n\nYour choice: ");
				search_elem = InputChangeTypeSearchStudent(numb);
				subset = students.LineSearch(search_elem, SearchElement, numb);
				if (subset.size() != 0)
				{
					for(int i=0; i<subset.size(); i++)
					{
						OutputScreenStudent(students.vect[i]);
						cout<<endl;
						PrintHeadMarks();
						students.vect[i].marks.OutputScreen(students.vect[i].marks.vect, OutputScreenStudentExam);
						cout << endl;
					}
				}
				else
					cout << "Items is not found" << endl;
				break;
			}
			case 5:
			{
				PrintHeadStudents();
				students.OutputScreen(students.vect, OutputScreenStudent);
				break;
			}
			default:
			{
				SaveStudentsToFile("Students.dat", students);
				for (int i = 0; i < students.size(); i++)
					SaveStudentMarksToFile("Student" + toString(i) +".dat", students.vect[i]);
				exit(0);
				break;
			}
			}
		}
		default:
		{
			SaveStudentsToFile("Students.dat", students);
			for (int i = 0; i < students.size(); i++)
				SaveStudentMarksToFile("Student" + toString(i) + ".dat", students.vect[i]);
			exit(0);
			break;
		}
		}
	}
}
