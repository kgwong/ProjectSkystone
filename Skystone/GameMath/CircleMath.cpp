#include "CircleMath.h"

#define PI 3.14159265359

double toRadians(double degrees)
{
	return degrees * PI / 180;
}

double toDegrees(double radians)
{
	return radians * 180 / PI;
}