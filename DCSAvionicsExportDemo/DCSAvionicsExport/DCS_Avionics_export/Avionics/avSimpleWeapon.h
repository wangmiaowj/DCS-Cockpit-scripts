#pragma once
#include <stdio.h>
#include "../Table.h"
#include "../Input.h"
#include "../Maths.h"
#include "../ED/CockpitAPI_Declare.h"
#include "../Avionics/avSimpleElectricSystem.h"
#include "weapons/Ammunition/Include/ammunition_laser_homing.h"

class avSimpleWeapon
{
public:
	avSimpleWeapon(EDPARAM& _edParam, avSimpleElectricSystem& _elect) :
		cockpitApi(_edParam),
		elect(_elect),
		laserHoming(new wAmmunitionLaserHoming())
	{

	}
	void init(int deviceId)
	{
		cockpitApi.WEAPON = deviceId;
		cockpitApi.initDevice(deviceId);
	}
	void setLaserCode(unsigned int laserCode)
	{
		laserHoming->setLaserCode(laserCode);
	}
private:
	EDPARAM& cockpitApi;
	wAmmunitionLaserHoming* laserHoming;
	avSimpleElectricSystem& elect;
};