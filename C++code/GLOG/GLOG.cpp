#include "GLOG.h"

using namespace std;

void OutputDebugPrintf(const char *strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	//vsprintf(strBuffer, strOutputString, vlArgs);
	va_end(vlArgs);
	//OutputDebugString(CA2W(strBuffer));
}

GLOG::GLOG()
{
}

GLOG::GLOG(std::string lnfo_file, std::string error_file)
{
	this->setInfoFile(lnfo_file);
	this->setErrorFile(error_file);
}


GLOG::~GLOG()
{
	GLOG_end_();
}

bool GLOG::GLOG_start_(std::string lnfo_file, std::string error_file)
{
	this->setInfoFile(lnfo_file);
	this->setErrorFile(error_file);
	return this->GLOG_start_();
}

bool GLOG::GLOG_start_()
{
	if (!isOpend())
	{
		m_info_log.open(m_info_log_file, ios::app);
		m_error_log.open(m_error_log_file, ios::app);
		return isOpend();
	}
}

void GLOG::GLOG_end_()
{
	if (isOpend())
	{
		m_info_log.close();
		m_error_log.close();
	}
}

void GLOG::INFO_LOG(std::string str)
{
	if (isOpend())
	{
		string di = GetNow() + str;
		m_info_log << di << endl;
		cout << di << "->INFO.log" << endl;
		OutputDebugPrintf(di.c_str());
	}
}

void GLOG::ERROR_LOG(std::string str)
{
	if (isOpend())
	{
		string di = GetNow() + str;
		m_error_log << di << endl;
		cout << di << "->ERROR.log" << endl;
		OutputDebugPrintf(di.c_str());
	}
}

bool GLOG::isOpend()
{
	bool flag1 = m_info_log.is_open();
	bool flag2 = m_error_log.is_open();
	if (flag1&&flag2)
		return true;
	else
		return false;
}

std::string GLOG::GetNow()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	string yyyy = getStringFromInt(time.wYear, 4);
	string mm = getStringFromInt(time.wMonth, 2);
	string dd = getStringFromInt(time.wDay, 2);
	string hh = getStringFromInt(time.wHour, 2);
	string ff = getStringFromInt(time.wMinute, 2);
	string ss = getStringFromInt(time.wSecond, 2);
	string ms = getStringFromInt(time.wMilliseconds, 3);
	string result = yyyy + "-" + mm + "-" + dd + " " + hh + ":" + ff + ":" + ss + "." + ms + ": ";
	return result;
}

bool GLOG::ClearLogFile()
{
	GLOG_end_();
	if (!isOpend())
	{
		m_info_log.open(m_info_log_file);
		m_error_log.open(m_error_log_file);
		return isOpend();
	}
}

std::string GLOG::getStringFromInt(int num, int n)
{
	string result = to_string(num);
	while (result.length()<n)
	{
		result = "0" + result;
	}
	return result;
}

void GLOG::MBCS_Printf(const char * strOutputString)
{
	OutputDebugStringA(strOutputString);
}

void GLOG::UNICODE_Printf(const wchar_t * strOutputString)
{
	OutputDebugStringW(strOutputString);
}

void GLOG::OutputDebugPrintf(const char *strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	va_end(vlArgs);
	switch (g_type)
	{
	case(CH_UNICODE):
		UNICODE_Printf(CA2W(strOutputString));
		//MBCS_Printf(strOutputString);
		cout << strOutputString;
		break;
	case(CH_MBCS):
		MBCS_Printf(strOutputString);
		cout << strOutputString;
		break;
	default:
		break;
	}
}