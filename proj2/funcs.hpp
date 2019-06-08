//ICS 45C - Project #2: Letter Never Sent
//Code made by Aljon Viray, ID: 86285526
#include <iostream>
#include <string>
#include <sstream>

#ifndef FUNCS_HPP
#define FUNCS_HPP


struct Student
{
	int id;
	char gradeOption;
	std::string name;
	double score = 0;
};

double* createDoubleArray (int n, std::string str);

double** fill2dDoubleArray (int x, int y, std::string str, double** array);

double** create2dDoubleArray (int x, int y, std::string str);

Student* createStudentArray (int n);

double calculateTotalScore (int n, double* scores, double* points, double* weights);

std::string giveLetterGrade (Student student, double* cutpointsSet);


#endif // FUNCS_HPP