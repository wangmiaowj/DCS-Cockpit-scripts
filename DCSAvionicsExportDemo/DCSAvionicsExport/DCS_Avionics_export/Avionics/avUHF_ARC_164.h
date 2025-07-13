#pragma once
#include <stdio.h>
#include "../Maths.h"
#include "../ED/CockpitAPI_Declare.h"
#include "../Table.h"
#include "avSimpleElectricSystem.h"

class avUHF_ARC_164 {
public:
	avUHF_ARC_164(EDPARAM& cockpitApi, avSimpleElectricSystem& elec);
	//Initialization
	void init(int deviceId);
	void pushTalk();
	int getFreq();
	void setFreq(int freq);
	void setVolume(float volume);
	inline const bool is_frequency_in_range(int freq)
	{
		return (freq >= 225E6 && freq < 399.975E6);
	}
	void set_preset_channel(unsigned int channel);

private:
	enum paramName {
		UHF_isActiveMode,
		UHF_getKnobsFrequencyMHz,
		UHF_getKnobsFrequencyKHz,
		UHF_getNetAddress,
		UHF_indicationOff,
		UHF_getBearing,
		UHF_getAlternateFrequency,
		UHF_isAlternateFreqStatus,
		UHF_isPresetChannelMode
	};
	EDPARAM& m_cockpitApi;
	avSimpleElectricSystem& m_elec;
	//std::map<int, EdParam>params;
};