#pragma once
#include <stdio.h>
#include "../Table.h"
#include "../Maths.h"
#include "../ED/CockpitAPI_Declare.h"
#include "../Avionics/avSimpleElectricSystem.h"
class avILS
{
public:
	avILS(EDPARAM& edParam, avSimpleElectricSystem& elec);
	void init(int deviceId);
	void setFreq(double freq);
	double getLocalizerFreq();
	double getGlideslopeFrequency(double localizerFreq);
	bool isLocalizerValid();
	bool isGlideslopeValid();
	double getLocalizerDeviation();
	double getGlideslopeDeviation();
	bool isOuterMarkerSignal();
	bool isMiddleMarkerSignal();
	bool isInnerMarkerSignal();
	bool isMarkerBeacon();

	inline void enable()
	{
		working = true;
	}
	inline void disable()
	{
		working = false;
	}
private:
	EDPARAM& m_cockpitApi;
	avSimpleElectricSystem& m_elec;
	bool working = false;

};