#pragma once
#include "ccParametersAPI.h"
#include "string"
#include <map>
#include "../MyException.h"

class EDPARAM
{
public:
	EDPARAM()
	{
		ed_param_api = ed_get_cockpit_param_api();
		void*** context = (void***)((intptr_t)ed_param_api.device_array + 0x30);
		if (!context)
		{
			printf("context not exit\n");
			return;
		}
		printf("Context: %p\n", context);
		deviceTable = *context;
		if (!deviceTable) {
			printf("deviceTable not exit");
			return;
		}
		printf("Device Table: %p\n", deviceTable);
		devicesClass[ELECTRIC_SYSTEM] = nullptr;
		devicesClass[UHF_RADIO] = nullptr;
		devicesClass[VHF_AM_RADIO] = nullptr;
		devicesClass[VHF_FM_RADIO] = nullptr;
		devicesClass[ILS] = nullptr;
		devicesClass[CLOCK] = nullptr;
		devicesClass[INTERCOM] = nullptr;
	}
	~EDPARAM()
	{
		delete tacanPtr;
		tacanPtr = nullptr;
	}
	cockpit_param_api ed_param_api;
	int ELECTRIC_SYSTEM = -1;
	int UHF_RADIO = -1;
	int INTERCOM = -1;
	int VHF_AM_RADIO = -1;
	int VHF_FM_RADIO = -1;
	int ILS = -1;
	int CLOCK = -1;
	int WEAPON = -1;
	void* initDevice(int idx, const char* deviceName)
	{
		void* device = deviceTable[idx];
		if (!device) {
			printf("%s not exit\n", deviceName);
			return nullptr;
		}
		printf("%s: %p\n", deviceName, device);
		return device;
	}
	void initDevice(int idx)
	{
		if (idx > 0)
		{
			void* device = deviceTable[idx];
			if (!device) {
				devicesClass[idx] = nullptr;
			}
			else
			{
				devicesClass[idx] = device;
			}
		}
	}
	
	void* getParamHandle(const char* name)
	{
		return ed_param_api.get_parameter_handle(name);
	}

	void setParamNumber(void* handle, double value)
	{
		ed_param_api.update_parameter_with_number(handle, value);
	}

	void setParamString(void* handle, const char* string)
	{
		ed_param_api.update_parameter_with_string(handle, string);
	}

	double getParamNumber(void* handle)
	{
		double res = 0;
		ed_param_api.parameter_value_to_number(handle, res, false);
		return res;
	}

	const char* getParamString(void* handle, unsigned buffer_size)
	{
		char buffer[256];
		ed_param_api.parameter_value_to_string(handle, buffer, 256);
		return &buffer[0];
	}

	int compareParams(void* handle1, void* handle2)
	{
		return ed_param_api.compare_parameters(handle1, handle2);
	}

	/*inline int getWeaponCount(int stationIdx)
	{
		if (devicesClass[WEAPON_SYSTEM] == nullptr)
		{
			return 0;
		}
		return ed_param_api.pfn_get_weapon_count(devicesClass[WEAPON_SYSTEM], 1);
	}*/
	inline void* getDCbus(int num = 1)
	{
		if (devicesClass[ELECTRIC_SYSTEM] == nullptr)
		{
			throw new MyException("电力系统没有初始化");
		}
		return ed_param_api.pfn_get_dc_wire(devicesClass[ELECTRIC_SYSTEM], num);
	}
	inline void* getACbus(int num = 1)
	{
		if (devicesClass[ELECTRIC_SYSTEM] == nullptr)
		{
			throw new MyException("电力系统没有初始化");
		}
		return ed_param_api.pfn_get_ac_wire(devicesClass[ELECTRIC_SYSTEM], num);
	}
	inline void switchBattery(bool onOff)
	{
		if (devicesClass[ELECTRIC_SYSTEM] == nullptr)
		{
			throw new MyException("电力系统未初始化");
		}
		ed_param_api.pfn_switch_battery(devicesClass[ELECTRIC_SYSTEM], onOff);
	}
	inline void switchGenerator(bool onOff, int num = 1)
	{
		if (devicesClass[ELECTRIC_SYSTEM] == nullptr)
		{
			throw new MyException("电力系统未初始化");
		}
		ed_param_api.pfn_switch_generator(devicesClass[ELECTRIC_SYSTEM], onOff, num);
	}
	inline void ILS_connectElecPower()
	{
		if (devicesClass[ILS] == nullptr)
		{
			throw new MyException("ILS没有初始化");
		}
		void* dc = getDCbus();
		if (dc == nullptr)
		{
			throw new MyException("dcBus为空");
		}
		void* ac = getACbus();
		if (ac == nullptr)
		{
			throw new MyException("acBus为空");
		}
		ed_param_api.pfn_ils_connect_electric(devicesClass[ILS], dc, ac);
		printf("ILS connected!!!\n");
	}
	inline void ILS_setElecPower(bool onOff)
	{
		if (devicesClass[ILS] == nullptr)
		{
			throw new MyException("ILS没有初始化");
		}
		ed_param_api.pfn_ils_set_elec_power(devicesClass[ILS], onOff);
	}
	inline bool ILS_isLocalizerValid()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return false;
		}
		return ed_param_api.pfn_ils_is_localizer_valid(devicesClass[ILS]);
	}
	inline bool ILS_isGlideslopeValid()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return false;
		}
		return ed_param_api.pfn_ils_is_glideslope_valid(devicesClass[ILS]);
	}
	inline double ILS_getLocalizerDeviation()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return 0.0;
		}
		return ed_param_api.pfn_ils_get_localizer_deviation(devicesClass[ILS]);
	}
	inline double ILS_getGlideslopeDeviation()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return 0.0;
		}
		return ed_param_api.pfn_ils_get_glideslope_deviation(devicesClass[ILS]);
	}
	inline bool ILS_isMarkerBeacon()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return false;
		}
		return ed_param_api.pfn_ils_is_marker_beacon(devicesClass[ILS]);
	}
	inline bool ILS_isOuterMarkerSignal()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return false;
		}
		return ed_param_api.pfn_ils_is_outer_marker_signal(devicesClass[ILS]);
	}
	inline bool ILS_isMiddleMarkerSignal()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return false;
		}
		return ed_param_api.pfn_ils_is_middle_marker_signal(devicesClass[ILS]);
	}
	inline bool ILS_isInnerMarkerSignal()
	{
		if (devicesClass[ILS] == nullptr)
		{
			return false;
		}
		return ed_param_api.pfn_ils_is_inner_marker_signal(devicesClass[ILS]);
	}
	inline void ILS_setFrequencyMHz(int freq)
	{
		if (devicesClass[ILS] == nullptr)
		{
			throw new MyException("ILS没有初始化");
		}
		ed_param_api.pfn_ils_set_MHz(devicesClass[ILS], freq);
	}
	inline void ILS_setFrequencyKHz(int freq)
	{
		if (devicesClass[ILS] == nullptr)
		{
			throw new MyException("ILS没有初始化");
		}
		ed_param_api.pfn_ils_set_KHz(devicesClass[ILS], freq);
	}
	inline double ILS_getLocalizerFrequency()
	{
		if (devicesClass[ILS] == nullptr)
		{
			throw new MyException("ILS没有初始化");
		}
		return ed_param_api.pfn_ils_getLocalizerFrequency(devicesClass[ILS]);
	}
	inline double ILS_getGlideslopeFrequency(double localizerFreq)
	{
		if (devicesClass[ILS] == nullptr)
		{
			throw new MyException("ILS没有初始化");
		}
		return ed_param_api.pfn_ils_getGlideslopeFrequency(devicesClass[ILS], localizerFreq);
	}
	inline bool UHF_displayTesting()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_display_testing(devicesClass[UHF_RADIO]);
	}
	inline bool UHF_isActiveMode()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_is_active_mode(devicesClass[UHF_RADIO]);
	}
	inline int UHF_getKnobsFrequencyMHz()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_get_knobs_frequency_MHz(devicesClass[UHF_RADIO]);
	}
	inline int UHF_getKnobsFrequencyKHz()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_get_knobs_frequency_KHz(devicesClass[UHF_RADIO]);
	}
	inline int UHF_getNetAddress()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_get_net_address(devicesClass[UHF_RADIO]);
	}
	inline bool UHF_indicationOff()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_indication_off(devicesClass[UHF_RADIO]);
	}
	inline float UHF_getBearing()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_get_bearing(devicesClass[UHF_RADIO]);
	}
	inline int UHF_getAlternateFrequency()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_get_alternate_frequency(devicesClass[UHF_RADIO]);
	}
	inline bool UFH_isAlternateFreqStatus()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_is_alternate_freq_status(devicesClass[UHF_RADIO]);
	}
	inline bool UHF_isPresetChannelMode()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		return ed_param_api.pfn_uhf_is_preset_channel_mode(devicesClass[UHF_RADIO]);
	}
	inline void UHF_set_preset_channel(unsigned int channel)
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		ed_param_api.pfn_uhf_set_preset_channel(devicesClass[UHF_RADIO], channel);
	}
	inline bool UHF_isAlternateFreqStatus()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有实例化");
		}
		ed_param_api.pfn_uhf_isAlternateFreqStatus(devicesClass[UHF_RADIO]);
	}
	inline void VHF_setElecPower(bool onOff, int num = 1)
	{
		void* vuhfClass;
		if (num == 1)
		{
			vuhfClass = devicesClass[VHF_AM_RADIO];
		}
		else
		{
			vuhfClass = devicesClass[VHF_FM_RADIO];
		}
		if (vuhfClass == nullptr)
		{
			throw new MyException("VHF无线电没有初始化");
		}
		vuhfClass = (void*)((intptr_t)vuhfClass + 0xB8);//0xB8是baseRadio的偏移，这个函数是avBaseRadio的东西
		ed_param_api.pfn_set_elec_power(vuhfClass, onOff);
	}
	inline void UHF_setElecPower(bool onOff)
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF无线电没有初始化");
		}
		void* vuhfClass = (void*)((intptr_t)devicesClass[UHF_RADIO] + 0xB8);//0xB8是baseRadio的偏移，这个函数是avBaseRadio的东西
		ed_param_api.pfn_set_elec_power(vuhfClass, onOff);
	}
	inline void UHF_connect_electric()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有初始化");
		}
		void* wire = getDCbus();
		if (wire != nullptr)
		{
			ed_param_api.pfn_uhf_connect_electric(devicesClass[UHF_RADIO], wire);
		}
		else
		{
			throw new MyException("getDCbus无法获取直流电");
		}
	}
	inline void UHF_setVolume(float volume)
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有初始化");
		}
		ed_param_api.pfn_baseRadio_set_volume(devicesClass[UHF_RADIO], volume);
	}
	inline void VHF_setVolume(float volume)
	{
		if (devicesClass[VHF_AM_RADIO] == nullptr)
		{
			throw new MyException("VHF_AM没有初始化");
		}
		if (devicesClass[VHF_FM_RADIO] == nullptr)
		{
			throw new MyException("VHF_FM没有初始化");
		}
		ed_param_api.pfn_baseRadio_set_volume(devicesClass[VHF_AM_RADIO], volume);
		ed_param_api.pfn_baseRadio_set_volume(devicesClass[VHF_FM_RADIO], volume);
	}
	inline float UHF_getVolume()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有初始化");
		}
		return ed_param_api.pfn_baseRadio_get_volume(devicesClass[UHF_RADIO]);
	}
	inline float VHF_getVolume(int num = 1)
	{
		void* vhfClass;
		if (num == 1)
		{
			vhfClass = devicesClass[VHF_AM_RADIO];
		}
		else
		{
			vhfClass = devicesClass[VHF_FM_RADIO];
		}
		if (vhfClass == nullptr)
		{
			throw new MyException("VHF没有初始化");
		}
		return ed_param_api.pfn_baseRadio_get_volume(vhfClass);
	}
	inline void VHF_connect_electric(int deviceId)
	{
		void* wire = getDCbus();
		if (wire != nullptr)
		{
			ed_param_api.pfn_vhf_connect_electric(devicesClass[deviceId], wire);
		}
		else
		{
			throw new MyException("getDCbus无法获取直流电");
		}
	}
	inline int UHF_getKnobsFrequency()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			return 0;
		}
		return ed_param_api.pfn_uhf_get_knobs_frequency(devicesClass[UHF_RADIO]);
	}
	inline int VHF_getKnobsFrequency(int num = 1)
	{
		void* vhfClass;
		if (num == 1)
		{
			vhfClass = devicesClass[VHF_AM_RADIO];
		}
		else
		{
			vhfClass = devicesClass[VHF_FM_RADIO];
		}
		if (vhfClass == nullptr)
		{
			return 0;
		}
		return ed_param_api.pfn_vhf_get_knobs_frequency(vhfClass);
	}
	inline void* UHF_get_communicator()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			return nullptr;
		}
		return ed_param_api.pfn_get_communicator(devicesClass[UHF_RADIO]);
	}
	inline void* VHF_get_communicator(int num = 1)
	{
		void* vhfClass;
		if (num == 1)
		{
			vhfClass = devicesClass[VHF_AM_RADIO];
		}
		else
		{
			vhfClass = devicesClass[VHF_FM_RADIO];
		}
		if (vhfClass == nullptr)
		{
			return nullptr;
		}
		return ed_param_api.pfn_get_communicator(devicesClass[VHF_AM_RADIO]);
	}
	inline void UHF_set_knobs_frequency(int freq)
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有初始化");
		}
		ed_param_api.pfn_uhf_set_knobs_frequency(devicesClass[UHF_RADIO], freq);
	}
	inline void VHF_set_knobs_frequency(int freq, int num = 1)
	{
		void* vhfClass;
		if (num == 1)
		{
			vhfClass = devicesClass[VHF_AM_RADIO];
		}
		else
		{
			vhfClass = devicesClass[VHF_FM_RADIO];
		}
		if (vhfClass == nullptr)
		{
			throw new MyException("VHF没有初始化");
		}
		ed_param_api.pfn_vhf_set_knobs_frequency(vhfClass, freq);
		printf("VHF频率设置%d\n", freq);
	}
	inline void UHF_intercom_setAsCurrent()
	{
		void* comm = UHF_get_communicator();
		if (comm != nullptr)
		{
			ed_param_api.pfn_set_communicator_as_current(comm);
		}
		else
		{
			throw new MyException("UHF_get_communicator无法获取通讯器\n");
		}
	}
	inline void VHF_intercom_setAsCurrent(int num = 1)
	{
		void* comm = VHF_get_communicator(num);
		if (comm != nullptr)
		{
			ed_param_api.pfn_set_communicator_as_current(comm);
		}
		else
		{
			throw new MyException("VHF_get_communicator无法获取通讯器\n");
		}
	}
	inline void UHF_set_modulation(char* modulation)
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有初始化");
		}
		ed_param_api.pfn_baseRadio_set_modulation(devicesClass[UHF_RADIO], modulation);
	}
	inline char* UHF_get_modulation()
	{
		if (devicesClass[UHF_RADIO] == nullptr)
		{
			throw new MyException("UHF没有初始化");
		}
		return ed_param_api.pfn_baseRadio_get_modulation(devicesClass[UHF_RADIO]);
	}
	inline void intercom_pushToTalk(bool push)
	{
		if (devicesClass[INTERCOM] == nullptr)
		{
			throw new MyException("通讯器intercom没有初始化");
		}
		ed_param_api.pfn_push_to_talk(devicesClass[INTERCOM], push);
	}
	inline bool intercom_isOn()
	{
		if (devicesClass[INTERCOM] == nullptr)
		{
			throw new MyException("通讯器intercom没有初始化");
		}
		return ed_param_api.isOnIntercom(devicesClass[INTERCOM]);
	}

	inline double get_currtime_seconds()
	{
		if (devicesClass[CLOCK] == nullptr)
		{
			throw new MyException("时钟没有初始化");
		}
		return ed_param_api.pfn_a11Clock_get_currtime_seconds(devicesClass[CLOCK]);
	}
	inline double get_currtime()
	{
		if (devicesClass[CLOCK] == nullptr)
		{
			throw new MyException("时钟没有初始化");
		}
		return ed_param_api.pfn_mechanicClock_get_curretime(devicesClass[CLOCK]);
	}
	inline void clock_repair()
	{
		if (devicesClass[CLOCK] == nullptr)
		{
			throw new MyException("时钟没有初始化");
		}
		return ed_param_api.pfn_a11Clock_repair(devicesClass[CLOCK]);
	}
	inline bool clock_set_damage(unsigned Failure_ID, const bool can_be_rejected)
	{
		if (devicesClass[CLOCK] == nullptr)
		{
			throw new MyException("时钟没有初始化");
		}
		return ed_param_api.pfn_a11Clock_setDamage(devicesClass[CLOCK], Failure_ID, can_be_rejected);
	}
	inline void TACAN_Constructor()
	{
		tacanPtr = ed_param_api.pfn_TACAN_Constructor();
	}
	inline void TACAN_connectElec()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		void* dc = getDCbus();
		void* ac = getACbus();
		ed_param_api.pfn_TACAN_connectElectric(tacanPtr, dc, ac);
	}
	inline int TACAN_getChannel()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getChannel(tacanPtr);
	}
	inline bool TACAN_getElecPower()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getElecPower(tacanPtr);
	}
	inline double TACAN_getMagneticBearing()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getMagneticBearing(tacanPtr);
	}
	inline int TACAN_getMode()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getMode(tacanPtr);
	}
	inline int TACAN_getModeXY()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getModeXY(tacanPtr);
	}
	inline double TACAN_getRange()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getRange(tacanPtr);
	}
	inline double TACAN_getReceiverFrequency()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getReceiverFrequency(tacanPtr);
	}
	inline double TACAN_getStowedBearing()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getStowedBearing(tacanPtr);
	}
	inline double TACAN_getTransmitterFrequency()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_getTransmitterFrequency(tacanPtr);
	}
	inline bool TACAN_isBearingValid()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_isBearingValid(tacanPtr);
	}
	inline bool TACAN_isRangeValid()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		return ed_param_api.pfn_TACAN_isRangeValid(tacanPtr);
	}
	inline void TACAN_onChannelChanged()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_onChannelChanged(tacanPtr);
	}
	inline void TACAN_post_init()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_post_init(tacanPtr);
	}
	inline void TACAN_release()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_release(tacanPtr);
	}
	inline void TACAN_repair()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_repairs(tacanPtr);
	}
	inline void TACAN_setChannel(int channel)
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_setChannel(tacanPtr, channel);
	}
	inline void TACAN_setChannelXYMode(int xyMode)
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_setChannelXYMode(tacanPtr, xyMode);
	}
	inline void TACAN_setMode(int mode)
	{
		ed_param_api.pfn_TACAN_setMode(tacanPtr, mode);
	}
	inline void TACAN_setReceiversOnOff(bool onOff)
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_setReceiversOnOff(tacanPtr, onOff);
	}
	inline void TACAN_setVolume(float volume)
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_setVolume(tacanPtr, volume);
	}
	inline void TACAN_setDamage(unsigned Failure_ID, const bool can_be_rejected)
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_setDamage(tacanPtr, Failure_ID, can_be_rejected);
	}
	inline void TACAN_switchPower(bool onOff)
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_switch_power(tacanPtr, onOff);
	}
	inline void TACAN_update()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_update(tacanPtr);
	}
	inline void TACAN_updateRangeBearing()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_updateRangeBearing(tacanPtr);
	}
	inline void TACAN_updateWarmup()
	{
		if (tacanPtr == nullptr)
		{
			throw new MyException("塔康设备未实例化");
		}
		ed_param_api.pfn_TACAN_updateWarmup(tacanPtr);
	}
	inline void performClickAction(int deviceId, int command, float value, bool echo = false)
	{
		if (deviceId < 1)
		{
			return;
		}
		void* Class = devicesClass[deviceId];
		if (Class == nullptr)
		{
			throw new MyException("设备id:" + std::to_string(deviceId) + " 未初始化");
		}
		if (command < 3001 || command>4000)
		{
			return;
		}
		ed_param_api.pfn_performClickAction(Class, command, value, echo);
	}
	inline void* getDevice(int deviceId)
	{
		return devicesClass[deviceId];
	}
private:
	std::map<int, void*>devicesClass;
	void** deviceTable;
	void* tacanPtr = nullptr;
};

