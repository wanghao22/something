#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
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

#define _DIST_XML_FILE_	"Distance.xml"

enum Distance_Process
{
	POINT_2_POINT,
	POINT_2_LINE,
	LINE_2_LINE
};

class __declspec(dllexport) Distance
{
public:
	Distance();
	~Distance();
	//Ö÷º¯Êý
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst,int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//Ð´XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//¶ÁXML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	//m_pt2pt_
	CvPoint m_pt2pt_ptS, m_pt2pt_ptE;
	bool m_pt2pt_AFlag;
	double m_pt2pt_Angle, m_pt2pt_Result;
	//m_pt2ln_
	CvPoint m_pt2ln_ptS, m_pt2ln_lnS, m_pt2ln_lnE;
	bool m_pt2ln_AFlag;
	double m_pt2ln_Angle, m_pt2ln_Result;
	//m_ln2ln_
	CvPoint m_ln2ln_lnSS, m_ln2ln_lnSE, m_ln2ln_lnES, m_ln2ln_lnEE;
	double m_ln2ln_Gap, m_ln2ln_Result;
private:
	//Point2Point
	int CalcPt2PtDist(cv::Mat src, cv::Mat &dst);
	//Point2Line
	int CalcPt2LnDist(cv::Mat src, cv::Mat &dst);
	//Line2Line
	int CalcLn2LnDist(cv::Mat src, cv::Mat &dst);
};

