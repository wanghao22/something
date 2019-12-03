#include "stdafx.h"
#include "StrChange.h"
using namespace std;

int StrChange::GetStrLen(const char* str)
{
	return strlen(str);
}

int StrChange::GetStrLen(std::string str)
{
	return str.length();
}

int StrChange::GetStrLen(const wchar_t* str)
{
	return lstrlenW(str);
}

int StrChange::GetStrLen(std::wstring str)
{
	return str.length();
}

int StrChange::GetStrLen(CString str)
{
	return str.GetLength();
}


char* StrChange::StrChangec(std::string str)
{
	int sum = str.length();
	char* ff = new char[sum];
	for (int i = 0; i < sum; i++)
	{
		ff[i] = str[i];
	}
	ff[sum] = '\0';
	return ff;
}

char* StrChange::StrChangec(CString str)
{
	std::string p = CW2A(str);
	int sum = p.length();
	char* pt = new char[p.length()];
	for (int i = 0; i < sum; i++)
	{
		pt[i] = p[i];
	}
	pt[sum] = '\0';
	return pt;
}

char* StrChange::StrChangec(const wchar_t* str)
{
	int wlen = GetStrLen(str);
	char* result = new char[wlen + 1];
	sprintf_s(result, wlen + 1, "%ws", str);
	return result;
}

char* StrChange::StrChangec(std::wstring str)
{
	return StrChangec(str.c_str());
}

std::string StrChange::StrChanges(const char* str)
{
	return str;
}

std::string StrChange::StrChanges(CString str)
{
	char* p = StrChangec(str);
	return p;
}

std::string StrChange::StrChanges(const wchar_t* str)
{
	return StrChangec(str);
}

std::string StrChange::StrChanges(std::wstring str)
{
	return StrChangec(str.c_str());
}

CString StrChange::StrChangeC(const char* str)
{
	return (CString)str;
}

CString StrChange::StrChangeC(std::string str)
{
	return (CString)str.c_str();
}

CString StrChange::StrChangeC(const wchar_t* str)
{
	char* strl = StrChangec(str);
	return StrChangeC(strl);
}

CString StrChange::StrChangeC(std::wstring str)
{
	char* strl = StrChangec(str);
	return StrChangeC(strl);
}

wchar_t* StrChange::StrChangewc(const char* str)
{
	int len = GetStrLen(str);
	wchar_t* result = new wchar_t[len + 1];
	swprintf_s(result, len + 1, L"%hs", str);
	return result;
}

wchar_t* StrChange::StrChangewc(std::string str)
{
	char* strl = StrChangec(str);
	return StrChangewc(strl);
}

wchar_t* StrChange::StrChangewc(std::wstring str)
{
	char* strl = StrChangec(str);
	return StrChangewc(strl);
}

wchar_t* StrChange::StrChangewc(CString str)
{
	char* strl = StrChangec(str);
	return StrChangewc(strl);
}

std::wstring StrChange::StrChangews(const char* str)
{
	int len = GetStrLen(str);
	wchar_t* result = new wchar_t[len + 1];
	swprintf_s(result, len + 1, L"%hs", str);
	return result;
}

std::wstring StrChange::StrChangews(std::string str)
{
	char* strl = StrChangec(str);
	return StrChangewc(strl);
}

std::wstring StrChange::StrChangews(const wchar_t* str)
{
	char* strl = StrChangec(str);
	return StrChangewc(strl);
}

std::wstring StrChange::StrChangews(CString str)
{
	char* strl = StrChangec(str);
	return StrChangewc(strl);
}

char* StrChange::atoc(int d)
{
	std::string pt = to_string(d);
	char* pl = StrChangec(pt);
	return pl;
}

char* StrChange::atoc(float f)
{
	std::string pt = to_string(f);
	char* pl = StrChangec(pt);
	return pl;
}

char* StrChange::atoc(double f)
{
	std::string pt = to_string(f);
	char* pl = StrChangec(pt);
	return pl;
}

wchar_t* StrChange::atowc(int d)
{
	std::string pt = to_string(d);
	return StrChangewc(pt);
}

wchar_t* StrChange::atowc(float f)
{
	std::string pt = to_string(f);
	return StrChangewc(pt);
}

wchar_t* StrChange::atowc(double f)
{
	std::string pt = to_string(f);
	return StrChangewc(pt);
}

CString StrChange::atocs(int d)
{
	CString ccc; ccc.Format(L"%d", d);
	return ccc;
}

CString StrChange::atocs(float f)
{
	CString ccc; ccc.Format(L"%f", f);
	return ccc;
}

CString StrChange::atocs(double f)
{
	CString ccc; ccc.Format(L"%f", f);
	return ccc;
}
