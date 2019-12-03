#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib,"../lib/opencv_world310d.lib")
#else
#pragma comment(lib,"../lib/opencv_world310.lib")
#endif

#ifndef _NO_IMAGE_
#define _NO_IMAGE_			-1
#endif
#ifndef _PARAM_ERROR_
#define _PARAM_ERROR_		-2
#endif
#ifndef _ROI_OVERTOP_
#define _ROI_OVERTOP_		-3
#endif
#ifndef _OPEN_XML_ERROR_
#define _OPEN_XML_ERROR_	-4
#endif

#define _PIX_PROCESS_XML_	"PixProcess.xml"

enum PIX_PROCESS_SUN_TYPE
{
	THRESHOLD_PROCESS,
	INVERSE_PROCESS,
	CANNY_PROCESS,
	SOBEL_PROCESS,
	LAPLACE_PROCESS,
	SUB_PIX_PROCESS,
	DIVISION_BY_HSV,
	DIVISION_BY_RGB,
	DIVISION_BY_GRAY
};

enum DIVISION_BYE_GRAY
{
	DIVISION_BY_H,
	DIVISION_BY_S,
	DIVISION_BY_V,
	DIVISION_BY_R,
	DIVISION_BY_G,
	DIVISION_BY_B,
	DIVISION_BY_O//表示输入是灰度图
};

class __declspec(dllexport) PixProcess
{
public:
	PixProcess();
	~PixProcess();
	//主函数
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//写入XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//读取XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	//m_Threshold_
	int m_Threshold_Thre, m_Threshold_Mode;
	//m_Canny_
	int m_Canny_BlurSize, m_Canny_Min, m_Canny_Max, m_Canny_Ksize;
	bool m_Canny_Gradient;//是否采用更精确的方式计算图像梯度
	//m_Sobel_
	int m_SobelDepth, m_SobelDx, m_SobelDy, m_SobelKsize, m_SobelType;
	double m_SobelScale, m_SobelDelta;
	//m_Laplace_
	int m_LaplaceGusize, m_LaplaceDepth, m_LaplaceKsize, m_LaplaceType;
	double m_LaplaceScale, m_LaplaceDelta;
	//m_SubPix_
	int m_SubPixSize, m_SubAutoThreMode, m_SubAutoThreType, m_SubAutoThreKsize;
	double m_SubPixC;
	cv::Scalar m_SubPixColor;
	//m_HSV_
	int m_H_min, m_S_min, m_V_min;
	int m_H_max, m_S_max, m_V_max;
	//m_RGB_
	int m_R_min, m_G_min, m_B_min;
	int m_R_max, m_G_max, m_B_max;
	//m_Gray
	int m_Gray_Case, m_Gray_Min, m_Gray_Max;
private:
	//二值化
	int ThresholdPro(cv::Mat src, cv::Mat &dst);
	//边缘检测
	int CannyProcess(cv::Mat src, cv::Mat &dst);
	int SobelProcess(cv::Mat src, cv::Mat &dst);
	int LaplaceProcess(cv::Mat src, cv::Mat &dst);
	//亚像素边缘检测
	int SubPixProcess(cv::Mat src, cv::Mat &dst);
	//HSV分割
	int DivisionByHSV(cv::Mat src, cv::Mat &dst);
	//RGB分割
	int DivisionByRGB(cv::Mat src, cv::Mat &dst);
	//单通道取图
	int DivisionByGray(cv::Mat src, cv::Mat &dst);
	//单通道处理
	int DivisionGrayImage(cv::Mat src, cv::Mat &dst, int min, int max);
};

