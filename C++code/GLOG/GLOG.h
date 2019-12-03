#pragma once
#include "atlbase.h"
#include "atlstr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

enum CH_type {
	CH_UNICODE,
	CH_MBCS
};

#ifdef UNICODE
const CH_type g_type = CH_UNICODE;
#else
const CH_type g_type = CH_MBCS;
#endif // UNICODE

class GLOG
{
public:
	GLOG();
	GLOG(std::string lnfo_file, std::string error_file);
	~GLOG();
	void setInfoFile(std::string file) {
		m_info_log_file = file;
	}
	void setErrorFile(std::string file)
	{
		m_error_log_file = file;
	}
	bool GLOG_start_(std::string lnfo_file, std::string error_file);
	bool GLOG_start_();
	void GLOG_end_();
	void INFO_LOG(std::string str);
	void ERROR_LOG(std::string str);
	void OutputDebugPrintf(const char *strOutputString, ...);
	bool isOpend();
	std::string GetNow();
	bool ClearLogFile();
private:
	std::string m_info_log_file;//INFO文件名
	std::string m_error_log_file;//ERROR文件名
	std::ofstream m_info_log;//INFO文件
	std::ofstream m_error_log;//ERROR文件

	std::string getStringFromInt(int num, int n);
	void MBCS_Printf(const char *strOutputString);
	void UNICODE_Printf(const wchar_t *strOutputString);
};

