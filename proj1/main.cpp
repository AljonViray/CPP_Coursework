//Code made by Aljon Viray, ID: 86285526
#include "main.hpp"
#include "math.hpp"


std::string getName()
{
	std::string word, name;

	while (true)  //while loop for getting location name
	{
		std::cin >> word;
		name += word;
		if(std::cin.get() == '\n')  //If end of line
		{
			break;
		}
		name += " ";
	}

	return name;
}


int main()
{
	//Starting Location section
	std::cin >> startLat >> startLatDir >> startLon >> startLonDir;  //for values and directions
	startLat  = directionConverter(startLat, startLatDir);
	startLon  = directionConverter(startLon, startLonDir);
	startName = getName();

	//New (Target) Location(s) section
	std::cin >> numOfTargets;
	for (int i=0; i<numOfTargets; i++)
	{
		std::cin >> newLat >> newLatDir >> newLon >> newLonDir;
		newLat  = directionConverter(newLat, newLatDir);
		newLon  = directionConverter(newLon, newLonDir);
		newName = getName();

		newDist = calculateDistance(startLat, newLat, startLon, newLon);

		//First location gets both closest and farthest spots initially
		if (closeDist == 0 && farDist == 0)
		{
			closeLat   = newLat,  closeLatDir = newLatDir,
			closeLon   = newLon,  closeLonDir = newLonDir,
			closeName  = newName, closeDist   = newDist;

			farLat     = newLat,  farLatDir   = newLatDir,
			farLon     = newLon,  farLonDir   = newLonDir,
			farName    = newName, farDist     = newDist;
		}

		//Every other location will replace "closest" or "farthest", OR be discarded.
		else if (newDist < closeDist)
		{
			closeLat   = newLat,  closeLatDir = newLatDir,
			closeLon   = newLon,  closeLonDir = newLonDir,
			closeName  = newName, closeDist   = newDist;
		}
		else if (newDist > farDist)
		{
			farLat     = newLat,  farLatDir   = newLatDir,
			farLon     = newLon,  farLonDir   = newLonDir,
			farName    = newName, farDist     = newDist;
		}
	}

	//Output section
	std::cout << "Start Location: " << startLat << startLatDir + " " 
									<< startLon << startLonDir + " " 
									<< "(" + startName + ")" << std::endl;

	std::cout << "Closest Location: " << closeLat << closeLatDir + " " 
									  << closeLon << closeLonDir 
									  << " (" + closeName + ")" 
									  << " (" << closeDist << " mi)" << std::endl;

	std::cout << "Farthest Location: " << farLat << farLatDir + " " 
									   << farLon << farLonDir 
									   << " (" + farName + ")" 
									   << " (" << farDist << " mi)" << std::endl;
}