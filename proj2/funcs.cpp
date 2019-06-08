//ICS 45C - Project #2: Letter Never Sent
//Code made by Aljon Viray, ID: 86285526
#include "funcs.hpp"


double* createDoubleArray (int n, std::string str)
{
	//Create dynamically-allocated array for doubles
	double* doubleArray = new double[n];

	//Create stringstream from a string
	std::stringstream stream(str);

	//Fill array with items from stringstream
    for (int i = 0; i < n && stream.good(); i++)
    	{stream >> doubleArray[i];}

    //Return filled array
    return doubleArray;
}


double** fill2dDoubleArray (int x, int y, std::string str, double** array)
{
	//For each array, fill that set with scores from getline
	for (int i = 0; i < x; i++)
	{
		std::getline(std::cin, str);
		std::stringstream stream(str);

	    for (int j = 0; j < y && stream.good(); j++)
	    {
	        stream >> array[i][j];
	    }
	}

	//Return filled array
	return array;
}


double** create2dDoubleArray (int x, int y, std::string str)
{
	//Creates an array of size x that will contain pointers to double arrays
	double** doubleDoubleArr = new double*[x];

	//Fills one-dimension array with more arrays of size y
	for (int i = 0; i < x; i++)
		{doubleDoubleArr[i] = new double[y];}

	//Fill all entries of all arrays
	doubleDoubleArr = fill2dDoubleArray(x, y, str, doubleDoubleArr);

	//Return empty 2D array
	return doubleDoubleArr;
}


Student* createStudentArray (int n)
{
	//Create dynamically-allocated array for Students (a struct I made)
	Student* studentsArr = new Student[n];

	//Fill array with students with attributes
    for (int i = 0; i < n; i++)
    {
    	//Initialize new Student struct
    	Student newStudent;

    	//Get Student attributes
   		std::cin >> newStudent.id >> newStudent.gradeOption;
   		std::cin.ignore();  //Ignore extra whitespace
   		std::getline(std::cin, newStudent.name);

   		//Put new student in array
    	studentsArr[i] = newStudent;
    }

    //Return filled array
    return studentsArr;
}


double calculateTotalScore (int n, double* scores, double* points, double* weights)
{
	double totalScore = 0;

	//Adds weighted score percentage to total score
	for (int i = 0; i < n; i++)
	{
		totalScore += ( (scores[i+1] / points[i]) * weights[i] );
	}

	return totalScore;
}


std::string giveLetterGrade (Student student, double* cutpointsSet)
{
	std::string grade = "";

	//If the student has "Letter Grade" grade option
	if (student.gradeOption == 'G')
	{
		if (student.score >= cutpointsSet[0])
			{grade = "A";}
		else if (student.score >= cutpointsSet[1])
			{grade = "B";}
		else if (student.score >= cutpointsSet[2])
			{grade = "C";}
		else if (student.score >= cutpointsSet[3])
			{grade = "D";}
		else
			{grade = "F";}
	}

	//If the student has "Pass/No Pass" grade option
	else if (student.gradeOption == 'P')
	{
		if (student.score >= cutpointsSet[2])
			{grade = "P";}
		else
			{grade = "NP";}
	}

	return grade;
}