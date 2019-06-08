//Code made by Aljon Viray, ID: 86285526
#include "math.hpp"


float degreesToRadians(float degrees)
{
	float radians = (degrees * M_PI)/180; //Convert degrees to radians
	return radians;
}


float directionConverter(float value, std::string direction)
{
	if (direction == "/S" or direction == "/E")
	{
		return -1*value;
	}
	return value;
}


float calculateDistance(float lat1, float lat2, float lon1, float lon2)
{
	float R = 3959.9;
	float diameter, dlat, dlon;
	float a, c;

	lat1 = degreesToRadians(lat1), lat2 = degreesToRadians(lat2),
	lon1 = degreesToRadians(lon1), lon2 = degreesToRadians(lon2);

	dlat = abs(lat1 - lat2);
	dlon = abs(lon1 - lon2);

	//Formula for great-circle distance
	a = pow(sin(dlat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2), 2);
	c = 2 * atan2( sqrt(a), sqrt(1 - a) );
	diameter = R * c;

	return diameter;
}