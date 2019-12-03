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

#define _SHAPE_XML_	"Shape.xml"

enum Dection_Process
{
	HOUGH_CIRCLE_DECT,
	MATCH_CIRCLE_DECT,
	ELLIPSE_DECT,
	HOUGH_LINE_DECT,
	MATCH_LINE_DECT,
	RECTANGLE_DECT,
	CROSS_DECT
};

class __declspec(dllexport) Shape
{
public:
	Shape();
	~Shape();
	//主函数
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//写XML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//读XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	//m_HouCir_
	int m_HouCir_Method, m_HouCir_Thickness;
	int m_HouCir_Minr, m_HouCir_Maxr;
	cv::Scalar m_HouCir_Color;
	double m_HouCir_Dp, m_HouCir_Mindist;
	double m_HouCir_Thre, m_HouCir_Vote;
	//m_MatCir_
	int m_MatCir_Cmin, m_MatCir_Cmax;
	int m_MatCir_Thickness;
	double m_MatCir_Degree;
	cv::Scalar m_MatCir_Color;
	//m_Ellipse_
	int m_Ellipse_Cmin, m_Ellipse_Cmax, m_Ellipse_Scale, m_Ellipse_Thickness;
	cv::Scalar m_Ellipse_Color;
	//m_HouLine_
	int m_HouLine_Cmin, m_HouLine_Cmax;
	bool m_HouLine_P;
	double m_HouLine_Rho, m_HouLine_Theta;
	int m_HouLine_Thre, m_HouLine_Thickness;
	double m_HouLine_LineLen, m_HouLine_LineGap;
	cv::Scalar m_HouLine_Color;
	//m_MatLine_
	int m_MatLine_Cmin, m_MatLine_Cmax;
	int m_MatLine_Dtype, m_MatLine_Thickness;
	double m_MatLine_C, m_MatLine_Reps, m_MatLine_Aeps;
	cv::Scalar m_MatLine_Color;
	//m_Rectangle_
	int m_Rectangle_Thickness, m_Rectangle_Cmin, m_Rectangle_Cmax;
	double m_Rectangle_Minarea, m_Rectangle_Maxcos;
	cv::Scalar m_Rectangle_Color;
	//m_Cross_
	int m_Cross_Cmin, m_Cross_Cmax, m_Cross_Thre;
	double m_Cross_Rho, m_Cross_Theta, m_Cross_Linlen, m_Cross_LineGap;
	double m_Cross_Mindist, m_Cross_Mingap, m_Cross_Maxrot;
	int m_Cross_Maxpix, m_Cross_Thickness;
	cv::Scalar m_Cross_Color;
private:
	//霍夫圆检测
	int HoughCircleDect(cv::Mat src, cv::Mat &dst);
	//拟合圆检测
	int MatchCircleDect(cv::Mat src, cv::Mat &dst);
	//椭圆检测
	int EllipseDect(cv::Mat src, cv::Mat &dst);
	//霍夫直线检测
	int HoughLineDect(cv::Mat src, cv::Mat &dst);
	//拟合直线检测
	int MatchLineDect(cv::Mat src, cv::Mat &dst);
	//矩形检测
	int RectangleDect(cv::Mat src, cv::Mat &dst);
	//十字检测
	int CrossDect(cv::Mat src, cv::Mat &dst);
	//拟合圆
	int CircleInfo2(std::vector<cv::Point> pts, cv::Point2d& center, double& radius);
	int fitCircle(std::vector<cv::Point>& contour, cv::Point2f& centor, double& radius, double &match_val);
	//获取角度
	double getAngle(cv::Point OutPt1, cv::Point ClosePt, cv::Point OutPt2);
	//获取两点之间的距离
	double getDist(cv::Point Pt1, cv::Point Pt2);
	//点斜式绘制直线
	void DrawLineByKP(cv::Mat &src, double k, cv::Point pt, cv::Scalar color, int thinkess);
};

