#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "../lib/opencv_world310d.lib")
#else
#pragma comment(lib, "../lib/opencv_world310.lib")
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
#ifndef _NO_DECTION_
#define _NO_DECTION_		-5
#endif

#define _TRANS_XML_FILE_	"Transformation.xml"

enum Trans_op
{
	TRANS_ROTATE,
	TRANS_FLIP,
	TRANS_CUT,
	TRANS_DILATE,//膨胀
	TRANS_ERODE,//腐蚀
	TRANS_ENHANCE,
	TRANS_MEAN_SHIFT,//均值漂移
	TRANS_HIST,//直方图
	TRANS_GUASSIAN,
	TRANS_RESIZE_ROTATE
};

class __declspec(dllexport) Transformation
{
public:
	Transformation();
	~Transformation();
	//主函数
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//写XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//读XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	int m_Rotate_Angle;//旋转角度
	int m_Filp_flag;//翻转方法(<0:x+y; ==0:x; >0:y)
	CvRect m_Cut_Size;//裁剪尺寸
	int m_Resize_Rotate_Angle;//缩放旋转角度
private:
	//旋转
	int tRotate(cv::Mat src, cv::Mat &dst);
	//翻转
	int tFlip(cv::Mat src, cv::Mat &dst);
	//裁剪
	int tCut(cv::Mat src, cv::Mat &dst);
	//腐蚀
	int tDilate(cv::Mat src, cv::Mat &dst);
	//膨胀
	int tErode(cv::Mat src, cv::Mat &dst);
	//图像增强
	void LogEnhance(IplImage *src, IplImage *dst);
	int tEnhance(cv::Mat src, cv::Mat &dst);
	//均值漂移分割
	int tMeanShift(cv::Mat src, cv::Mat &dst);
	//直方图
	int tHist(cv::Mat src, cv::Mat &dst);
	//高斯模糊
	int tGaussianBlur(cv::Mat src, cv::Mat &dst);
	//缩放旋转
	int tResizeRotate(cv::Mat src, cv::Mat &dst);
};

