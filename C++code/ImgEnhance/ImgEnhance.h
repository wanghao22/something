#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <io.h>
#include "DirFileOption.h"

#define _ENHANCE_XML_ "Enhance.xml"

#define _TRAIN_CMD_ "train_val.cmd"

class ImgEnhance
{
public:
	ImgEnhance();
	~ImgEnhance();
	void Enhance();
	void LoadImages(std::string path);
	void AddImage(std::vector<std::string> filenames);
	void AddImage(std::string filename);
	int SaveXML();
	int LoadXML();
	//��ʼѵ��
	void TrainStart(std::string out_dir);
	void CmdTrainStart(std::string out_dir);
	void SetCaffeToolsDir(std::string caffe_tools)
	{
		caffe_tools_dir = caffe_tools;
	}
	bool m_Flag_Rotate;//��ת
	bool m_Flag_Rotate90;//��ת90��
	bool m_Flag_FlipX;//X�ᷭת
	bool m_Flag_FlipY;//Y�ᷭת
	bool m_Flag_FlipXY;//XY�ᷭת
	bool m_Flag_Crop;//�޼�
	bool m_Flag_Blur;//�˲�
	bool m_Flag_Contrast;//��������
	bool m_Flag_Brightness;//��������
	bool m_Flag_Noise;//�����
	bool m_Flag_Sharpen;//��
	int m_Rotate_Step;
	double m_Crop_Scale;//�������ӣ�0.5~0.9��
	int m_Contrast_Max;
	int m_Contrast_Step;
	int m_Brightness_Max;
	int m_Brightness_Step;
	bool m_Other_Path_Flag;//�Ƿ񱣴�������λ��
	double m_Sharpen_Thre;
	double m_Sharpen_Amount;
	int m_Val_Scale;//��֤���Ĵ�С��ǧ��֮��
	std::string m_Other_Path;//����λ��
	std::vector<std::string> m_fullpath;//Դͼ���ȫ·��
	std::vector<cv::Mat> m_imgs;//Դͼ��
	std::vector<std::string> path;//·��
	std::vector<std::string> name;//����
	std::vector<std::string> type;//��׺
	std::vector<cv::Mat> m_enhance_imgs;//��ǿ��ͼ��
	std::vector<std::string> m_enhance_fpath;//��ǿ��ͼ���ȫ·��
	std::string this_dir;
private:
	std::string caffe_tools_dir;//Caffe����·��
	//�������е��ļ�
	void findFile(std::string path, std::vector<std::string>& res);
	//��������·���ָ�ɣ�·�����ļ������ļ���׺��
	int PathDevision(std::string str, std::string &path, std::string &name, std::string &type);
	//��ת�������
	void Do_rotate(cv::Mat src, cv::Mat &dst, double angle);
	//�����Ⱦ������
	void Do_Vintensity(cv::Mat src, cv::Mat &dst, int value);
	//�񻯾������
	void Do_Sharpen(cv::Mat src, cv::Mat &dst, double threshold, double amount);
	//��ת
	int IRotate();
	int IRotate90();
	//��ת
	int IFlipX();
	int IFlipY();
	int IFlipXY();
	//�޼�
	int ICrop();
	//�˲�
	int IBlur();
	//�����ȵ���
	int IContrast();
	int IBrightness();
	//�������
	int INoise();
	//��
	int ISharpen();
	//����txt�ļ�
	void ClassifyTrainVal();
	//�����ȡ���ļ���
	std::string ClassifyFloder(std::string str);
	//ͨ��ȫ·����ȡҪд��txt�ļ��е�����
	void GiveTxtInfo(std::string fullpath, bool &train_flag, int &info, std::string &filename);
};

