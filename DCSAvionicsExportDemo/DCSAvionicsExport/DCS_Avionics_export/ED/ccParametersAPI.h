#pragma once
#include <windows.h>

//params handling
typedef void* (*PFN_ED_COCKPIT_GET_PARAMETER_HANDLE)  (const char* name);
typedef void   (*PFN_ED_COCKPIT_UPDATE_PARAMETER_WITH_STRING)  (void* handle, const char* string_value);
typedef void   (*PFN_ED_COCKPIT_UPDATE_PARAMETER_WITH_NUMBER)  (void* handle, double number_value);
typedef bool   (*PFN_ED_COCKPIT_PARAMETER_VALUE_TO_NUMBER)  (const void* handle, double& res, bool interpolated);
typedef bool   (*PFN_ED_COCKPIT_PARAMETER_VALUE_TO_STRING)  (const void* handle, char* buffer, unsigned buffer_size);
typedef int    (*PFN_ED_COCKPIT_COMPARE_PARAMETERS)  (void* handle_1, void* handle_2);
//typedef void   (cockpit::avBaseRadio::*MemberFncBool)		   (bool value);
typedef void   (*RADIO_POWER_FUNC)							   (void* value);
typedef bool  (*GET_RADIO_POWER_FUNC)							(void*);
typedef bool  (*GET_SOMETHING)									(void);
typedef int   (*GET_SOMETHING_INT)								(void);
typedef void* (*PFN_ED_COCKPIT_SET_ACTION_DIGITAL)(int value);
typedef void  (*PFN_CONNECT_ELECTRIC)(void*, void*);
typedef void  (*PFN_CONNECT_BOTH_ELECTRIC)(void*, void*, void*);
typedef void  (*PFN_SET_ELEC_POWER)(void*, bool);
typedef void* (*PFN_GET_COMMUNICATOR)(void*);
typedef void  (*PFN_SET_COMMUNICATOR_AS_CURRENT)(void*);
typedef void* (*PFN_GET_WIRE)(void*, int);
typedef int   (*PFN_GET_FREQ)(void*);
typedef void  (*PFN_PUSH_TO_TALK)(void*, bool);
typedef void  (*PFN_TRY_SET_COMMUNICATOR)(void*, unsigned int);
typedef bool  (*PFN_IS_ON)(void*);
typedef void  (*PFN_SET_ON)(void*, bool);
typedef void* (*PFN_GET_HUMAN_COMMUNICATOR)(void);
typedef void  (*PFN_OPEN_RADIO_MENU)(void*);
typedef double (*PFN_GET_DOUBLE)(void*);
typedef double (*PFN_GET_DOUBLE2)(void*, double);
typedef void  (*PFN_SET_FLOAT)(void*, float);
typedef float (*PFN_GET_FLOAT)(void*);
typedef void  (*PFN_SET_INT)(void*, int);
typedef void  (*PFN_SET_UNSIGNED_INT)(void*, unsigned int);
typedef void  (*PFN_SET_DOUBLE)(void*, double);
typedef int (*PFN_GET_WEAPON_COUNT)(void*, int);
typedef void (*PFN_SWITCH_BATTERY)(void*, bool);
typedef void (*PFN_SWITCH_GENERATOR)(void*, bool, int);
typedef void (*PFN_PERFORM_CLICK_ACTION)(void*, int, float, bool);
typedef void (*PFN_SET_CHAR)(void*, char*);
typedef char* (*PFN_GET_CHAR)(void*);
typedef void (*PFN_LAUNCH_STATION)(void*, int, int);
typedef void (*PFN_REPAIRS)(void*);
typedef bool (*PFN_SET_DAMAGE)(void*, unsigned, bool);
typedef void* (*PFN_INITIALIZER)(void);
typedef void (*PFN_VOID_VOID)(void*);

struct cockpit_param_api
{
	PFN_ED_COCKPIT_GET_PARAMETER_HANDLE             get_parameter_handle;
	PFN_ED_COCKPIT_UPDATE_PARAMETER_WITH_STRING     update_parameter_with_string;
	PFN_ED_COCKPIT_UPDATE_PARAMETER_WITH_NUMBER     update_parameter_with_number;
	PFN_ED_COCKPIT_PARAMETER_VALUE_TO_NUMBER        parameter_value_to_number;
	PFN_ED_COCKPIT_PARAMETER_VALUE_TO_STRING        parameter_value_to_string;
	PFN_ED_COCKPIT_COMPARE_PARAMETERS               compare_parameters;
	RADIO_POWER_FUNC								 setRadioPowerFncPtr;
	GET_RADIO_POWER_FUNC								 getRadioPowerFncPtr;
	GET_RADIO_POWER_FUNC								 switchRadioPowerFncPtr;
	PFN_IS_ON	isOnIntercom;
	GET_SOMETHING_INT getGunShells;
	PFN_ED_COCKPIT_SET_ACTION_DIGITAL				 pfn_ed_cockpit_set_action_digital;
	PFN_SET_ELEC_POWER                               pfn_set_elec_power;
	PFN_GET_COMMUNICATOR							 pfn_get_communicator;
	PFN_SET_COMMUNICATOR_AS_CURRENT                  pfn_set_communicator_as_current;
	PFN_GET_WIRE									 pfn_get_dc_wire;
	PFN_GET_WIRE									 pfn_get_ac_wire;
	PFN_GET_FREQ pfn_get_freq;
	PFN_PUSH_TO_TALK pfn_push_to_talk;
	PFN_TRY_SET_COMMUNICATOR pfn_try_set_communicator;
	PFN_IS_ON pfn_is_communicator_on;
	PFN_IS_ON pfn_is_transmitter_on;
	PFN_IS_ON pfn_is_receiver_on;
	PFN_SET_ON pfn_set_communicator_on;
	PFN_SET_ON pfn_set_transmitter_on;
	PFN_SET_ON pfn_set_receiver_on;
	PFN_SET_ON pfn_send_net_message;
	PFN_GET_HUMAN_COMMUNICATOR pfn_get_human_communicator;
	PFN_SET_DOUBLE pfn_set_radius;

	PFN_GET_WEAPON_COUNT pfn_get_weapon_count;
	PFN_SET_ON pfn_avSimpleWeaponSystem_launch;
	PFN_SET_ON pfn_avSimpleWeaponSystem_onPick;
	PFN_LAUNCH_STATION pfn_avSimpleWeaponSystem_launch_station;

	PFN_SWITCH_BATTERY pfn_switch_battery;
	PFN_SWITCH_GENERATOR pfn_switch_generator;

	PFN_CONNECT_BOTH_ELECTRIC pfn_ils_connect_electric;
	PFN_IS_ON pfn_ils_is_on;
	PFN_SET_INT pfn_ils_set_MHz;
	PFN_SET_INT pfn_ils_set_KHz;
	PFN_GET_DOUBLE pfn_ils_getLocalizerFrequency;
	PFN_GET_DOUBLE2 pfn_ils_getGlideslopeFrequency;
	PFN_SET_ON pfn_ils_set_elec_power;
	PFN_IS_ON pfn_ils_is_localizer_valid;
	PFN_IS_ON pfn_ils_is_glideslope_valid;
	PFN_GET_DOUBLE pfn_ils_get_localizer_deviation;
	PFN_GET_DOUBLE pfn_ils_get_glideslope_deviation;
	PFN_IS_ON pfn_ils_is_marker_beacon;
	PFN_IS_ON pfn_ils_is_outer_marker_signal;
	PFN_IS_ON pfn_ils_is_middle_marker_signal;
	PFN_IS_ON pfn_ils_is_inner_marker_signal;

	PFN_SET_CHAR pfn_baseRadio_set_modulation;
	PFN_GET_CHAR pfn_baseRadio_get_modulation;
	PFN_SET_FLOAT pfn_baseRadio_set_volume;
	PFN_GET_FLOAT pfn_baseRadio_get_volume;
	PFN_SET_DAMAGE pfn_baseRadio_set_damage;

	PFN_IS_ON pfn_uhf_display_testing;
	PFN_IS_ON pfn_uhf_is_active_mode;
	PFN_GET_FREQ pfn_uhf_get_knobs_frequency_MHz;
	PFN_GET_FREQ pfn_uhf_get_knobs_frequency_KHz;
	PFN_GET_FREQ pfn_uhf_get_net_address;
	PFN_IS_ON pfn_uhf_indication_off;
	PFN_GET_FLOAT pfn_uhf_get_bearing;
	PFN_GET_FREQ pfn_uhf_get_alternate_frequency;
	PFN_IS_ON pfn_uhf_is_alternate_freq_status;
	PFN_IS_ON pfn_uhf_is_preset_channel_mode;
	PFN_SET_INT pfn_uhf_set_knobs_frequency;
	PFN_CONNECT_ELECTRIC pfn_uhf_connect_electric;
	PFN_GET_FREQ pfn_uhf_get_knobs_frequency;
	PFN_SET_UNSIGNED_INT pfn_uhf_set_preset_channel;
	PFN_IS_ON pfn_uhf_isAlternateFreqStatus;

	PFN_CONNECT_ELECTRIC pfn_vhf_connect_electric;
	PFN_SET_INT pfn_vhf_set_knobs_frequency;
	PFN_GET_FREQ pfn_vhf_get_knobs_frequency;
	PFN_SET_CHAR pfn_vhf_set_modulation;

	PFN_GET_DOUBLE pfn_mechanicClock_get_curretime;
	PFN_GET_DOUBLE pfn_a11Clock_get_currtime_seconds;
	PFN_REPAIRS pfn_a11Clock_repair;
	PFN_SET_DAMAGE pfn_a11Clock_setDamage;


	PFN_PERFORM_CLICK_ACTION pfn_performClickAction;
	//PFN_CREATE_LUA_VM pfn_create_lua_vm;
	//PFN_DESTROY_LUA_VM pfn_destroy_lua_vm;

	PFN_INITIALIZER pfn_TACAN_Constructor;
	PFN_CONNECT_BOTH_ELECTRIC pfn_TACAN_connectElectric;
	PFN_GET_FREQ pfn_TACAN_getChannel;
	PFN_IS_ON pfn_TACAN_getElecPower;
	PFN_GET_DOUBLE pfn_TACAN_getMagneticBearing;
	PFN_GET_FREQ pfn_TACAN_getMode;
	PFN_GET_FREQ pfn_TACAN_getModeXY;
	PFN_GET_DOUBLE pfn_TACAN_getRange;
	PFN_GET_DOUBLE pfn_TACAN_getReceiverFrequency;
	PFN_GET_DOUBLE pfn_TACAN_getStowedBearing;
	PFN_GET_DOUBLE pfn_TACAN_getTransmitterFrequency;
	PFN_IS_ON pfn_TACAN_isBearingValid;
	PFN_IS_ON pfn_TACAN_isRangeValid;
	PFN_VOID_VOID pfn_TACAN_onChannelChanged;
	PFN_VOID_VOID pfn_TACAN_post_init;
	PFN_VOID_VOID pfn_TACAN_release;
	PFN_REPAIRS pfn_TACAN_repairs;
	PFN_SET_INT pfn_TACAN_setChannel;
	PFN_SET_INT pfn_TACAN_setChannelXYMode;
	PFN_SET_INT pfn_TACAN_setMode;
	PFN_SET_ON pfn_TACAN_setReceiversOnOff;
	PFN_SET_FLOAT pfn_TACAN_setVolume;
	PFN_SET_DAMAGE pfn_TACAN_setDamage;
	PFN_SET_ON pfn_TACAN_switch_power;
	PFN_VOID_VOID pfn_TACAN_update;
	PFN_VOID_VOID pfn_TACAN_updateRangeBearing;
	PFN_VOID_VOID pfn_TACAN_updateWarmup;
	void** device_array;
};

inline cockpit_param_api  ed_get_cockpit_param_api()
{
	HMODULE cockpit_dll = GetModuleHandleA("CockpitBase.dll"); //assume that we work inside same process

	cockpit_param_api ret;
	ret.get_parameter_handle = (PFN_ED_COCKPIT_GET_PARAMETER_HANDLE)GetProcAddress(cockpit_dll, "ed_cockpit_get_parameter_handle");
	ret.update_parameter_with_number = (PFN_ED_COCKPIT_UPDATE_PARAMETER_WITH_NUMBER)GetProcAddress(cockpit_dll, "ed_cockpit_update_parameter_with_number");
	ret.update_parameter_with_string = (PFN_ED_COCKPIT_UPDATE_PARAMETER_WITH_STRING)GetProcAddress(cockpit_dll, "ed_cockpit_update_parameter_with_string");
	ret.parameter_value_to_number = (PFN_ED_COCKPIT_PARAMETER_VALUE_TO_NUMBER)GetProcAddress(cockpit_dll, "ed_cockpit_parameter_value_to_number");
	ret.parameter_value_to_string = (PFN_ED_COCKPIT_PARAMETER_VALUE_TO_STRING)GetProcAddress(cockpit_dll, "ed_cockpit_parameter_value_to_string");
	ret.compare_parameters = (PFN_ED_COCKPIT_COMPARE_PARAMETERS)GetProcAddress(cockpit_dll, "ed_cockpit_compare_parameters");
	//base: ?setElecPower@avBaseRadio@cockpit@@UEAAX_N@Z
	//?setElecPower@avBaseRadio@cockpit@@UEAAX_N@Z
	//?setElecPower@avBasicElectric@cockpit@@UEAAX_N@Z
	//?getElecPower@avBasicElectric@cockpit@@UEBA_NXZ
	ret.setRadioPowerFncPtr = (RADIO_POWER_FUNC)GetProcAddress(cockpit_dll, "?setElecPower@avRadio_MAC@cockpit@@UEAAX_N@Z");
	//?get_set_frequency@avRadio_MAC@cockpit@@MEBAHXZ
	//?getElecPower@avRadio_MAC@cockpit@@UEBA_NXZ
	ret.getRadioPowerFncPtr = (GET_RADIO_POWER_FUNC)GetProcAddress(cockpit_dll, "?ext_is_on@avBaseRadio@cockpit@@MEBA_NXZ");
	ret.switchRadioPowerFncPtr = (GET_RADIO_POWER_FUNC)GetProcAddress(cockpit_dll, "?perform_init_state@avRadio_MAC@cockpit@@MEAAXXZ");
	ret.pfn_ed_cockpit_set_action_digital = (PFN_ED_COCKPIT_SET_ACTION_DIGITAL)GetProcAddress(cockpit_dll, "ed_cockpit_set_action_digital");
	ret.isOnIntercom = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isOn@avIntercomV2@cockpit@@UEBA_NXZ");

	ret.pfn_set_elec_power = (PFN_SET_ELEC_POWER)GetProcAddress(cockpit_dll, "?setElecPower@avBaseRadio@cockpit@@UEAAX_N@Z");
	ret.pfn_get_communicator = (PFN_GET_COMMUNICATOR)GetProcAddress(cockpit_dll, "?getCommunicator@avBaseRadio@cockpit@@QEAAAEAVavCommunicator@2@XZ");
	ret.pfn_set_communicator_as_current = (PFN_SET_COMMUNICATOR_AS_CURRENT)GetProcAddress(cockpit_dll, "?setAsCurrent@avCommunicator@cockpit@@QEAAXXZ");
	ret.device_array = (void**)GetProcAddress(cockpit_dll, "?contexts@ccCockpitContext@cockpit@@0PAV12@A");
	ret.pfn_get_dc_wire = (PFN_GET_WIRE)GetProcAddress(cockpit_dll, "?getDCbus@avSimpleElectricSystem@cockpit@@QEAAAEAVWire@Elec@EagleFM@@H@Z");
	ret.pfn_get_ac_wire = (PFN_GET_WIRE)GetProcAddress(cockpit_dll, "?getACbus@avSimpleElectricSystem@cockpit@@QEAAAEAVWire@Elec@EagleFM@@H@Z");
	ret.pfn_push_to_talk = (PFN_PUSH_TO_TALK)GetProcAddress(cockpit_dll, "?pushToTalk@avIntercomV2@cockpit@@IEAAX_N@Z");
	ret.pfn_try_set_communicator = (PFN_TRY_SET_COMMUNICATOR)GetProcAddress(cockpit_dll, "?makeSetupForCommunicator@avIntercomV2@cockpit@@MEAA_NI@Z");
	ret.pfn_is_communicator_on = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isOn@avCommunicator@cockpit@@QEBA_NXZ");
	ret.pfn_is_receiver_on = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isReceiverOn@avCommunicator@cockpit@@QEBA_NXZ");
	ret.pfn_is_transmitter_on = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isTransmitterOn@avCommunicator@cockpit@@QEBA_NXZ");

	ret.pfn_set_communicator_on = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?setOnOff@avCommunicator@cockpit@@QEAAX_N@Z");
	ret.pfn_set_receiver_on = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?setReceiverOnOff@avCommunicator@cockpit@@QEAAX_N@Z");
	ret.pfn_set_transmitter_on = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?setTransmitterOnOff@avCommunicator@cockpit@@QEAAX_N@Z");
	ret.pfn_send_net_message = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?sendNetMessage@avCommunicator@cockpit@@IEAAX_N@Z");
	ret.pfn_get_human_communicator = (PFN_GET_HUMAN_COMMUNICATOR)GetProcAddress(cockpit_dll, "?c_get_communicator@cockpit@@YAPEAVwHumanCommunicator@@XZ");


	ret.pfn_set_radius = (PFN_SET_DOUBLE)GetProcAddress(cockpit_dll, "?setScanRadius@avSidewinderSeeker@cockpit@@QEAAXN@Z");

	ret.pfn_get_weapon_count = (PFN_GET_WEAPON_COUNT)GetProcAddress(cockpit_dll, "?get_weapon_count@avSimpleWeaponSystem@cockpit@@QEAAHH@Z");
	ret.pfn_get_weapon_count = (PFN_GET_WEAPON_COUNT)GetProcAddress(cockpit_dll, "?get_weapon_count@avSimpleWeaponSystem@cockpit@@QEAAHH@Z");
	ret.pfn_avSimpleWeaponSystem_launch = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?Launch@avSimpleWeaponSystem@cockpit@@EEAAX_N@Z");
	ret.pfn_avSimpleWeaponSystem_onPick = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?on_pickle@avSimpleWeaponSystem@cockpit@@AEAAX_N@Z");
	ret.pfn_avSimpleWeaponSystem_launch_station = (PFN_LAUNCH_STATION)GetProcAddress(cockpit_dll, "?launch_station@avSimpleWeaponSystem@cockpit@@AEAAXHH@Z");

	ret.pfn_switch_battery = (PFN_SWITCH_BATTERY)GetProcAddress(cockpit_dll, "?switchBattery@avSimpleElectricSystem@cockpit@@QEAAX_N@Z");
	ret.pfn_switch_generator = (PFN_SWITCH_GENERATOR)GetProcAddress(cockpit_dll, "?switchGenerator@avSimpleElectricSystem@cockpit@@QEAAX_NH@Z");

	ret.pfn_ils_connect_electric = (PFN_CONNECT_BOTH_ELECTRIC)GetProcAddress(cockpit_dll, "?connectElecPower@avILS@cockpit@@UEAAXAEAVItemBase@Elec@EagleFM@@0@Z");
	ret.pfn_ils_is_on = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?getElecPower@avILS@cockpit@@UEBA_NXZ");
	ret.pfn_ils_set_elec_power = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?setElecPower@avILS@cockpit@@QEAAX_N@Z");
	ret.pfn_ils_is_localizer_valid = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isLocalizerValid@avILS@cockpit@@QEBA_NXZ");
	ret.pfn_ils_is_glideslope_valid = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isGlideslopeValid@avILS@cockpit@@QEBA_NXZ");
	ret.pfn_ils_get_localizer_deviation = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getLocalizerDeviation@avILS@cockpit@@QEBANXZ");
	ret.pfn_ils_get_glideslope_deviation = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getGlideslopeDeviation@avILS@cockpit@@QEBANXZ");
	ret.pfn_ils_is_marker_beacon = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isMarkerBeacon@avILS@cockpit@@QEBA_NXZ");
	ret.pfn_ils_is_outer_marker_signal = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isOuterMarkerSignal@avILS@cockpit@@QEBA_NXZ");
	ret.pfn_ils_is_middle_marker_signal = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isMiddleMarkerSignal@avILS@cockpit@@QEBA_NXZ");
	ret.pfn_ils_is_inner_marker_signal = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isInnerMarkerSignal@avILS@cockpit@@QEBA_NXZ");
	ret.pfn_ils_set_MHz = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?setFrequencyMHz@avILS@cockpit@@QEAAXH@Z");
	ret.pfn_ils_set_KHz = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?setFrequencyKHz@avILS@cockpit@@QEAAXH@Z");
	ret.pfn_ils_getLocalizerFrequency = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getLocalizerFrequency@avILS@cockpit@@IEBANXZ");
	ret.pfn_ils_getGlideslopeFrequency = (PFN_GET_DOUBLE2)GetProcAddress(cockpit_dll, "?getGlideslopeFrequency@avILS@cockpit@@MEBANN@Z");

	ret.pfn_baseRadio_get_modulation = (PFN_GET_CHAR)GetProcAddress(cockpit_dll, "?get_modulation@avBaseRadio@cockpit@@IEBADXZ");
	ret.pfn_baseRadio_set_modulation = (PFN_SET_CHAR)GetProcAddress(cockpit_dll, "?set_modulation@avBaseRadio@cockpit@@MEAAXD@Z");
	ret.pfn_baseRadio_set_volume = (PFN_SET_FLOAT)GetProcAddress(cockpit_dll, "?set_volume@avBaseRadio@cockpit@@MEAAXM@Z");
	ret.pfn_baseRadio_get_volume = (PFN_GET_FLOAT)GetProcAddress(cockpit_dll, "?get_volume@avBaseRadio@cockpit@@MEBAMXZ");
	ret.pfn_baseRadio_set_damage = (PFN_SET_DAMAGE)GetProcAddress(cockpit_dll, "?set_damage@avBaseRadio@cockpit@@UEAA_NI_N@Z");

	ret.pfn_uhf_display_testing = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?displayTesting@avUHF_ARC_164@cockpit@@QEAA_NXZ");
	ret.pfn_uhf_is_active_mode = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isActiveMode@avUHF_ARC_164@cockpit@@QEAA_NXZ");
	ret.pfn_uhf_get_knobs_frequency_KHz = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getKnobsFrequencyKHz@avUHF_ARC_164@cockpit@@QEBAHXZ");
	ret.pfn_uhf_get_knobs_frequency_MHz = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getKnobsFrequencyMHz@avUHF_ARC_164@cockpit@@QEBAHXZ");
	ret.pfn_uhf_get_net_address = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getNetAddress@avUHF_ARC_164@cockpit@@QEBAHXZ");
	ret.pfn_uhf_indication_off = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?indicationOff@avUHF_ARC_164@cockpit@@QEBA_NXZ");
	ret.pfn_uhf_get_bearing = (PFN_GET_FLOAT)GetProcAddress(cockpit_dll, "?getBearing@avUHF_ARC_164@cockpit@@UEBAMXZ");
	ret.pfn_uhf_get_alternate_frequency = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getAlternateFrequency@avUHF_ARC_164@cockpit@@QEBAHXZ");
	ret.pfn_uhf_is_alternate_freq_status = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isAlternateFreqStatus@avUHF_ARC_164@cockpit@@QEBA_NXZ");
	ret.pfn_uhf_is_preset_channel_mode = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isPresetChannelMode@avUHF_ARC_164@cockpit@@QEBA_NXZ");
	ret.pfn_uhf_set_knobs_frequency = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?set_knobs_frequency@avUHF_ARC_164@cockpit@@MEAAXH@Z");
	ret.pfn_uhf_set_preset_channel = (PFN_SET_UNSIGNED_INT)GetProcAddress(cockpit_dll, "?set_preset_channel@avUHF_ARC_164@cockpit@@MEAAXI@Z");
	ret.pfn_uhf_connect_electric = (PFN_CONNECT_ELECTRIC)GetProcAddress(cockpit_dll, "?connect_electric@avUHF_ARC_164@cockpit@@IEAAXAEAVItemBase@Elec@EagleFM@@@Z");
	ret.pfn_uhf_get_knobs_frequency = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?get_knobs_frequency@avUHF_ARC_164@cockpit@@IEBAHXZ");
	ret.pfn_uhf_isAlternateFreqStatus = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isAlternateFreqStatus@avUHF_ARC_164@cockpit@@QEBA_NXZ");

	ret.pfn_vhf_connect_electric = (PFN_CONNECT_ELECTRIC)GetProcAddress(cockpit_dll, "?connect_electric@avVHF_ARC_186@cockpit@@IEAAXAEAVItemBase@Elec@EagleFM@@@Z");
	ret.pfn_vhf_set_knobs_frequency = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?set_tuned_frequency@avBaseRadio@cockpit@@MEAAXH@Z");
	ret.pfn_vhf_get_knobs_frequency = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?get_tuned_frequency@avBaseRadio@cockpit@@QEBAHXZ");
	ret.pfn_vhf_set_modulation = (PFN_SET_CHAR)GetProcAddress(cockpit_dll, "?set_modulation@avVHF_ARC_186@cockpit@@MEAAXD@Z");

	ret.pfn_performClickAction = (PFN_PERFORM_CLICK_ACTION)GetProcAddress(cockpit_dll, "?performClickableAction@avDevice@cockpit@@QEAAXHM_N@Z");

	ret.pfn_mechanicClock_get_curretime = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?get_currtime@avMechanicClock@cockpit@@QEBANXZ");

	ret.pfn_a11Clock_get_currtime_seconds = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?get_currtime_seconds@avA11Clock@cockpit@@QEBANXZ");
	ret.pfn_a11Clock_setDamage = (PFN_SET_DAMAGE)GetProcAddress(cockpit_dll, "?set_damage@avA11Clock@cockpit@@UEAA_NI_N@Z");
	ret.pfn_a11Clock_repair = (PFN_REPAIRS)GetProcAddress(cockpit_dll, "?repair@avA11Clock@cockpit@@UEAAXXZ");
	//ret.pfn_create_lua_vm = (PFN_CREATE_LUA_VM)GetProcAddress( cockpit_dll, "ed_cockpit_open_lua_state" );
	//ret.pfn_destroy_lua_vm = (PFN_DESTROY_LUA_VM)GetProcAddress( cockpit_dll, "ed_cockpit_close_lua_state" );

	//ret.getGunShells = (GET_SOMETHING_INT)GetProcAddress(cockpit_dll, "")
	ret.pfn_TACAN_Constructor = (PFN_INITIALIZER)GetProcAddress(cockpit_dll, "??0avTACAN@cockpit@@QEAA@XZ");
	ret.pfn_TACAN_connectElectric = (PFN_CONNECT_BOTH_ELECTRIC)GetProcAddress(cockpit_dll, "?connectElecPower@avTACAN@cockpit@@QEAAXAEAVItemBase@Elec@EagleFM@@0@Z");
	ret.pfn_TACAN_getChannel = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getChannel@avTACAN@cockpit@@QEBAHXZ");
	ret.pfn_TACAN_getElecPower = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?getElecPower@avTACAN@cockpit@@UEBA_NXZ");
	ret.pfn_TACAN_getMagneticBearing = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getMagneticBearing@avTACAN@cockpit@@UEAANXZ");
	ret.pfn_TACAN_getMode = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getMode@avTACAN@cockpit@@QEBAHXZ");
	ret.pfn_TACAN_getModeXY = (PFN_GET_FREQ)GetProcAddress(cockpit_dll, "?getModeXY@avTACAN@cockpit@@QEBAHXZ");
	ret.pfn_TACAN_getRange = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getRange@avTACAN@cockpit@@UEAANXZ");
	ret.pfn_TACAN_getReceiverFrequency = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getReceiverFrequency@avTACAN@cockpit@@IEAANXZ");
	ret.pfn_TACAN_getStowedBearing = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getStowedBearing@avTACAN@cockpit@@IEAANXZ");
	ret.pfn_TACAN_getTransmitterFrequency = (PFN_GET_DOUBLE)GetProcAddress(cockpit_dll, "?getTransmitterFrequency@avTACAN@cockpit@@IEAANXZ");
	ret.pfn_TACAN_isBearingValid = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isBearingValid@avTACAN@cockpit@@UEAA_NXZ");
	ret.pfn_TACAN_isRangeValid = (PFN_IS_ON)GetProcAddress(cockpit_dll, "?isRangeValid@avTACAN@cockpit@@UEAA_NXZ");
	ret.pfn_TACAN_onChannelChanged = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?onChannelChanged@avTACAN@cockpit@@MEAAXXZ");
	ret.pfn_TACAN_post_init = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?post_initialize@avTACAN@cockpit@@UEAAXXZ");
	ret.pfn_TACAN_release = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?release@avTACAN@cockpit@@UEAAXXZ");
	ret.pfn_TACAN_repairs = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?repair@avTACAN@cockpit@@UEAAXXZ");
	ret.pfn_TACAN_setChannel = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?setChannel@avTACAN@cockpit@@UEAAXH@Z");
	ret.pfn_TACAN_setChannelXYMode = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?setChannelXYMode@avTACAN@cockpit@@UEAAXH@Z");
	ret.pfn_TACAN_setMode = (PFN_SET_INT)GetProcAddress(cockpit_dll, "?setMode@avTACAN@cockpit@@UEAAXH@Z");
	ret.pfn_TACAN_setReceiversOnOff = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?setReceiversOnOff@avTACAN@cockpit@@MEAAX_N@Z");
	ret.pfn_TACAN_setVolume = (PFN_SET_FLOAT)GetProcAddress(cockpit_dll, "?setVolume@avTACAN@cockpit@@UEAAXM@Z");
	ret.pfn_TACAN_setDamage = (PFN_SET_DAMAGE)GetProcAddress(cockpit_dll, "?set_damage@avTACAN@cockpit@@UEAA_NI_N@Z");
	ret.pfn_TACAN_switch_power = (PFN_SET_ON)GetProcAddress(cockpit_dll, "?switchElecPower@avTACAN@cockpit@@MEAAX_N@Z");
	ret.pfn_TACAN_update = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?update@avTACAN@cockpit@@UEAAXXZ");
	ret.pfn_TACAN_updateRangeBearing = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?updateRangeBearing@avTACAN@cockpit@@MEAAXXZ");
	ret.pfn_TACAN_updateWarmup = (PFN_VOID_VOID)GetProcAddress(cockpit_dll, "?updateWarmup@avTACAN@cockpit@@MEAAXXZ");

	return ret;
}