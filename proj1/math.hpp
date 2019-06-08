//Code made by Aljon Viray, ID: 86285526
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#ifndef MATH_HPP
#define MATH_HPP


float degreesToRadians(float degrees);

float directionConverter(float value, std::string direction);

float calculateDistance(float lat1, float lat2, float lon1, float lon2);

#endif // MATH_HPP