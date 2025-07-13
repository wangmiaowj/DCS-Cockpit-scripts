#include "DCS_Avionics_exportAPI.h"
#include "stdafx.h"
extern "C"
{
#include "include/lua/lua.h"
#include "include/lua/lualib.h"
#include "include/lua/lauxlib.h"
	DCS_AVIONICS_EXPORT_API int l_setVhfFM(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_setVhfFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_setVhfVolume(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_vhfIsFM(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_getVhfFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_initVhf(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_vhfPushTalk(lua_State* L);

	DCS_AVIONICS_EXPORT_API int l_setUhfFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_setUhfVolume(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_getUhfFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_initUhf(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_uhfPushTalk(lua_State* L);

	DCS_AVIONICS_EXPORT_API int l_initElec(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_initIntercom(lua_State* L);

	DCS_AVIONICS_EXPORT_API int l_setIlsFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_getIlsLocalizerFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_getIlsGlideslopeFreq(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_ilsIsLocalizerValid(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_ilsIsGlideslopeValid(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_getIlsLocalizerDeviation(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_getIlsGlideslopeDeviation(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_ilsIsMarkerBeacon(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_ilsIsOuterMarkerSignal(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_ilsIsMiddleMarkerSignal(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_ilsIsInnerMarkerSignal(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_enableIls(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_disableIls(lua_State* L);
	DCS_AVIONICS_EXPORT_API int l_initIls(lua_State* L);

	DCS_AVIONICS_EXPORT_API int l_release(lua_State* L);

	DCS_AVIONICS_EXPORT_API int l_test(lua_State* L);

	DCS_AVIONICS_EXPORT_API int luaopen_DCSAvionicsExport(lua_State* L);//luaopen_后面的名字很重要，一定要和dll名字相同
	DCS_AVIONICS_EXPORT_API int lua_DCSAvionicsExport_destroy(lua_State* L);
};