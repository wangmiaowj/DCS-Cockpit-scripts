#pragma once
#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include "ED/CockpitAPI_Declare.h"
#include "Maths.h"
class EdParam
{
public:
	EdParam() :
		param(0),
		tg(-128),
		tgText("NULL"),
		cur(-128),
		dt(-128),
		mode(0),
		min(0),
		max(1)
	{

	}
	EdParam(void* paramHandle, double target, double current, double rate) :
		param(paramHandle),
		tg(target),
		tgText("NULL"),
		cur(current),
		dt(rate),
		mode(1),
		min(0),
		max(1)
	{

	}
	EdParam(void* paramHandle, double target, double current, double rate, double min, double max) :
		param(paramHandle),
		tg(target),
		tgText("NULL"),
		cur(current),
		dt(rate),
		mode(1),
		min(min),
		max(max)
	{

	}
	EdParam(void* paramHandle, double target) :
		param(paramHandle),
		tg(target),
		tgText("NULL"),
		cur(-128),
		dt(-128),
		mode(0),
		min(0),
		max(1)
	{

	}
	EdParam(void* paramHandle, const char* target) :
		param(paramHandle),
		tgText(target),
		tg(-128),
		cur(-128),
		dt(-128),
		mode(2),
		min(0),
		max(1)
	{

	}
	void update(EDPARAM& cockpitAPI)
	{
		if (mode == 1)
		{
			if (abs(tg - cur) < dt)
			{
				cur = tg;
			}
			else if (tg > cur)
			{
				cur = clamp(cur + dt, min, max);
			}
			else if (tg < cur)
			{
				cur = clamp(cur - dt, min, max);
			}
			cockpitAPI.setParamNumber(param, cur);
		}
		else if (mode == 0)
		{
			cockpitAPI.setParamNumber(param, tg);
		}
		else
		{
			cockpitAPI.setParamString(param, tgText);
		}
	}
	void* param;
	double tg;
	const char* tgText;
	double cur;
	double dt;
	double min, max;
	int mode;//0 直接更新tg，1更新cur，2更新text
private:

};
class Proto
{
public:
	Proto(const std::wstring& _path, float _length, float _gain, float _radius, float _pitch, float _lowpass) :
		path(_path), length(_length), gain(_gain), radius(_radius), pitch(_pitch), lowpass(_lowpass) {}
	Proto(const std::wstring& _path, float _length, float _gain, float _radius, float _pitch) :
		path(_path), length(_length), gain(_gain), radius(_radius), pitch(_pitch), lowpass(24000.0f) {}
	Proto(const std::wstring& _path, float _length, float _gain, float _radius) :
		path(_path), length(_length), gain(_gain), radius(_radius), pitch(1.0f), lowpass(24000.0f) {}
	Proto(const std::wstring& _path, float _length, float _gain) :
		path(_path), length(_length), gain(_gain), radius(1000.0f), pitch(1.0f), lowpass(24000.0f) {}
	Proto(const std::wstring& _path, float _length) :
		path(_path), length(_length), gain(1.0f), radius(1000.0f), pitch(1.0f), lowpass(24000.0f) {}
	const std::wstring path;
	const float gain;
	const float pitch;
	const float radius;
	const float lowpass;
	const float length;
};
class Pylon {
public:
	class WsType {
	public:
		WsType():level1(0),level2(0), level3(0), level4(0),isValid(false){}
		int level1; int level2; int level3; int level4; bool isValid;
	};
	Pylon() :count(0), CLSID(""), container(false)
	{
		adapter = WsType(); weapon = WsType(); wstype = WsType();
	}
	WsType wstype;
	int count;
	std::string CLSID;
	WsType adapter;
	bool container;
	WsType weapon;
};
#endif
