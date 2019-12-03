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

#define _MATCH_XML_FILE_	"Match.xml"
//Դ������������: UTF-8(BOM)    
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

enum Match_Method
{
	MATCH_GRAY,
	MATCH_PYR,
	MATCH_ROTATE
};

enum Threshold_Background_Color
{
	THRE_BK_BALCK,
	THRE_BK_WHITE
};

class __declspec(dllexport) Match
{
public:
	Match();
	~Match();
	//������
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int method);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int method);
	//дXML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//��XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	//����ģ��
	bool __stdcall SetTemplate(char* file);
	//ͨ��
	std::string m_Templ_Path;
	//m_Gray_
	int m_Gray_Method, m_Gray_Thickness;
	cv::Scalar m_Gray_Color;
	//m_Pyr_
	double m_Pyr_Scale;
	int m_Pyr_Method, m_Pyr_Thickness;
	cv::Scalar m_Pyr_Color;
	//m_Rotate_
	int m_Rotate_Method, m_Rotate_Thickness;
	cv::Scalar m_Rotate_Color;
private:
	//�Ҷ�ƥ��
	int MatchGrayImage(cv::Mat src, cv::Mat &dst);
	//������ƥ��
	int MatchPyrImage(cv::Mat src, cv::Mat &dst);
	//���Ƕ�ƥ��
	int MatchRotateImage(cv::Mat src, cv::Mat &dst);
	//������ת����
	void rotateRect(cv::Mat &dst, cv::RotatedRect box, cv::Scalar color, int thickness = 1);
	cv::Ptr<cv::FeatureDetector> orb = cv::ORB::create();
	cv::BFMatcher matcher;// ����ƥ��
	cv::Mat templ;
};

