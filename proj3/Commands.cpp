// Commands.cpp
//
// Code made by Aljon Viray, ID: 86285526
// ICS 45C Winter 2019
// Project #3: Maps and Legends

#include "Commands.hpp"


// "Main Commands" Function
void handleCommands(const std::string& input1, const std::string& input2, const std::string& input3, const std::string& garbage, bool& debug, bool& running, HashMap& hashMap)
{
	if(garbage != "")
	{
		std::cout << "INVALID" << std::endl;
	}

	// User-facing Commands
	else if(input1 == "CREATE" && input2 != "" && input3 != "")
	{
		create(input2, input3, hashMap);
	}

	else if(input1 == "LOGIN" && input2 != "" && input3 != "")
	{
		login(input2, input3, hashMap);
	}

	else if(input1 == "REMOVE" && input2 != "" && input3 == "")
	{
		remove(input2, hashMap);
	}

	else if(input1 == "CLEAR" && input2 == "" && input3 == "")
	{
		clear(hashMap);
	}

	// Debug Commands
	else if(input1 == "DEBUG" && input2 != "" && input3 == "")
	{
		toggleDebug(input2, debug);
	}

	else if(debug == true && input1 == "LOGIN" && input2 == "COUNT" && input3 == "")
	{
		std::cout << hashMap.size() << std::endl;
	}

	else if(debug == true && input1 == "BUCKET" && input2 == "COUNT" && input3 == "")
	{
		std::cout << hashMap.bucketCount() << std::endl;
	}

	else if(debug == true && input1 == "LOAD" && input2 == "FACTOR" && input3 == "")
	{
		std::cout << hashMap.loadFactor() << std::endl;
	}

	else if(debug == true && input1 == "MAX" && input2 == "BUCKET" && input3 == "SIZE")
	{
		std::cout << hashMap.maxBucketSize() << std::endl;
	}

	//Other Commands
	else if(input1 == "QUIT")
	{
		running = false;
		std::cout << "GOODBYE" << std::endl;
	}

	else
	{
		std::cout << "INVALID" << std::endl;
	}
}


////////////////////////////////////////////////////////////


// "User-facing Commands" Functions
void create(const std::string& username, const std::string& password, HashMap& hashMap)
{
	if (hashMap.contains(username) == true)
	{
		std::cout << "EXISTS" << std::endl;
	}

	else
	{
		hashMap.add(username, password);
		std::cout << "CREATED" << std::endl;
	}
}


void login(const std::string& username, const std::string& password, HashMap& hashMap)
{
	if(hashMap.contains(username) && hashMap.value(username) == password)
	{
		std::cout << "SUCCEEDED" << std::endl;
	}

	else
	{
		std::cout << "FAILED" << std::endl;
	}
}


void remove(const std::string& username, HashMap& hashMap)
{
	if(hashMap.contains(username))
	{
		hashMap.remove(username);
		std::cout << "REMOVED" << std::endl;
	}

	else
	{
		std::cout << "NONEXISTENT" << std::endl;
	}
}


void clear(HashMap& hashMap)
{
	hashMap.clearAll();
	std::cout << "CLEARED" << std::endl;
}


// Debug Command
void toggleDebug(const std::string& state, bool& debug)
{
	if(state == "ON")
	{
		if(debug == false)
		{
			debug = true;
			std::cout << "ON NOW" << std::endl;
		}

		else
		{
			std::cout << "ON ALREADY" << std::endl;
		}
	}


	else if(state == "OFF")
	{
		if(debug == true)
		{
			debug = false;
			std::cout << "OFF NOW" << std::endl;
		}

		else
		{
			std::cout << "OFF ALREADY" << std::endl;
		}
	}


	else
	{
		std::cout << "INVALID" << std::endl;
	}
}