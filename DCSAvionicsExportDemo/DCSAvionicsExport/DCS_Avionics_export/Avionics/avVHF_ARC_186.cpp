#include "avVHF_ARC_186.h"
avVHF_ARC_186::avVHF_ARC_186(EDPARAM& edParam, avSimpleElectricSystem& elec) :
	m_cockpitApi(edParam),
	m_elec(elec)
{

}

void avVHF_ARC_186::init(int deviceId,bool fm) {
	if (fm)
	{
		m_cockpitApi.VHF_FM_RADIO = deviceId;
		m_cockpitApi.initDevice(deviceId);
	}
	else
	{
		m_cockpitApi.VHF_AM_RADIO = deviceId;
		m_cockpitApi.initDevice(deviceId);
	}
	m_cockpitApi.VHF_connect_electric(deviceId);
}

void avVHF_ARC_186::pushTalk()
{
	m_cockpitApi.VHF_intercom_setAsCurrent(fm ? 2 : 1);
	m_cockpitApi.intercom_pushToTalk(true);
}

int avVHF_ARC_186::getFreq()
{
	return m_cockpitApi.VHF_getKnobsFrequency(fm ? 2 : 1);
}
void avVHF_ARC_186::setFreq(int freq)
{
	m_cockpitApi.VHF_set_knobs_frequency(freq, fm ? 2 : 1);
}
bool avVHF_ARC_186::isFM()
{
	return fm;
}
void avVHF_ARC_186::setAM()
{
	fm = false;
}
void avVHF_ARC_186::setFM()
{
	fm = true;
}
void avVHF_ARC_186::setVolume(float volume)
{
	m_cockpitApi.VHF_setVolume(volume);
}
