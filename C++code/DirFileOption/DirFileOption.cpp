#include "stdafx.h"
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

//������������char*תwchar_t*
CString DirFile::zhToCString(std::string str)
{
	//����char *�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�
	int charLen = str.length();
	//������ֽ��ַ��Ĵ�С�����ַ����㡣
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), charLen, NULL, 0);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
	TCHAR *buf = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), charLen, buf, len);
	buf[len] = '\0'; //����ַ�����β��ע�ⲻ��len+1
					 //��TCHAR����ת��ΪCString
	CString pWideChar;
	pWideChar.Append(buf);
	//ɾ��������
	delete[]buf;
	return pWideChar;
}

//�����ļ��� ����·��
int DirFile::CreateDir(string dir)
{
	CString pWideChar = zhToCString(dir);
	return _wmkdir(pWideChar);
}

int DirFile::CreateDir(CString dir)
{
	return _wmkdir(dir);
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
