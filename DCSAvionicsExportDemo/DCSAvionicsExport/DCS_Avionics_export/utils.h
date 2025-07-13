#pragma once
#include <windows.h>  
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>  
static inline const std::string wcharToChar(const WCHAR* wstr)
{
	if (wstr == nullptr) return "";

	// ȷ��ת����������ֽ���  
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
	if (size_needed == 0) {
		// �������  
		return "";
	}

	// �����㹻�Ŀռ����洢ת������ַ������������ַ���  
	std::vector<char> mbstr(size_needed);

	// ִ��ʵ�ʵ�ת��  
	int result = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &mbstr[0], size_needed, nullptr, nullptr);
	if (result == 0) {
		// �������  
		return "";
	}

	// ת���ɹ������������ݸ��Ƶ�string�в�����  
	return std::string(mbstr.begin(), mbstr.end());
}
static inline void SecondsTo_ddHHmmss(unsigned long seconds, int& day, int& hours, int& min, int& second)
{
	day = seconds / 86400;
	hours = (seconds - day * 86400) / 3600;
	min = (seconds - day * 86400 - hours * 3600) / 60;
	second = seconds - day * 86400 - hours * 3600 - min * 60;
}
static inline std::string SecondsFormat_mmss(unsigned long seconds, int& min, int& second)
{
	int day, hours = 0;
	SecondsTo_ddHHmmss(seconds, day, hours, min, second);
	std::ostringstream oss; // ����ַ�����  
	oss << std::setfill('0') << std::setw(2) << min << ":"
		<< std::setfill('0') << std::setw(2) << second;

	return oss.str(); // ���ظ�ʽ�����ַ���  
}

static inline double DMS_to_DD(const std::string& way, const double dd, const double mm, const double ss)
{
	if (dd > 90 || dd < -90 || mm>59 || mm < 0 || ss>59 || ss < 0)
	{
		return 0;
	}
	double DD = dd + mm / 60 + ss / 3600;
	if (way == "S" || way == "W")
	{
		DD = -DD;
	}
	else if (way != "E" && way != "N")
	{
		return 0.0;
	}
	return DD;
}
//type��1����γ�ȣ�0���Ǿ���
static inline void DD_to_D_M_S(double dd, int type, std::string& way, double& d, double& m, double& s)
{
	if (((dd > 90 || dd < -90) && type == 1) || ((dd > 180 || dd < -180) && type != 1))
	{
		return;
	}
	d = floor(dd);
	double m_d = (dd - d) * 60;
	m = floor(m_d);
	s = (m_d - m) * 60;
	if (d > 0)
	{
		if (type == 1)
		{
			way = "N";
		}
		else
		{
			way = "E";
		}
	}
	else
	{
		if (type == 1)
		{
			way = "S";
		}
		else
		{
			way = "W";
		}
	}
	d = abs(d);
}
static std::string DD_to_DMS(double dd, int type)
{
	std::string way = "";
	double d = 0.0, m = 0.0, s = 0.0;
	DD_to_D_M_S(dd, type, way, d, m, s);
	std::ostringstream oss;
	if (type == 1)
	{
		// ����γ�ȣ�ʹ��%02d��ȷ����������ռ��λ���֣����Ӻ������ֱ�ʹ��%02d��%05.2f  
		oss << way << std::setfill('0') << std::setw(2) << static_cast<int>(d) << "-"
			<< std::setw(2) << static_cast<int>(m) << "-"
			<< std::fixed << std::setprecision(2) << std::setw(5) << s;
	}
	else
	{
		// ���ھ��ȣ�ʹ��%03d��ȷ����������ռ��λ���֣���Ϊ���ȿ�������λ������180�ȣ�  
		oss << way << std::setfill('0') << std::setw(3) << static_cast<int>(d) << "-"
			<< std::setw(2) << static_cast<int>(m) << "-"
			<< std::fixed << std::setprecision(2) << std::setw(5) << s;
	}

	// ��ȡoss�����ɵ��ַ���  
	return oss.str();
}