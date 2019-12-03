#pragma once
#include <io.h>
#include <fstream>
#include <iostream>
#include <string>

namespace DirFile {
	//�ļ��л����ļ��Ƿ����
	bool IsExisteDir(std::string path);

	//�����ļ��к����ļ��л������ļ��ϲ�Ϊһ��������·��
	std::string DirAddSubdir(std::string path, std::string subdir);

	//�����ļ��� ����·��
	int CreateDir(std::string dir);

	//�����ļ��� ���·��
	int CreateDir(std::string path, std::string subdir);

	//�����ļ� ����·��
	int _CreateFile(std::string fullname);

	//�����ļ� ���·��
	int _CreateFile(std::string path, std::string filename);

	//�ļ�/�ļ��� ������ ����·��
	int RenameDirFile(std::string dir, std::string newdir);

	//�ļ�/�ļ��� ������ ���·��
	int RenameDirFile(std::string fadir, std::string subdir, std::string newsubdir);

	//�ļ� ɾ�� ����·��
	int _DeleteFile(std::string fullname);

	//�ļ� ɾ�� ���·��
	int _DeleteFile(std::string dir, std::string filename);

	//�ļ��� ɾ�� ����·��
	int DeleteDir(std::string dir);

	//�ļ��� ɾ�� ���·��
	int DeleteDir(std::string dir, std::string subdir);

	//������һ����·��
	std::string GetFatherDir(std::string str);

	//�ƶ��ļ� 
	void MoveDirFiles(std::string pathA, std::string pathB);

	//�ƶ��ļ� 
	void MoveDirFiles(std::string pathA, std::string pathA_sub, std::string pathB);

	//�����ļ�
	void CopyDirFiles(std::string pathA, std::string pathB);

	//�����ļ�
	void CopyDirFiles(std::string pathA, std::string pathA_sub, std::string pathB);
}