#pragma once
#include <stdio.h>
#include "../Maths.h"
#include "../ED/CockpitAPI_Declare.h"
#include "avSimpleElectricSystem.h"

class avVHF_ARC_186 {
public:
	avVHF_ARC_186(EDPARAM& cockpitApi, avSimpleElectricSystem& elec);
	//Initialization
	void init(int deviceId,bool fm);
	void pushTalk();
	int getFreq();
	void setFreq(int freq);
	bool isFM();
	void setFM();
	void setAM();
	void setVolume(float volume);
	inline const bool is_frequency_in_range(int freq)
	{
		if (fm)
		{
			return (freq >= 30E6 && freq < 108E6);
		}
		return (freq >= 116E6 && freq < 151.95E6);
	}
private:
	EDPARAM& m_cockpitApi;
	avSimpleElectricSystem& m_elec;
	bool fm = false;
};