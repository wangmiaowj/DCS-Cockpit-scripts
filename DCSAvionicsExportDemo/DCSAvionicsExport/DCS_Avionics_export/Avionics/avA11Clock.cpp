#include "avA11Clock.h"
avA11Clock::avA11Clock(avSimpleElectricSystem& p_elec, EDPARAM& edParam)
	:
	elec(p_elec),
	cockpitApi(edParam)
{
	params[CURRENT_SECOND] = EdParam(edParam.getParamHandle("CURRENT_SECOND"), 0.0);
	params[CURRENT_TIME] = EdParam(edParam.getParamHandle("CURRENT_TIME"), 0.0);
	params[CLOCK_HH] = EdParam(edParam.getParamHandle("CLOCK_HH"), 0.0);
	params[CLOCK_MM] = EdParam(edParam.getParamHandle("CLOCK_MM"), 0.0);
	params[CLOCK_SS] = EdParam(edParam.getParamHandle("CLOCK_SS"), 0.0);
}
void avA11Clock::zeroInit() {

}
void avA11Clock::coldInit() {
	zeroInit();
}
void avA11Clock::hotInit() {
	zeroInit();
}
void avA11Clock::airborneInit() {
	zeroInit();
}
void avA11Clock::setCommand(int command, float value)
{

}
void avA11Clock::update(double dt)
{
	params[CURRENT_SECOND].tg = get_currtime_seconds();
	params[CURRENT_TIME].tg = get_currtime();
	params[CLOCK_HH].tg = floor(params[CURRENT_TIME].tg / 3600);
	params[CLOCK_MM].tg = floor((params[CURRENT_TIME].tg - params[CLOCK_HH].tg * 3600) / 60);
	params[CLOCK_SS].tg = params[CURRENT_TIME].tg - params[CLOCK_HH].tg * 3600 - params[CLOCK_MM].tg * 60;
	for (auto it = params.begin(); it != params.end(); ++it)
	{
		it->second.update(cockpitApi);
	}
}
bool avA11Clock::set_damage(unsigned Failure_ID, const bool can_be_rejected)
{
	try
	{
		return cockpitApi.clock_set_damage(Failure_ID, can_be_rejected);
	}
	catch (const MyException& e)
	{
		e.printMsg();
		return false;
	}
}
void avA11Clock::repair()
{
	try
	{
		cockpitApi.clock_repair();
	}
	catch (const MyException& e)
	{
		e.printMsg();
	}
}
double avA11Clock::get_currtime_seconds()
{
	try
	{
		return cockpitApi.get_currtime_seconds();
	}
	catch (const MyException& e)
	{
		e.printMsg();
		return 0.0;
	}
}
double avA11Clock::get_currtime()
{
	try
	{
		return cockpitApi.get_currtime();
	}
	catch (const MyException& e)
	{
		e.printMsg();
		return 0.0;
	}
}