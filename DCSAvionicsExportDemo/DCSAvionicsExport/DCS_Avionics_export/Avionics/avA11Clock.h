#pragma once
#include <stdio.h>
#include "../Maths.h"
#include "../ED/CockpitAPI_Declare.h"
#include "avSimpleElectricSystem.h"
#include <map>
#include "../Table.h"

class avA11Clock
{
	typedef enum CLOCK_commands
	{
		CLOCK_lev_up = 3001,
		CLOCK_lev_rotate,
		CLOCK_lev_up_Ext,
		CLOCK_lev_rotate_Ext
	};

	enum A11_Clock_Failures
	{
		A11_CLOCK_FAILURE = 0,
	};
public:
	avA11Clock(avSimpleElectricSystem& p_elec, EDPARAM& edParam);
	virtual void zeroInit();
	virtual void coldInit();
	virtual void hotInit();
	virtual void airborneInit();

	void update(double dt); //in der () "double dt" eingefügt, war vorher ohne
	void setCommand(int command, float value);
	bool set_damage(unsigned Failure_ID, const bool can_be_rejected);
	void repair();
	double get_currtime_seconds();
	double get_currtime();
private:
	enum paramNames {
		CURRENT_SECOND,
		CURRENT_TIME,
		CLOCK_HH,
		CLOCK_MM,
		CLOCK_SS,
	};
	EDPARAM& cockpitApi;
	avSimpleElectricSystem& elec;
	std::map<int, EdParam>params;
};