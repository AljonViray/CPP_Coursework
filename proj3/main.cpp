// main.cpp
//
// Code made by Aljon Viray, ID: 86285526
// ICS 45C Winter 2019
// Project #3: Maps and Legends

#include <sstream>
#include "Commands.hpp"


int main()
{
	HashMap hashMap;
	std::string line, input1, input2, input3, garbage;
	bool debug = false, running = true;

	while(running == true)
	{
		// Reset input strings
		line = "", input1 = "", input2 = "", input3 = "", garbage = "";

		std::getline(std::cin, line);
		std::stringstream stream(line);

		stream >> input1;
		stream >> input2;
		stream >> input3;
		stream >> garbage;	// Only up to 3 useable words/inputs allowed, the rest is garbage

		handleCommands(input1, input2, input3, garbage, debug, running, hashMap);
	}
}