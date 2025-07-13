#pragma once
#include <stdio.h>
#include "../Table.h"
#include "../Maths.h"
#include "../ED/CockpitAPI_Declare.h"

class avSimpleElectricSystem
{
public:
	avSimpleElectricSystem(EDPARAM& edParam);

	//Initialization
	//----------Functions Engine 1-----------
	const bool isDC();
	const bool isAC();
	const bool isAC1();
	const bool isAC2();
	void init(int deviceId);
	double getAC1Voltage();
	double getAC2Voltage();
	double getDC1Voltage();
	double getDC2Voltage();

private:
	EDPARAM& cockpitAPI;
	//-------------Engine Values/Commands Engine1----------------------------
	void* acWire = nullptr;
	void* dcWire = nullptr;
};