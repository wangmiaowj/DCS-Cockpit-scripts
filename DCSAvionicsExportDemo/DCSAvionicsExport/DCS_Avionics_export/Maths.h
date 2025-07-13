#pragma once
#include <math.h>
#include "Vec3.h"
#include <algorithm>
//=========================================================================//
//
//		FILE NAME	: Maths.h
//		AUTHOR		: Joshua Nelson & A4-Comunity-Team
//		Copyright	: Joshua Nelson & A4-Comunity-Team
//		DATE		: May 2020
//
//		DESCRIPTION	: Makes the life easier in regards of converting
//					  
//					  
//================================ Includes ===============================//
//=========================================================================//

#undef max
#undef min

//f¨¹r die Berechnungen der Airframe.h
static inline double toDegrees(double radians)
{
	return radians * 180.0 / 3.14159;
}

static inline double toRad(double degrees)
{
	return degrees * 3.14159 / 180.0;
}

static inline double clamp(double value, double min, double max)
{
	return std::max(std::min(value, max), min);
}

static inline double LoopPlayAnimal(double inputVal, double add, double minVal, double maxVal)
{
	double result = inputVal + add;
	double range = maxVal - minVal;
	if (result > maxVal || result < minVal)
	{
		double tmp = result / range;
		if (tmp < 0)
		{
			result = minVal + result - ceil(tmp) * range;
		}
		else
		{
			result = minVal + result - floor(tmp) * range;
		}
	}
	return result;
}