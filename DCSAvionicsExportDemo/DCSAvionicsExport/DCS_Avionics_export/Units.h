#pragma once

//=========================================================================//
//
//		FILE NAME	: Units.h
//		AUTHOR		: Joshua Nelson
//		Copyright	: Joshua Nelson
//		DATE		: May 2020
//
//		DESCRIPTION	: Makes converting more easy...  
//					  
//					  
//================================ Includes ===============================//
//=========================================================================//

inline long double operator"" _deg(long double x)
{
	return x * 0.01745329252;
}

inline long double operator"" _nauticalMile(long double x)
{
	return x * 1852.0;
}
