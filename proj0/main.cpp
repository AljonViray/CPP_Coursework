#include <iostream>


std::string strMultiply(std::string x, int n)
{
	std::string result = "";
	for (int i = 0; i < (n-1); i++)
	{
		result += x;
	}
	return result;
}

int main()
{
	int n;
	std::string str1 = "***";
	std::string str2 = "* *";
	std::string spaces = " ";

	std::cin >> n;  //Input a number
	spaces = strMultiply(spaces, n);  //Create n number of spaces

	for (int i = 0; i < n; i++)
	{
		std::cout << spaces + str1 << std::endl;  //Prints full stars
		std::cout << spaces + str2 << std::endl;  //Prints spaced stars

		if (i+1 == n)  //If for loop is about to finish
		{
			std::cout << spaces + str1 << std::endl;
		}

		spaces.erase(0, 1);  //Erase 1 space
		str1 = str1 + "**";
		str2 = str2 + " *";
	}

}