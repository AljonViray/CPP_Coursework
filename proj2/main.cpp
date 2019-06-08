//ICS 45C - Project #2: Letter Never Sent
//Code made by Aljon Viray, ID: 86285526
#include "main.hpp"


int main()
{
	//Graded Artifacts
	std::cin >> numOfArtifacts;
	std::cin.ignore();  //Removes the extra '/n' from cin so getline doesn't end early
	std::getline(std::cin, pointsStr);
	std::getline(std::cin, weightsStr);
	pointsArr = createDoubleArray(numOfArtifacts, pointsStr);
	weightsArr = createDoubleArray(numOfArtifacts, weightsStr);


    //Students
	std::cin >> numOfStudents;
	std::cin.ignore();
	studentsArr = createStudentArray(numOfStudents);


    //Raw Scores
	std::cin >> numOfScores;
	std::cin.ignore();
	scoresArr = create2dDoubleArray(numOfScores, numOfArtifacts+1, scoresStr);


	//Total Scores
	std::cout << "TOTAL SCORES" << std::endl;
	for (int i = 0; i < numOfScores; i++)
	{
		//Iterate through every student, Assign score to student if matching ID
		for (int j = 0; j < numOfStudents; j++)
		{
			//Note: student ID from raw scores input is stored in scoresArr[i][0]
			if (scoresArr[i][0] == studentsArr[j].id)
			{
				studentsArr[j].score = calculateTotalScore(numOfArtifacts, scoresArr[i], pointsArr, weightsArr);
				break;
			}
		}
	}

	//Output of all student scores
	for (int i = 0; i < numOfStudents; i++)
	{
		std::cout << studentsArr[i].id << " " << studentsArr[i].name << " " << studentsArr[i].score << std::endl;
	}


	//Cutpoint Sets
	std::cin >> numOfCutpoints;
	std::cin.ignore();

	for (int i = 0; i < numOfCutpoints; i++)
	{
	    std::cout << "CUTPOINT SET " << (i+1) << std::endl;

	    std::getline(std::cin, cutpointsStr);
	    cutpointsArr = createDoubleArray(4, cutpointsStr);

	    for (int j = 0; j < numOfStudents; j++)
	    {
    		std::cout << studentsArr[j].id << " " << studentsArr[j].name << " " << giveLetterGrade(studentsArr[j], cutpointsArr) << std::endl;
	    }

	    delete[] cutpointsArr;
	}


	//Array allocation cleanup
	delete[] pointsArr;
	delete[] weightsArr;
	delete[] studentsArr;

	for (int i = 0; i < numOfScores; i++)
		{delete[] scoresArr[i];}
	delete[] scoresArr;
}