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
	//������
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//д��XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//��ȡXML
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
	//��������
	int DrawContours(cv::Mat src, cv::Mat &dst);
	//����������������
	int DrawContourRotateRect(cv::Mat src, cv::Mat &dst);
	//������ת����
	void DrawBox(CvBox2D box, cv::Mat &dst, cv::Scalar color);
};

/*
void cvThreshold(const CvArr* src, CvArr* dst, double threshold, double max_value, int threshold_type);

threshold_type=CV_THRESH_BINARY:��� src(x,y)>threshold ,dst(x,y) = max_value; ����,dst(x,y)=0;			��ɫ�����Ұ�ɫ
threshold_type=CV_THRESH_BINARY_INV:��� src(x,y)>threshold,dst(x,y) = 0; ����,dst(x,y) = max_value.	��ɫ�����Һ�ɫ
threshold_type=CV_THRESH_TRUNC:��� src(x,y)>threshold��dst(x,y) = max_value; ����dst(x,y) = src(x,y).
threshold_type=CV_THRESH_TOZERO:���src(x,y)>threshold��dst(x,y) = src(x,y) ; ���� dst(x,y) = 0��
threshold_type=CV_THRESH_TOZERO_INV:��� src(x,y)>threshold��dst(x,y) = 0 ; ����dst(x,y) = src(x,y).
*/