#include "avSimpleElectricSystem.h"

avSimpleElectricSystem::avSimpleElectricSystem
(
	EDPARAM& edParam
) :
	cockpitAPI(edParam)
{
	
}

void avSimpleElectricSystem::init(int deviceId)
{
	cockpitAPI.ELECTRIC_SYSTEM = deviceId;
	cockpitAPI.initDevice(deviceId);
}

double avSimpleElectricSystem::getAC1Voltage()
{
	if (acWire == nullptr)
	{
		return 0.0;
	}
	return *((double*)((intptr_t)acWire + 0x138));
}
double avSimpleElectricSystem::getAC2Voltage()
{
	if (acWire == nullptr)
	{
		return 0.0;
	}
	return *((double*)((intptr_t)acWire + 0x2a8));
}
double avSimpleElectricSystem::getDC1Voltage()
{
	if (dcWire == nullptr)
	{
		return 0.0;
	}
	return *((double*)((intptr_t)dcWire + 0x138));
}
double avSimpleElectricSystem::getDC2Voltage()
{
	if (dcWire == nullptr)
	{
		return 0.0;
	}
	double ac = std::max(getAC1Voltage(), getAC2Voltage());
	return (*((double*)((intptr_t)dcWire + 0x2A8))) * (ac / 115.0);
}
const bool avSimpleElectricSystem::isAC1()
{
	return getAC1Voltage() >= 115.0;
}
const bool avSimpleElectricSystem::isAC2()
{
	return getAC2Voltage() >= 115.0;
}
const bool avSimpleElectricSystem::isDC()
{
	return getDC1Voltage() >= 28.0 || getDC2Voltage() >= 28.0;
}
const bool avSimpleElectricSystem::isAC()
{
	return isAC1() || isAC2();
}