#include "DirFileOption.h"
using namespace std;

//�ļ��л����ļ��Ƿ����
bool DirFile::IsExisteDir(string path)
{
	if (-1 != _access(path.c_str(), 0))
	{
		return true;
	}
	return false;
}

//�����ļ��к����ļ��л������ļ��ϲ�Ϊһ��������·��
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

//�����ļ��� ����·��
int DirFile::CreateDir(string dir)
{
	wchar_t wdir[100];
	swprintf_s(wdir, 100, L"%hs", dir.c_str());
	return _wmkdir(wdir);
}

//�����ļ��� ���·��
int DirFile::CreateDir(string path, string subdir)
{
	if (!IsExisteDir(path))
		return -1;
	string dir = DirAddSubdir(path, subdir);
	return CreateDir(dir);
}

//�����ļ� ����·��
int DirFile::_CreateFile(string fullname)
{
	fstream file;
	file.open(fullname, ios::out);
	if (!file)
		return -1;
	file.close();
	return 0;
}

//�����ļ� ���·��
int DirFile::_CreateFile(string path, string filename)
{
	if (!IsExisteDir(path))
		return -1;
	string dir = DirAddSubdir(path, filename);
	return _CreateFile(dir);
}

//�ļ�/�ļ��� ������ ����·��
int DirFile::RenameDirFile(string dir, string newdir)
{
	if (!IsExisteDir(dir))
		return -1;
	if (IsExisteDir(newdir))
		DeleteDir(newdir);
	return rename(dir.c_str(), newdir.c_str());
}

//�ļ�/�ļ��� ������ ���·��
int DirFile::RenameDirFile(string fadir, string subdir, string newsubdir)
{
	string dir = DirAddSubdir(fadir, subdir);
	string newdir = DirAddSubdir(fadir, newsubdir);
	return RenameDirFile(dir, newdir);
}

//�ļ� ɾ�� ����·��
int DirFile::_DeleteFile(string fullname)
{
	if (!IsExisteDir(fullname))
		return -1;
	return remove(fullname.c_str());
}

//�ļ� ɾ�� ���·��
int DirFile::_DeleteFile(string dir, string filename)
{
	string fullpath = DirAddSubdir(dir, filename);
	return _DeleteFile(fullpath);
}

//�ļ��� ɾ�� ����·��
int DirFile::DeleteDir(string dir)
{
	if (!IsExisteDir(dir))
		return -1;
	string cmd = "rd /s/q " + dir;
	system(cmd.c_str());
	return 0;
}

//�ļ��� ɾ�� ���·��
int DirFile::DeleteDir(string dir, string subdir)
{
	string fullpath = DirAddSubdir(dir, subdir);
	return DeleteDir(fullpath);
}

//������һ����·��
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

//�ƶ��ļ� 
void DirFile::MoveDirFiles(std::string pathA, std::string pathB)
{
	string cmd = "move " + pathA + " " + pathB;
	system(cmd.c_str());
}

//�ƶ��ļ� 
void DirFile::MoveDirFiles(std::string pathA, std::string pathA_sub, std::string pathB)
{
	string fullpathA = DirAddSubdir(pathA, pathA_sub);
	MoveDirFiles(fullpathA, pathB);
}

//�����ļ�
void DirFile::CopyDirFiles(std::string pathA, std::string pathB)
{
	string cmd = "copy " + pathA + " " + pathB;
	system(cmd.c_str());
}

//�����ļ�
void DirFile::CopyDirFiles(std::string pathA, std::string pathA_sub, std::string pathB)
{
	string fullpathA = DirAddSubdir(pathA, pathA_sub);
	CopyDirFiles(fullpathA, pathB);
}
