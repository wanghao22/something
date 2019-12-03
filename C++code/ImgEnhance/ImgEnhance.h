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
	//开始训练
	void TrainStart(std::string out_dir);
	void CmdTrainStart(std::string out_dir);
	void SetCaffeToolsDir(std::string caffe_tools)
	{
		caffe_tools_dir = caffe_tools;
	}
	bool m_Flag_Rotate;//旋转
	bool m_Flag_Rotate90;//旋转90°
	bool m_Flag_FlipX;//X轴翻转
	bool m_Flag_FlipY;//Y轴翻转
	bool m_Flag_FlipXY;//XY轴翻转
	bool m_Flag_Crop;//修剪
	bool m_Flag_Blur;//滤波
	bool m_Flag_Contrast;//降低亮度
	bool m_Flag_Brightness;//提升亮度
	bool m_Flag_Noise;//加噪点
	bool m_Flag_Sharpen;//锐化
	int m_Rotate_Step;
	double m_Crop_Scale;//缩放因子（0.5~0.9）
	int m_Contrast_Max;
	int m_Contrast_Step;
	int m_Brightness_Max;
	int m_Brightness_Step;
	bool m_Other_Path_Flag;//是否保存在输入位置
	double m_Sharpen_Thre;
	double m_Sharpen_Amount;
	int m_Val_Scale;//验证集的大小（千分之）
	std::string m_Other_Path;//输入位置
	std::vector<std::string> m_fullpath;//源图像的全路径
	std::vector<cv::Mat> m_imgs;//源图像
	std::vector<std::string> path;//路径
	std::vector<std::string> name;//名称
	std::vector<std::string> type;//后缀
	std::vector<cv::Mat> m_enhance_imgs;//增强的图像
	std::vector<std::string> m_enhance_fpath;//增强的图像的全路径
	std::string this_dir;
private:
	std::string caffe_tools_dir;//Caffe工具路径
	//遍历所有的文件
	void findFile(std::string path, std::vector<std::string>& res);
	//把完整的路径分割成：路径、文件名、文件后缀。
	int PathDevision(std::string str, std::string &path, std::string &name, std::string &type);
	//旋转具体操作
	void Do_rotate(cv::Mat src, cv::Mat &dst, double angle);
	//明暗度具体操作
	void Do_Vintensity(cv::Mat src, cv::Mat &dst, int value);
	//锐化具体操作
	void Do_Sharpen(cv::Mat src, cv::Mat &dst, double threshold, double amount);
	//旋转
	int IRotate();
	int IRotate90();
	//翻转
	int IFlipX();
	int IFlipY();
	int IFlipXY();
	//修剪
	int ICrop();
	//滤波
	int IBlur();
	//明暗度调节
	int IContrast();
	int IBrightness();
	//添加噪声
	int INoise();
	//锐化
	int ISharpen();
	//生成txt文件
	void ClassifyTrainVal();
	//随机获取子文件夹
	std::string ClassifyFloder(std::string str);
	//通过全路径获取要写到txt文件中的内容
	void GiveTxtInfo(std::string fullpath, bool &train_flag, int &info, std::string &filename);
};

