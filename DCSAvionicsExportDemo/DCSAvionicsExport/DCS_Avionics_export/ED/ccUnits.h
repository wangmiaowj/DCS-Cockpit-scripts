#pragma once
class ccUConverter {
public:
	static ccUConverter& instance()
	{
		return ccUConverter();
	}
	double MetersToNM(double meters)
	{
		return meters * unit.nm;
	}
	double MetersToKM(double meters)
	{
		return meters * unit.km;
	}
	double MetersToFeet(double meters)
	{
		return meters * unit.feet;
	}
	double MetersToYard(double meters)
	{
		return meters * unit.yard;
	}
	double MS_ToKmH(double ms)
	{
		return ms * unit.kmh;
	}
	double MS_ToKts(double ms)
	{
		return ms * unit.kts;
	}
	double MS_ToFpm(double ms)
	{
		return ms * unit.fpm;
	}
	double RadToDeg(double rad)
	{
		return rad * unit.deg;
	}
	double PaToMmHg(double pa)
	{
		return pa * unit.mmHg;
	}
	double PaToIm(double pa)
	{
		return pa * unit.im;
	}
private:
	ccUConverter() {} // ˽�й��캯������ֹ�ⲿ����ʵ��  
	~ccUConverter() {} // ˽��������������ֹ�ⲿɾ��ʵ��  
	ccUConverter(const ccUConverter&) = delete; // ɾ�����ƹ��캯��  
	ccUConverter& operator=(const ccUConverter&) = delete; // ɾ����ֵ�����  
	struct Unit {
		double m = 1.0;
		double km = 1.0 / 1000.0;
		double feet = 3.2808399;
		double yard = 0.9144;
		double nm = 1.0 / 1851.9999984;
		double ms = 1.0;
		double kmh = 3.6;
		double kts = 3600.0 / 1851.9999984;
		double fpm = 60.0 * 3.2808399;
		double deg = 57.296;
		double mmHg = 1.0 / 133.3;
		double im = 1.0 / 133.3 / 25.4;
	};
	Unit unit;
};