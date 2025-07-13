#include "DCS_Avionics_export.h"
#include "ED/CockpitAPI_Declare.h"
#include "Avionics/avSimpleElectricSystem.h"
#include "Avionics/avILS.h"
#include "Avionics/avUHF_ARC_164.h"
#include "Avionics/avVHF_ARC_186.h"
#include "Avionics/avA11Clock.h"
#include "ED/sound.h"

EDPARAM* edParam = nullptr;
avSimpleElectricSystem* elect = nullptr;
avILS* ils = nullptr;
avUHF_ARC_164* uhf = nullptr;
avVHF_ARC_186* vhf = nullptr;
avA11Clock* s_clock = nullptr;
Sound* snd = nullptr;

int l_setUhfFreq(lua_State* L)
{
	int freq = luaL_checkint(L, 1);
	uhf->setFreq(freq);
	return 0;
}
int l_setUhfVolume(lua_State*L)
{
	double volume = luaL_checknumber(L, 1);
	uhf->setVolume(volume);
	return 0;
}
int l_getUhfFreq(lua_State* L)
{
	lua_pushinteger(L, uhf->getFreq());
	return 1;
}
int l_uhfPushTalk(lua_State* L)
{
	uhf->pushTalk();
	return 0;
}
int l_initUhf(lua_State* L)
{
	int deviceId = luaL_checknumber(L, 1);
	uhf->init(deviceId);
	return 0;
}
int l_setVhfFM(lua_State* L)
{
	vhf->setFM();
	return 0;
}
int l_setVhfAM(lua_State* L)
{
	vhf->setAM();
	return 0;
}
int l_setVhfFreq(lua_State* L)
{
	int freq = luaL_checkinteger(L, 1);
	vhf->setFreq(freq);
	return 0;
}
int l_setVhfVolume(lua_State* L)
{
	double volume = luaL_checknumber(L, 1);
	vhf->setVolume(volume);
	return 0;
}
int l_vhfIsFM(lua_State* L)
{
	lua_pushboolean(L, vhf->isFM());
	return 1;
}
int l_getVhfFreq(lua_State* L)
{
	lua_pushinteger(L, vhf->getFreq());
	return 1;
}
int l_initVhf(lua_State* L)
{
	int deviceId = luaL_checkinteger(L,1);
	bool fm = luaL_checkinteger(L, 2);
	vhf->init(deviceId, fm);
	return 0;
}
int l_vhfPushTalk(lua_State* L)
{
	vhf->pushTalk();
	return 0;
}
int l_disableIls(lua_State* L)
{
	ils->disable();
	return 0;
}
int l_enableIls(lua_State* L)
{
	ils->enable();
	return 0;
}
int l_setIlsFreq(lua_State* L)
{
	double freq = luaL_checkinteger(L, 1);
	ils->setFreq(freq);
	return 0;
}
int l_getIlsLocalizerFreq(lua_State* L)
{
	lua_pushnumber(L, ils->getLocalizerFreq());
	return 1;
}
int l_getIlsGlideslopeFreq(lua_State* L)
{
	double localizerFreq = luaL_checknumber(L, 1);
	lua_pushnumber(L, ils->getGlideslopeFrequency(localizerFreq));
	return 1;
}
int l_ilsIsLocalizerValid(lua_State* L)
{
	lua_pushboolean(L, ils->isLocalizerValid());
	return 1;
}
int l_ilsIsGlideslopeValid(lua_State* L)
{
	lua_pushboolean(L, ils->isGlideslopeValid());
	return 1;
}
int l_getIlsLocalizerDeviation(lua_State* L)
{
	lua_pushnumber(L, ils->getLocalizerDeviation());
	return 1;
}
int l_getIlsGlideslopeDeviation(lua_State* L)
{
	lua_pushnumber(L, ils->getGlideslopeDeviation());
	return 1;
}
int l_ilsIsMarkerBeacon(lua_State* L)
{
	lua_pushboolean(L, ils->isMarkerBeacon());
	return 1;
}
int l_ilsIsOuterMarkerSignal(lua_State* L)
{
	lua_pushboolean(L, ils->isOuterMarkerSignal());
	return 1;
}
int l_ilsIsMiddleMarkerSignal(lua_State* L)
{
	lua_pushboolean(L, ils->isMiddleMarkerSignal());
	return 1;
}
int l_ilsIsInnerMarkerSignal(lua_State* L)
{
	lua_pushboolean(L, ils->isInnerMarkerSignal());
	return 1;
}
int l_initIls(lua_State* L)
{
	int deviceId = luaL_checkinteger(L, 1);
	ils->init(deviceId);
	return 0;
}
int l_initElec(lua_State* L)
{
	int deviceId = luaL_checkint(L, 1);
	elect->init(deviceId);
	return 0;//������������Ǹ���lua������Ҫ���ظ�����ٶ���
}
int l_initIntercom(lua_State* L)
{
	int deviceId = luaL_checkint(L, 1);
	edParam->INTERCOM = deviceId;
	edParam->initDevice(deviceId);
	return 0;//������������Ǹ���lua������Ҫ���ظ�����ٶ���
}

int l_release(lua_State* L)
{
	delete vhf;
	delete uhf;
	delete elect;
	delete ils;
	delete s_clock;
	delete snd;
	delete edParam;
	vhf = nullptr;
	uhf = nullptr;
	ils = nullptr;
	s_clock = nullptr;
	elect = nullptr;
	snd = nullptr;
	edParam = nullptr;
	return 0;
}

luaL_Reg UHF[] = {
	{"setFreq",l_setUhfFreq},//��һ����lua�����������ʱ�õľ����������
	{"setVolume",l_setUhfVolume},
	{"getFreq",l_getUhfFreq},
	{"pushTalk",l_uhfPushTalk},
	
	{NULL,NULL}//��Ҫ����NULL��β
};
luaL_Reg VHF[] = {
	{"setFM",l_setVhfFM},
	{"setAM",l_setVhfAM},
	{"setFreq",l_setVhfFreq},
	{"setVolume",l_setVhfVolume},
	{"isFM",l_vhfIsFM},
	{"getFreq",l_getVhfFreq},
	{"pushTalk",l_vhfPushTalk},

	{NULL,NULL}
};
luaL_Reg ILS[] = {

	{"disable",l_disableIls},
	{"enable",l_enableIls},
	{"setFreq",l_setIlsFreq},
	{"getGlideslopeFreq",l_getIlsGlideslopeFreq},
	{"getLocalizerFreq",l_getIlsLocalizerFreq},
	{"isLocalizerValid",l_ilsIsLocalizerValid},
	{"isGlideslopeValid",l_ilsIsGlideslopeValid},
	{"getLocalizerDeviation",l_getIlsLocalizerDeviation},
	{"getGlideslopeDeviation",l_getIlsGlideslopeDeviation},
	{"isInnerMarkerSignal",l_ilsIsInnerMarkerSignal},
	{"isMiddleMarkerSignal",l_ilsIsMiddleMarkerSignal},
	{"isOuterMarkerSignal",l_ilsIsOuterMarkerSignal},
	{"isMarkerBeacon",l_ilsIsMarkerBeacon},

	{NULL,NULL},
};

luaL_Reg init[] = {
	{"ils",l_initIls},
	{"electric",l_initElec},
	{"intercom",l_initIntercom},
	{"vhf",l_initVhf},
	{"uhf",l_initVhf},

	{NULL,NULL},
};

void luaL_pushFuncToTable(lua_State* L, int table_idx,const char* name, lua_CFunction func)
{
	lua_pushstring(L, name); // ѹ�������������
	lua_pushcfunction(L, func); // ѹ��ֵ��C ������
	lua_settable(L, table_idx); // ���õ�����
}
// �������������ڽ� luaL_Reg �����еĺ���ע�ᵽ Lua ����
void luaL_register_to_table(lua_State* L, int table_idx, const luaL_Reg* l) {
	for (; l->name != NULL; l++) {
		luaL_pushFuncToTable(L,table_idx,l->name,l->func);
	}
}

// ���ڴ�Lua stack�ж�ȡWsType  
Pylon::WsType readWsType(lua_State* L, int index) {
	Pylon::WsType wsType;
	lua_getfield(L, index, "level1"); wsType.level1 = lua_tointeger(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "level2"); wsType.level2 = lua_tointeger(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "level3"); wsType.level3 = lua_tointeger(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "level4"); wsType.level4 = lua_tointeger(L, -1); lua_pop(L, 1);
	wsType.isValid = true;
	return wsType;
}

// ���ڴ�Lua stack�ж�ȡPylon  
Pylon readPylon(lua_State* L, int index) {
	Pylon pylon;
	lua_getfield(L, index, "CLSID"); pylon.CLSID = lua_tostring(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "container"); pylon.container = lua_toboolean(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "count"); pylon.count = lua_tointeger(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "weapon"); pylon.weapon = readWsType(L, -1); lua_pop(L, 1);
	lua_getfield(L, index, "adapter");
	if (lua_istable(L,-1))
	{
		pylon.adapter = readWsType(L, -1);
	}
	else
	{
		printf("adapter Nope\n");
	}
	lua_pop(L, 1);
	lua_getfield(L, index, "wstype");
	if (lua_istable(L,-1))
	{
		pylon.wstype = readWsType(L, -1);
	}
	else
	{
		printf("wstype Nope\n");
	}
	lua_pop(L, 1);
	return pylon;
}

int l_test(lua_State* L)
{
	if (!lua_istable(L,1))
	{
		return 0;
	}
	std::vector<Pylon> pylons;
	lua_pushnil(L); // ��һ��key  
	while (lua_next(L, 1) != 0) {
		// ʹ�� 'key' (������ -2 ��) �� 'value' (������ -1 ��)  
		// 'key' �������ţ�����������У�  
		int key = lua_tonumber(L, -2);
		// ��ȡPylon�ṹ��  
		Pylon pylon = readPylon(L, -1);

		// ��Pylon��ӵ�vector��
		pylons.push_back(pylon);

		// �Ƴ� 'value'������ 'key' ������һ�ε���  
		lua_pop(L, 1);
	}
	for (int i = 1; i <= pylons.size();i++) {
		// ��ӡ����pylon...
		Pylon pylon = pylons[i-1];
		printf("pylon_%d.CLSID = \"%s\",\n",i,pylon.CLSID.c_str());
		printf("pylon_%d.count = %d,\n", i, pylon.count);
		printf("pylon_%d.container = %s,\n", i, pylon.container?"true":"false");
		printf("pylon_%d.weapon.level1 = %d,\n", i, pylon.weapon.level1);
		printf("pylon_%d.weapon.level2 = %d,\n", i, pylon.weapon.level2);
		printf("pylon_%d.weapon.level3 = %d,\n", i, pylon.weapon.level3);
		printf("pylon_%d.weapon.level4 = %d,\n", i, pylon.weapon.level4);
		if (pylon.adapter.isValid)
		{
			printf("pylon_%d.adapter.level1 = %d,\n", i, pylon.adapter.level1);
			printf("pylon_%d.adapter.level2 = %d,\n", i, pylon.adapter.level2);
			printf("pylon_%d.adapter.level3 = %d,\n", i, pylon.adapter.level3);
			printf("pylon_%d.adapter.level4 = %d,\n", i, pylon.adapter.level4);
		}
		if (pylon.wstype.isValid)
		{
			printf("pylon_%d.wstype.level1 = %d,\n", i, pylon.wstype.level1);
			printf("pylon_%d.wstype.level2 = %d,\n", i, pylon.wstype.level2);
			printf("pylon_%d.wstype.level3 = %d,\n", i, pylon.wstype.level3);
			printf("pylon_%d.wstype.level4 = %d,\n", i, pylon.wstype.level4);
		}		
	}
	return 0;
}

int luaopen_DCSAvionicsExport(lua_State* L)//luaopen_��������ֺ���Ҫ��һ��Ҫ��dll������ͬ
{
	lua_newtable(L);//�ܱ�
	int tblIdx = lua_gettop(L);
	luaL_pushFuncToTable(L, tblIdx, "test", l_test);
	luaL_pushFuncToTable(L, tblIdx, "release", l_release);
	lua_newtable(L);//uhf
	tblIdx = lua_gettop(L);
	luaL_register_to_table(L, tblIdx,UHF);
	lua_setfield(L, -2, "UHF");

	lua_newtable(L);//vhf
	tblIdx = lua_gettop(L);
	luaL_register_to_table(L, tblIdx, VHF);
	lua_setfield(L, -2, "VHF");

	lua_newtable(L);//ils
	tblIdx = lua_gettop(L);
	luaL_register_to_table(L, tblIdx, ILS);
	lua_setfield(L, -2, "ILS");

	lua_newtable(L);//init
	tblIdx = lua_gettop(L);
	luaL_register_to_table(L, tblIdx, init);
	lua_setfield(L, -2, "init");
	
	edParam = new EDPARAM();
	elect = new avSimpleElectricSystem(*edParam);
	uhf = new avUHF_ARC_164(*edParam, *elect);
	vhf = new avVHF_ARC_186(*edParam, *elect);
	ils = new avILS(*edParam, *elect);
	s_clock = new avA11Clock(*elect, *edParam);

	printf("��ʼ���ɹ�\n");
	return 1;
}