#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
//#ifndef _LOAD_LIB_
#ifdef _DEBUG
#pragma comment(lib, "../lib/opencv_world310d.lib")
#else
#pragma comment(lib, "../lib/opencv_world310.lib")
#endif // _DEBUG
//#define _LOAD_LIB_
//#endif // _LOAD_LIB_

#define _XML_FILE_NAME_	"ROI.xml"

enum ROI_SUNTYPE
{
	CIRCLE_ROI,
	ANNULUS_ROI,
	RECTANGLE_ROI,
	RING_ROI,
	ELLIPSE_ROI,
	ROTATEDRECT_ROI,
	POLYGON_ROI,
};

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

class __declspec(dllexport) ROI
{
public:
	ROI();
	~ROI();
	//读取XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	//写XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//主函数bool Excute();
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	//m_Circle_
	CvPoint	m_Circle_Center;
	int m_Circle_Radius;
	bool m_Circle_Division;
	CvSize m_Circle_Resize;
	//m_Annulus_
	CvPoint m_Annulus_Center;
	int m_Annulus_Radius_Min, m_Annulus_Radius_Max;
	bool m_Annulus_Division;
	CvSize m_Annulus_Resize;
	//m_Rectangl_
	CvRect m_Rectangl_Rect;
	bool m_Rectangl_Division;
	CvSize m_Rectangl_Resize;
	//m_Ring_
	CvRect m_Ring_Rect_Min, m_Ring_Rect_Max;
	bool m_Ring_Division;
	CvSize m_Ring_Resize;
	//m_Ellipse_
	cv::RotatedRect m_Ellipse;
	bool m_Ellipse_Division;
	CvSize m_Ellipse_Resize;
	//m_RotateRect_
	CvBox2D m_RotateRect;
	bool m_RotateRect_Division;
	CvSize m_RotateRect_Resize;
	//m_Polygon_
	std::vector<int> m_Polygon_X;
	std::vector<int> m_Polygon_Y;
	bool m_Polygon_Division;
	CvSize m_Polygon_Resize;
private:
	//矩形
	int RectangleROI(cv::Mat src, cv::Mat &dst);
	//矩形环
	int RingROI(cv::Mat src, cv::Mat &dst);
	//圆形
	int CircleROI(cv::Mat src, cv::Mat &dst);
	//圆环
	int AnnulusROI(cv::Mat src, cv::Mat &dst);
	//椭圆
	int EllipseROI(cv::Mat src, cv::Mat &dst);
	//旋转矩形
	int RotateRectROI(cv::Mat src, cv::Mat &dst);
	//多边形
	int PolygonROI(cv::Mat src, cv::Mat &dst);
	//获取有效区域
	int GetRect(cv::Mat src, CvRect &rect);
	//确定是否分割
	int DivisionResize(cv::Mat src, cv::Mat mask, cv::Mat &dst, bool bDivision = false, CvSize size = cvSize(0, 0));
	//比较两个CvRect
	int CompareRect(CvRect &rect_min, CvRect &rect_max);
	//绘制旋转矩形
	void DrawBox(CvBox2D box, cv::Mat &dst);
	//绘制填充得旋转矩形
	void DrawFillBox(cv::Mat &img, cv::RotatedRect box);
};

