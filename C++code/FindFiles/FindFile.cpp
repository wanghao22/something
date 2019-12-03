#include "FindFile.h"

using namespace std;

__declspec(dllexport) void __stdcall FindFile::findFile(std::string path, std::vector<std::string>& res, bool down_flag)
{
	string p;
	intptr_t hFile = 0;             
	struct _finddata_t fileinfo; 
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != 0)
	{
		do
		{
			string path_s = p.assign(path).append("\\").append(fileinfo.name);
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;
			if (fileinfo.attrib == _A_SUBDIR || fileinfo.attrib == _A_HIDDEN)
			{
				//遍历子目录
				if (down_flag)
				{
					std::vector<std::string> temp;
					findFile(path_s, temp);
					for (size_t i = 0; i < temp.size(); i++)
						res.push_back(temp[i]);
				}
				continue;
			}
			res.push_back(path_s);            //插入容器
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);    //关闭文件
	}
}

__declspec(dllexport) void __stdcall FindFile::findDir(std::string path, std::vector<std::string>& res, bool down_flag)
{
	string p;
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != 0)
	{
		do
		{
			string path_s = p.assign(path).append("\\").append(fileinfo.name);
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;
			if (fileinfo.attrib == _A_SUBDIR || fileinfo.attrib == _A_HIDDEN)
			{
				//遍历子目录
				if (down_flag)
				{
					std::vector<std::string> temp;
					findFile(path_s, temp);
					for (size_t i = 0; i < temp.size(); i++)
						res.push_back(temp[i]);
				}
				res.push_back(path_s);
				continue;
			}         //插入容器
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);    //关闭文件
	}
}
