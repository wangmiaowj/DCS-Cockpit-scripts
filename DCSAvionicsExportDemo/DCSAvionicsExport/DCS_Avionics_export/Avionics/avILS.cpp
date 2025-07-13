#include "avILS.h"
avILS::avILS(EDPARAM& edParam, avSimpleElectricSystem& elec) :
	m_cockpitApi(edParam),
	m_elec(elec)
{
	
}

void avILS::init(int deviceId)
{
	m_cockpitApi.ILS = deviceId;
	m_cockpitApi.initDevice(deviceId);
	m_cockpitApi.ILS_connectElecPower();
}

void avILS::setFreq(double freq)
{
	int MHz = (int)floor(freq);
	int KHz = (int)((freq - MHz) * 1000);
	try
	{
		m_cockpitApi.ILS_setFrequencyMHz(MHz);
		m_cockpitApi.ILS_setFrequencyKHz(KHz);
	}
	catch (const MyException& e)
	{
		e.printMsg();
	}
}
double avILS::getLocalizerFreq()
{
	try
	{
		return m_cockpitApi.ILS_getLocalizerFrequency();
	}
	catch (const MyException& e)
	{
		e.printMsg();
	}
}
double avILS::getGlideslopeFrequency(double localizerFreq)
{
	try
	{
		return m_cockpitApi.ILS_getGlideslopeFrequency(localizerFreq);
	}
	catch (const MyException& e)
	{
		e.printMsg();
	}
}

bool avILS::isLocalizerValid()
{
	return m_cockpitApi.ILS_isLocalizerValid();
}

bool avILS::isGlideslopeValid()
{
	return m_cockpitApi.ILS_isGlideslopeValid();
}

double avILS::getLocalizerDeviation()
{
	return m_cockpitApi.ILS_getLocalizerDeviation();
}

double avILS::getGlideslopeDeviation()
{
	return m_cockpitApi.ILS_getGlideslopeDeviation();
}

bool avILS::isOuterMarkerSignal()
{
	return m_cockpitApi.ILS_isOuterMarkerSignal();
}

bool avILS::isMiddleMarkerSignal()
{
	return m_cockpitApi.ILS_isMiddleMarkerSignal();
}

bool avILS::isInnerMarkerSignal()
{
	return m_cockpitApi.ILS_isInnerMarkerSignal();
}

bool avILS::isMarkerBeacon()
{
	return m_cockpitApi.ILS_isMarkerBeacon();
}
