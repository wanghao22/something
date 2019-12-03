#include "DirFileOption.h"
using namespace std;

//文件夹或者文件是否存在
bool DirFile::IsExisteDir(string path)
{
	if (-1 != _access(path.c_str(), 0))
	{
		return true;
	}
	return false;
}

//将父文件夹和子文件夹或者子文件合并为一个完整的路径
string DirFile::DirAddSubdir(string path, string subdir)
{
	string dir;
	int d1 = path.find_last_of("\\");
	int d2 = path.find_last_of("/");
	int len = path.length();
	if (d1 == len - 1 || d2 == len - 1)
		dir = path + subdir;
	else
		dir = path + "\\" + subdir;
	return dir;
}

//创建文件夹 完整路径
int DirFile::CreateDir(string dir)
{
	wchar_t wdir[100];
	swprintf_s(wdir, 100, L"%hs", dir.c_str());
	return _wmkdir(wdir);
}

//创建文件夹 组合路径
int DirFile::CreateDir(string path, string subdir)
{
	if (!IsExisteDir(path))
		return -1;
	string dir = DirAddSubdir(path, subdir);
	return CreateDir(dir);
}

//创建文件 完整路径
int DirFile::_CreateFile(string fullname)
{
	fstream file;
	file.open(fullname, ios::out);
	if (!file)
		return -1;
	file.close();
	return 0;
}

//创建文件 组合路径
int DirFile::_CreateFile(string path, string filename)
{
	if (!IsExisteDir(path))
		return -1;
	string dir = DirAddSubdir(path, filename);
	return _CreateFile(dir);
}

//文件/文件夹 重命名 完整路径
int DirFile::RenameDirFile(string dir, string newdir)
{
	if (!IsExisteDir(dir))
		return -1;
	if (IsExisteDir(newdir))
		DeleteDir(newdir);
	return rename(dir.c_str(), newdir.c_str());
}

//文件/文件夹 重命名 组合路径
int DirFile::RenameDirFile(string fadir, string subdir, string newsubdir)
{
	string dir = DirAddSubdir(fadir, subdir);
	string newdir = DirAddSubdir(fadir, newsubdir);
	return RenameDirFile(dir, newdir);
}

//文件 删除 完整路径
int DirFile::_DeleteFile(string fullname)
{
	if (!IsExisteDir(fullname))
		return -1;
	return remove(fullname.c_str());
}

//文件 删除 组合路径
int DirFile::_DeleteFile(string dir, string filename)
{
	string fullpath = DirAddSubdir(dir, filename);
	return _DeleteFile(fullpath);
}

//文件夹 删除 完整路径
int DirFile::DeleteDir(string dir)
{
	if (!IsExisteDir(dir))
		return -1;
	string cmd = "rd /s/q " + dir;
	system(cmd.c_str());
	return 0;
}

//文件夹 删除 组合路径
int DirFile::DeleteDir(string dir, string subdir)
{
	string fullpath = DirAddSubdir(dir, subdir);
	return DeleteDir(fullpath);
}

//返回上一级的路径
std::string DirFile::GetFatherDir(std::string str)
{
	string dir;
	int d1 = str.find_last_of("\\");
	int d2 = str.find_last_of("/");
	int len = str.length();
	if (d1 == len - 1 || d2 == len - 1)
		dir = str.substr(0,len-1);
	else
		dir = str;
	d1 = dir.find_last_of("\\");
	d2 = dir.find_last_of("/");
	dir = dir.substr(0, max(d1, d2));
	return dir;
}

//移动文件 
void DirFile::MoveDirFiles(std::string pathA, std::string pathB)
{
	string cmd = "move " + pathA + " " + pathB;
	system(cmd.c_str());
}

//移动文件 
void DirFile::MoveDirFiles(std::string pathA, std::string pathA_sub, std::string pathB)
{
	string fullpathA = DirAddSubdir(pathA, pathA_sub);
	MoveDirFiles(fullpathA, pathB);
}

//复制文件
void DirFile::CopyDirFiles(std::string pathA, std::string pathB)
{
	string cmd = "copy " + pathA + " " + pathB;
	system(cmd.c_str());
}

//复制文件
void DirFile::CopyDirFiles(std::string pathA, std::string pathA_sub, std::string pathB)
{
	string fullpathA = DirAddSubdir(pathA, pathA_sub);
	CopyDirFiles(fullpathA, pathB);
}
