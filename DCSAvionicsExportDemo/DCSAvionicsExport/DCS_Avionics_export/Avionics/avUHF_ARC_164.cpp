#include "avUHF_ARC_164.h"
avUHF_ARC_164::avUHF_ARC_164(EDPARAM& edParam, avSimpleElectricSystem& elec) :
	m_cockpitApi(edParam),
	m_elec(elec)
{
	
}

void avUHF_ARC_164::init(int deviceId) {
	m_cockpitApi.UHF_RADIO = deviceId;
	m_cockpitApi.initDevice(deviceId);
	m_cockpitApi.UHF_connect_electric();
}

void avUHF_ARC_164::pushTalk()
{
	m_cockpitApi.UHF_intercom_setAsCurrent();
	m_cockpitApi.intercom_pushToTalk(true);
}

int avUHF_ARC_164::getFreq()
{
	return m_cockpitApi.UHF_getKnobsFrequency();
}
void avUHF_ARC_164::setFreq(int freq)
{
	m_cockpitApi.UHF_set_knobs_frequency(freq);
}
void avUHF_ARC_164::setVolume(float volume)
{
	m_cockpitApi.UHF_setVolume(volume);
}
void avUHF_ARC_164::set_preset_channel(unsigned int channel)
{
	try
	{
		m_cockpitApi.UHF_set_preset_channel(channel);
	}
	catch (const MyException& e)
	{
		e.printMsg();
	}
}