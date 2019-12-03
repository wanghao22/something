#pragma once
#include "stdafx.h"
#ifndef _STRING_CHANGE_H
#define _STRING_CHANGE_H
#include <iostream>
#include <string>
namespace StrChange
{
	int GetStrLen(const char* str);
	int GetStrLen(std::string str);
	int GetStrLen(const wchar_t* str);
	int GetStrLen(std::wstring str);
	int GetStrLen(CString str);
	char* StrChangec(std::string str);
	char* StrChangec(CString str);
	char* StrChangec(const wchar_t* str);
	char* StrChangec(std::wstring str);
	std::string StrChanges(const char* str);
	std::string StrChanges(CString str);
	std::string StrChanges(const wchar_t* str);
	std::string StrChanges(std::wstring str);
	CString StrChangeC(const char* str);
	CString StrChangeC(std::string str);
	CString StrChangeC(const wchar_t* str);
	CString StrChangeC(std::wstring str);
	wchar_t* StrChangewc(const char* str);
	wchar_t* StrChangewc(std::string str);
	wchar_t* StrChangewc(std::wstring str);
	wchar_t* StrChangewc(CString str);
	std::wstring StrChangews(const char* str);
	std::wstring StrChangews(std::string str);
	std::wstring StrChangews(const wchar_t* str);
	std::wstring StrChangews(CString str);
	char* atoc(int d);
	char* atoc(float f);
	char* atoc(double f);
	wchar_t* atowc(int d);
	wchar_t* atowc(float f);
	wchar_t* atowc(double f);
	CString atocs(int d);
	CString atocs(float f);
	CString atocs(double f);
};

#endif // !_STRING_CHANGE_H


