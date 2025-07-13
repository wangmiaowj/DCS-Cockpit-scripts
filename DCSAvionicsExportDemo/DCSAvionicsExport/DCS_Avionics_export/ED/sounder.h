#pragma once
#include <stdio.h>
#include "sound.h"
#include "../Avionics/avSimpleElectricSystem.h"
#include "../Avionics/avA11Clock.h"
#include "../Input.h"
class Sounder {
public:
	Sounder(Sound& p_sound, avA11Clock& p_clock, avSimpleElectricSystem& p_elec)
		:
		snd(p_sound),
		clock(p_clock),
		quaternion(),
		elec(p_elec)
	{

	}
	void init()
	{
		aircraftHost = std::make_unique< SoundHost>(snd.WORLD_CONTEXT, "J-20A_MAIN_HOST", snd);
		cptHost = std::make_unique< SoundHost>(snd.COCKPIT_CONTEXT, "J-20A_MAIN_CPT_HOST", snd);
		headPhonesHost = std::make_unique< SoundHost>(snd.HEADPHONES_CONTEXT, "J-20A_MAIN_HP_HOST", snd);
		aircraftHost->addSource(SND_PLAYMODE_ONCE, protos.APU_Start);
		aircraftHost->addSource(SND_PLAYMODE_LOOPED, protos.APU_Running);
		aircraftHost->addSource(SND_PLAYMODE_LOOPED, protos.APU_End);
		aircraftHost->addSource(SND_PLAYMODE_LOOPED, protos.airbrakeRun);
		aircraftHost->addSource(SND_PLAYMODE_LOOPED, protos.airbrakeEnd);
		aircraftHost->addSource(SND_PLAYMODE_LOOPED, protos.flapRun);
		aircraftHost->addSource(SND_PLAYMODE_LOOPED, protos.flapEnd);
		aircraftHost->addSource(SND_PLAYMODE_ONCE, protos.laserFire);
		cptHost->addSource(SND_PLAYMODE_ONCE, protos.APU_Start);
		cptHost->addSource(SND_PLAYMODE_LOOPED, protos.APU_Running);
		cptHost->addSource(SND_PLAYMODE_LOOPED, protos.APU_End);
		cptHost->addSource(SND_PLAYMODE_ONCE, protos.laserFireIn);
		headPhonesHost->addSource(SND_PLAYMODE_ONCE, protos.Test);
		headPhonesHost->addSource(SND_PLAYMODE_ONCE, protos.bitSucc);
		headPhonesHost->addSource(SND_PLAYMODE_ONCE, protos.leftEngFire);
		headPhonesHost->addSource(SND_PLAYMODE_ONCE, protos.rightEngFire);
		headPhonesHost->addSource(SND_PLAYMODE_ONCE, protos.brokenWingWaring);
		aircraftHost->getSource(protos.APU_Start).link(cptHost->getSource(protos.APU_Start));
		aircraftHost->getSource(protos.APU_Running).link(cptHost->getSource(protos.APU_Running));
		aircraftHost->getSource(protos.APU_End).link(cptHost->getSource(protos.APU_End));
		aircraftHost->getSource(protos.laserFire).link(cptHost->getSource(protos.laserFire));
		//headPhonesHost->getSource(protos.Test).playOnce();

		world3DListenerParam = std::make_unique<SND_ListenerParams>();
		world3DListenerParam->fields = 5;
		world3DListenerParam->position[0] = 0.0;
		world3DListenerParam->position[1] = 0.0;
		world3DListenerParam->position[2] = 0.0;
		world3DListenerParam->velocity[0] = 0.0;
		world3DListenerParam->velocity[1] = 0.0;
		world3DListenerParam->velocity[2] = 0.0;
		world3DListenerParam->orientation[0] = 0.0;
		world3DListenerParam->orientation[1] = 0.0;
		world3DListenerParam->orientation[2] = 0.0;
		world3DListenerParam->orientation[3] = 0.0;
		world3DListenerParam->gain = 1.0;
		world3DListenerParam->pitch = 1.0;
		world3DListenerParam->lowpass = 24000.0;
		world3DListenerParam->timestamp = 0.0;
		snd.snd_set_listener(snd.WORLD_CONTEXT, world3DListenerParam.get());
		printf("sounder init\n");
	}
	void updateApuSnd(double dt)
	{
		
	}
	void updateAirBrakeSnd(double dt) {
		SoundSource& airbrakeRunSrc = aircraftHost->getSource(protos.airbrakeRun);
		SoundSource& airbrakeEndSrc = aircraftHost->getSource(protos.airbrakeEnd);
	}
	void updateFlapSnd(double dt) {
		SoundSource& flapRunSrc = aircraftHost->getSource(protos.flapRun);
		SoundSource& flapEndSrc = aircraftHost->getSource(protos.flapEnd);
	}
	void updateBitSnd(double dt)
	{
		
	}
	void updateWarning(double dt)
	{
		
	}
	void setCommand(int cmd, float value)
	{
		if (cmd == LaserFire)
		{
			SoundSource& laserFireSrc = aircraftHost->getSource(protos.laserFire);
			laserFireSrc.playOnce();
		}
	}
	void update(double dt,Vec3 worldPosition,Vec3 localSpeed,Quaternion quaternion)
	{
		//updateApuSnd(dt);
		updateBitSnd(dt);
		updateAirBrakeSnd(dt);
		updateFlapSnd(dt);
		try
		{
			updateWarning(dt);
		}
		catch (const std::exception& e)
		{
			printf("%s\n", e.what());
		}
		headPhonesHost->update(dt,worldPosition,localSpeed, clock.get_currtime(), quaternion);
		aircraftHost->update(dt, worldPosition, localSpeed, clock.get_currtime(), quaternion);
		cptHost->update(dt, worldPosition, localSpeed, clock.get_currtime(), quaternion);
		world3DListenerParam->position[0] = worldPosition.x;
		world3DListenerParam->position[1] = worldPosition.y;
		world3DListenerParam->position[2] = worldPosition.z;
		world3DListenerParam->velocity[0] = localSpeed.x;
		world3DListenerParam->velocity[1] = localSpeed.y;
		world3DListenerParam->velocity[2] = localSpeed.z;
		world3DListenerParam->orientation[0] = quaternion.x;
		world3DListenerParam->orientation[1] = quaternion.y;
		world3DListenerParam->orientation[2] = quaternion.z;
		world3DListenerParam->orientation[3] = quaternion.w;
		world3DListenerParam->timestamp = clock.get_currtime();
	}
	void setCurrentOrientation(const Quaternion& _quaternion)
	{
		quaternion = _quaternion;
	}
private:
	struct Protos {
		Proto Test = Proto(L"Mp3Player/HOYO-MiX - Ê±ÄºµÄË¼¾ì Le Souvenir avec le crepuscule", 90.666f);
		Proto APU_Start = Proto(L"Aircrafts/J-20A/APU", 24.628f);
		Proto APU_Running = Proto(L"Aircrafts/J-20A/APU_loop", 10.066f);
		Proto APU_End = Proto(L"Aircrafts/FA-18/APU_End", 20.498f);
		Proto bitSucc = Proto(L"Aircrafts/J-20A/Cockpit/bitComplate", 1.550f);
		Proto leftEngFire = Proto(L"Aircrafts/J-20A/Cockpit/Warning/LeftEngineFire", 1.934f);
		Proto rightEngFire = Proto(L"Aircrafts/J-20A/Cockpit/Warning/RightEngineFire", 1.867f);
		Proto brokenWingWaring = Proto(L"Aircrafts/F-15/Cockpit/OWS2", 0.805f);
		Proto airbrakeRun = Proto(L"Aircrafts/AirBrake", 6.619f);
		Proto airbrakeEnd = Proto(L"Aircrafts/AirBrakeEnd", 0.739f);
		Proto flapRun = Proto(L"Aircrafts/FlapsElectric", 4.609f);
		Proto flapEnd = Proto(L"Aircrafts/FlapsElectricEnd", 0.542f);
		Proto laserFire = Proto(L"Weapons/LaserFire", 1.134f, 5.0f, 5000.0f);
		Proto laserFireIn = Proto(L"Weapons/LaserFire", 1.134f);
	};
	Sound& snd;
	avA11Clock& clock;
	avSimpleElectricSystem& elec;
	std::unique_ptr< SoundHost> aircraftHost;
	std::unique_ptr< SoundHost> cptHost;
	std::unique_ptr< SoundHost> headPhonesHost;
	std::map<std::wstring, int>warningPlayIdxMap;
	std::vector<int>warningPlayList;
	std::unique_ptr< SND_ListenerParams> world3DListenerParam;
	int playIdx = -1;
	Protos protos;
	int apuSndPlayStep = 0;
	Quaternion quaternion;
};