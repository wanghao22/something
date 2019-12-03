#pragma once
#include <iostream>
#include <vector>
#include <io.h>

namespace FindFile {

	__declspec(dllexport) void __stdcall findFile(std::string path, std::vector<std::string> &res, 
		bool down_flag = true);

	__declspec(dllexport) void __stdcall findDir(std::string path, std::vector<std::string> &res,
		bool down_flag = true);
}