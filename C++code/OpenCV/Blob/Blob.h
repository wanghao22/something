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

#define _BLOB_XML_FILE_		"Blob.xml"

enum BLOB_SUNTYPE
{
	DRAW_CONTOURS,
	DRAW_CONTOURS_CVBOX
};

class __declspec(dllexport) Blob
{
public:
	Blob();
	~Blob();
	//主函数
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//写入XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//读取XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	//m_Contour_
	int m_Contour_Thre, m_Contour_BlurSize;
	int m_Contour_Mode, m_Contour_Thickness;
	cv::Scalar m_Contour_Color;
	//m_CvBox_
	int m_CvBox_Thre, m_CvBox_BlurSize;
	int m_CvBox_Mode, m_CvBox_Thickness;
	cv::Scalar m_CvBox_Color;
private:
	//绘制轮廓
	int DrawContours(cv::Mat src, cv::Mat &dst);
	//绘制轮廓的外界矩形
	int DrawContourRotateRect(cv::Mat src, cv::Mat &dst);
	//绘制旋转矩形
	void DrawBox(CvBox2D box, cv::Mat &dst, cv::Scalar color);
};

/*
void cvThreshold(const CvArr* src, CvArr* dst, double threshold, double max_value, int threshold_type);

threshold_type=CV_THRESH_BINARY:如果 src(x,y)>threshold ,dst(x,y) = max_value; 否则,dst(x,y)=0;			黑色背景找白色
threshold_type=CV_THRESH_BINARY_INV:如果 src(x,y)>threshold,dst(x,y) = 0; 否则,dst(x,y) = max_value.	白色背景找黑色
threshold_type=CV_THRESH_TRUNC:如果 src(x,y)>threshold，dst(x,y) = max_value; 否则dst(x,y) = src(x,y).
threshold_type=CV_THRESH_TOZERO:如果src(x,y)>threshold，dst(x,y) = src(x,y) ; 否则 dst(x,y) = 0。
threshold_type=CV_THRESH_TOZERO_INV:如果 src(x,y)>threshold，dst(x,y) = 0 ; 否则dst(x,y) = src(x,y).
*/