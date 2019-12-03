#include "stdafx.h"
#include "Shape.h"

using namespace cv;
using namespace std;

Shape::Shape()
{
	
}


Shape::~Shape()
{
}


bool __stdcall Shape::Excute(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(HOUGH_CIRCLE_DECT):
		if (HoughCircleDect(src, dst) != 0)
			return false;
		return true;
	case(MATCH_CIRCLE_DECT) :
		if (MatchCircleDect(src, dst) != 0)
			return false;
		return true;
	case(ELLIPSE_DECT) :
		if (EllipseDect(src, dst) != 0)
			return false;
		return true;
	case(HOUGH_LINE_DECT) :
		if (HoughLineDect(src, dst) != 0)
			return false;
		return true;
	case(MATCH_LINE_DECT) :
		if (MatchLineDect(src, dst) != 0)
			return false;
		return true;
	case(RECTANGLE_DECT) :
		if (RectangleDect(src, dst) != 0)
			return false;
		return true;
	case(CROSS_DECT) :
		if (CrossDect(src, dst) != 0)
			return false;
		return true;
	default:
		break;
	}
	return true;
}

int __stdcall Shape::Excute_(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(HOUGH_CIRCLE_DECT) :
		return HoughCircleDect(src, dst);
	case(MATCH_CIRCLE_DECT) :
		return MatchCircleDect(src, dst);
	case(ELLIPSE_DECT) :
		return EllipseDect(src, dst);
	case(HOUGH_LINE_DECT) :
		return HoughLineDect(src, dst);
	case(MATCH_LINE_DECT) :
		return MatchLineDect(src, dst);
	case(RECTANGLE_DECT) :
		return RectangleDect(src, dst);
	case(CROSS_DECT) :
		return CrossDect(src, dst);
	default:
		break;
	}
	return 0;
}

int __stdcall Shape::SaveXML()
{
	FileStorage fs(_SHAPE_XML_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//HoughCircleDect
	fs << "HoughCircleDect" << "{" << "name" << "HoughCircleDect" << "type" << 3 << "suntype" << HOUGH_CIRCLE_DECT;
	fs << "m_HouCir_Method" << m_HouCir_Method;
	fs << "m_HouCir_Minr" << m_HouCir_Minr;
	fs << "m_HouCir_Maxr" << m_HouCir_Maxr;
	fs << "m_HouCir_Dp" << m_HouCir_Dp;
	fs << "m_HouCir_Mindist" << m_HouCir_Mindist;
	fs << "m_HouCir_Thre" << m_HouCir_Thre;
	fs << "m_HouCir_Vote" << m_HouCir_Vote;
	fs << "m_HouCir_Thickness" << m_HouCir_Thickness;
	fs << "m_HouCir_Color_R" << m_HouCir_Color[2];
	fs << "m_HouCir_Color_G" << m_HouCir_Color[1];
	fs << "m_HouCir_Color_B" << m_HouCir_Color[0] << "}";
	//MatchCircleDect
	fs << "MatchCircleDect" << "{" << "name" << "MatchCircleDect" << "type" << 3 << "suntype" << MATCH_CIRCLE_DECT;
	fs << "m_MatCir_Cmin" << m_MatCir_Cmin;
	fs << "m_MatCir_Cmax" << m_MatCir_Cmax;
	fs << "m_MatCir_Thickness" << m_MatCir_Thickness;
	fs << "m_MatCir_Degree" << m_MatCir_Degree;
	fs << "m_MatCir_Color_R" << m_MatCir_Color[2];
	fs << "m_MatCir_Color_G" << m_MatCir_Color[1];
	fs << "m_MatCir_Color_B" << m_MatCir_Color[0] << "}";
	//EllipseDect
	fs << "EllipseDect" << "{" << "name" << "EllipseDect" << "type" << 3 << "suntype" << ELLIPSE_DECT;
	fs << "m_Ellipse_Cmin" << m_Ellipse_Cmin;
	fs << "m_Ellipse_Cmax" << m_Ellipse_Cmax;
	fs << "m_Ellipse_Scale" << m_Ellipse_Scale;
	fs << "m_Ellipse_Thickness" << m_Ellipse_Thickness;
	fs << "m_Ellipse_Color_R" << m_Ellipse_Color[2];
	fs << "m_Ellipse_Color_G" << m_Ellipse_Color[1];
	fs << "m_Ellipse_Color_B" << m_Ellipse_Color[0] << "}";
	//HoughLineDect
	fs << "HoughLineDect" << "{" << "name" << "HoughLineDect" << "type" << 3 << "suntype" << HOUGH_LINE_DECT;
	fs << "m_HouLine_Cmin" << m_HouLine_Cmin;
	fs << "m_HouLine_Cmax" << m_HouLine_Cmax;
	fs << "m_HouLine_P" << m_HouLine_P;
	fs << "m_HouLine_Rho" << m_HouLine_Rho;
	fs << "m_HouLine_Theta" << m_HouLine_Theta;
	fs << "m_HouLine_Thre" << m_HouLine_Thre;
	fs << "m_HouLine_LineLen" << m_HouLine_LineLen;
	fs << "m_HouLine_LineGap" << m_HouLine_LineGap;
	fs << "m_HouLine_Thickness" << m_HouLine_Thickness;
	fs << "m_HouLine_Color_R" << m_HouLine_Color[2];
	fs << "m_HouLine_Color_G" << m_HouLine_Color[1];
	fs << "m_HouLine_Color_B" << m_HouLine_Color[0] << "}";
	//MatchLineDect
	fs << "MatchLineDect" << "{" << "name" << "MatchLineDect" << "type" << 3 << "suntype" << MATCH_LINE_DECT;
	fs << "m_MatLine_Cmin" << m_MatLine_Cmin;
	fs << "m_MatLine_Cmax" << m_MatLine_Cmax;
	fs << "m_MatLine_Dtype" << m_MatLine_Dtype;
	fs << "m_MatLine_C" << m_MatLine_C;
	fs << "m_MatLine_Reps" << m_MatLine_Reps;
	fs << "m_MatLine_Aeps" << m_MatLine_Aeps;
	fs << "m_MatLine_Thickness" << m_MatLine_Thickness;
	fs << "m_MatLine_Color_R" << m_MatLine_Color[2];
	fs << "m_MatLine_Color_G" << m_MatLine_Color[1];
	fs << "m_MatLine_Color_B" << m_MatLine_Color[0] << "}";
	//RectangleDect
	fs << "RectangleDect" << "{" << "name" << "RectangleDect" << "type" << 3 << "suntype" << RECTANGLE_DECT;
	fs << "m_Rectangle_Thickness" << m_Rectangle_Thickness;
	fs << "m_Rectangle_Cmin" << m_Rectangle_Cmin;
	fs << "m_Rectangle_Cmax" << m_Rectangle_Cmax;
	fs << "m_Rectangle_Minarea" << m_Rectangle_Minarea;
	fs << "m_Rectangle_Maxcos" << m_Rectangle_Maxcos;
	fs << "m_Rectangle_Color_R" << m_Rectangle_Color[2];
	fs << "m_Rectangle_Color_G" << m_Rectangle_Color[1];
	fs << "m_Rectangle_Color_B" << m_Rectangle_Color[0] << "}";
	//CrossDect
	fs << "CrossDect" << "{" << "name" << "CrossDect" << "type" << 3 << "suntype" << CROSS_DECT;
	fs << "m_Cross_Cmin" << m_Cross_Cmin;
	fs << "m_Cross_Cmax" << m_Cross_Cmax;
	fs << "m_Cross_Rho" << m_Cross_Rho;
	fs << "m_Cross_Theta" << m_Cross_Theta;
	fs << "m_Cross_Thre" << m_Cross_Thre;
	fs << "m_Cross_Linlen" << m_Cross_Linlen;
	fs << "m_Cross_LineGap" << m_Cross_LineGap;
	fs << "m_Cross_Mindist" << m_Cross_Mindist;
	fs << "m_Cross_Mingap" << m_Cross_Mingap;
	fs << "m_Cross_Maxpix" << m_Cross_Maxpix;
	fs << "m_Cross_Maxrot" << m_Cross_Maxrot;
	fs << "m_Cross_Thickness" << m_Cross_Thickness;
	fs << "m_Cross_Color_R" << m_Cross_Color[2];
	fs << "m_Cross_Color_G" << m_Cross_Color[1];
	fs << "m_Cross_Color_B" << m_Cross_Color[0] << "}";
	fs.release();
	return 0;
}

int __stdcall Shape::SaveXML(char* filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//HoughCircleDect
	fs << "HoughCircleDect" << "{" << "name" << "HoughCircleDect" << "type" << 3 << "suntype" << HOUGH_CIRCLE_DECT;
	fs << "m_HouCir_Method" << m_HouCir_Method;
	fs << "m_HouCir_Minr" << m_HouCir_Minr;
	fs << "m_HouCir_Maxr" << m_HouCir_Maxr;
	fs << "m_HouCir_Dp" << m_HouCir_Dp;
	fs << "m_HouCir_Mindist" << m_HouCir_Mindist;
	fs << "m_HouCir_Thre" << m_HouCir_Thre;
	fs << "m_HouCir_Vote" << m_HouCir_Vote;
	fs << "m_HouCir_Thickness" << m_HouCir_Thickness;
	fs << "m_HouCir_Color_R" << m_HouCir_Color[2];
	fs << "m_HouCir_Color_G" << m_HouCir_Color[1];
	fs << "m_HouCir_Color_B" << m_HouCir_Color[0] << "}";
	//MatchCircleDect
	fs << "MatchCircleDect" << "{" << "name" << "MatchCircleDect" << "type" << 3 << "suntype" << MATCH_CIRCLE_DECT;
	fs << "m_MatCir_Cmin" << m_MatCir_Cmin;
	fs << "m_MatCir_Cmax" << m_MatCir_Cmax;
	fs << "m_MatCir_Thickness" << m_MatCir_Thickness;
	fs << "m_MatCir_Degree" << m_MatCir_Degree;
	fs << "m_MatCir_Color_R" << m_MatCir_Color[2];
	fs << "m_MatCir_Color_G" << m_MatCir_Color[1];
	fs << "m_MatCir_Color_B" << m_MatCir_Color[0] << "}";
	//EllipseDect
	fs << "EllipseDect" << "{" << "name" << "EllipseDect" << "type" << 3 << "suntype" << ELLIPSE_DECT;
	fs << "m_Ellipse_Cmin" << m_Ellipse_Cmin;
	fs << "m_Ellipse_Cmax" << m_Ellipse_Cmax;
	fs << "m_Ellipse_Scale" << m_Ellipse_Scale;
	fs << "m_Ellipse_Thickness" << m_Ellipse_Thickness;
	fs << "m_Ellipse_Color_R" << m_Ellipse_Color[2];
	fs << "m_Ellipse_Color_G" << m_Ellipse_Color[1];
	fs << "m_Ellipse_Color_B" << m_Ellipse_Color[0] << "}";
	//HoughLineDect
	fs << "HoughLineDect" << "{" << "name" << "HoughLineDect" << "type" << 3 << "suntype" << HOUGH_LINE_DECT;
	fs << "m_HouLine_Cmin" << m_HouLine_Cmin;
	fs << "m_HouLine_Cmax" << m_HouLine_Cmax;
	fs << "m_HouLine_P" << m_HouLine_P;
	fs << "m_HouLine_Rho" << m_HouLine_Rho;
	fs << "m_HouLine_Theta" << m_HouLine_Theta;
	fs << "m_HouLine_Thre" << m_HouLine_Thre;
	fs << "m_HouLine_LineLen" << m_HouLine_LineLen;
	fs << "m_HouLine_LineGap" << m_HouLine_LineGap;
	fs << "m_HouLine_Thickness" << m_HouLine_Thickness;
	fs << "m_HouLine_Color_R" << m_HouLine_Color[2];
	fs << "m_HouLine_Color_G" << m_HouLine_Color[1];
	fs << "m_HouLine_Color_B" << m_HouLine_Color[0] << "}";
	//MatchLineDect
	fs << "MatchLineDect" << "{" << "name" << "MatchLineDect" << "type" << 3 << "suntype" << MATCH_LINE_DECT;
	fs << "m_MatLine_Cmin" << m_MatLine_Cmin;
	fs << "m_MatLine_Cmax" << m_MatLine_Cmax;
	fs << "m_MatLine_Dtype" << m_MatLine_Dtype;
	fs << "m_MatLine_C" << m_MatLine_C;
	fs << "m_MatLine_Reps" << m_MatLine_Reps;
	fs << "m_MatLine_Aeps" << m_MatLine_Aeps;
	fs << "m_MatLine_Thickness" << m_MatLine_Thickness;
	fs << "m_MatLine_Color_R" << m_MatLine_Color[2];
	fs << "m_MatLine_Color_G" << m_MatLine_Color[1];
	fs << "m_MatLine_Color_B" << m_MatLine_Color[0] << "}";
	//RectangleDect
	fs << "RectangleDect" << "{" << "name" << "RectangleDect" << "type" << 3 << "suntype" << RECTANGLE_DECT;
	fs << "m_Rectangle_Thickness" << m_Rectangle_Thickness;
	fs << "m_Rectangle_Cmin" << m_Rectangle_Cmin;
	fs << "m_Rectangle_Cmax" << m_Rectangle_Cmax;
	fs << "m_Rectangle_Minarea" << m_Rectangle_Minarea;
	fs << "m_Rectangle_Maxcos" << m_Rectangle_Maxcos;
	fs << "m_Rectangle_Color_R" << m_Rectangle_Color[2];
	fs << "m_Rectangle_Color_G" << m_Rectangle_Color[1];
	fs << "m_Rectangle_Color_B" << m_Rectangle_Color[0] << "}";
	//CrossDect
	fs << "CrossDect" << "{" << "name" << "CrossDect" << "type" << 3 << "suntype" << CROSS_DECT;
	fs << "m_Cross_Cmin" << m_Cross_Cmin;
	fs << "m_Cross_Cmax" << m_Cross_Cmax;
	fs << "m_Cross_Rho" << m_Cross_Rho;
	fs << "m_Cross_Theta" << m_Cross_Theta;
	fs << "m_Cross_Thre" << m_Cross_Thre;
	fs << "m_Cross_Linlen" << m_Cross_Linlen;
	fs << "m_Cross_LineGap" << m_Cross_LineGap;
	fs << "m_Cross_Mindist" << m_Cross_Mindist;
	fs << "m_Cross_Mingap" << m_Cross_Mingap;
	fs << "m_Cross_Maxpix" << m_Cross_Maxpix;
	fs << "m_Cross_Maxrot" << m_Cross_Maxrot;
	fs << "m_Cross_Thickness" << m_Cross_Thickness;
	fs << "m_Cross_Color_R" << m_Cross_Color[2];
	fs << "m_Cross_Color_G" << m_Cross_Color[1];
	fs << "m_Cross_Color_B" << m_Cross_Color[0] << "}";
	fs.release();
	return 0;
}

int __stdcall Shape::LoadXML()
{
	FileStorage fs(_SHAPE_XML_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode HouCirNode = fs["HoughCircleDect"];
	m_HouCir_Method = HouCirNode["m_HouCir_Method"];
	m_HouCir_Thickness = HouCirNode["m_HouCir_Thickness"];
	m_HouCir_Minr = HouCirNode["m_HouCir_Minr"];
	m_HouCir_Maxr = HouCirNode["m_HouCir_Maxr"];
	m_HouCir_Dp = HouCirNode["m_HouCir_Dp"];
	m_HouCir_Mindist = HouCirNode["m_HouCir_Mindist"];
	m_HouCir_Thre = HouCirNode["m_HouCir_Thre"];
	m_HouCir_Vote = HouCirNode["m_HouCir_Vote"];
	m_HouCir_Color[2] = HouCirNode["m_HouCir_Color_R"];
	m_HouCir_Color[2] = HouCirNode["m_HouCir_Color_G"];
	m_HouCir_Color[2] = HouCirNode["m_HouCir_Color_B"];
	FileNode MatCirNode = fs["MatchCircleDect"];
	m_MatCir_Cmin = MatCirNode["m_MatCir_Cmin"];
	m_MatCir_Cmax = MatCirNode["m_MatCir_Cmax"];
	m_MatCir_Thickness = MatCirNode["m_MatCir_Thickness"];
	m_MatCir_Degree = MatCirNode["m_MatCir_Degree"];
	m_MatCir_Color[2] = MatCirNode["m_MatCir_Color_R"];
	m_MatCir_Color[1] = MatCirNode["m_MatCir_Color_G"];
	m_MatCir_Color[0] = MatCirNode["m_MatCir_Color_B"];
	FileNode EllipseNode = fs["EllipseDect"];
	m_Ellipse_Cmin = EllipseNode["m_Ellipse_Cmin"];
	m_Ellipse_Cmax = EllipseNode["m_Ellipse_Cmax"];
	m_Ellipse_Scale = EllipseNode["m_Ellipse_Scale"];
	m_Ellipse_Thickness = EllipseNode["m_Ellipse_Thickness"];
	m_Ellipse_Color[2] = EllipseNode["m_Ellipse_Color_R"];
	m_Ellipse_Color[1] = EllipseNode["m_Ellipse_Color_G"];
	m_Ellipse_Color[0] = EllipseNode["m_Ellipse_Color_B"];
	//HoughLineDect
	FileNode HouLineNode = fs["HoughLineDect"];
	m_HouLine_Cmin = HouLineNode["m_HouLine_Cmin"];
	m_HouLine_Cmax = HouLineNode["m_HouLine_Cmax"];
	m_HouLine_P = (int)HouLineNode["m_HouLine_P"];
	m_HouLine_Rho = HouLineNode["m_HouLine_Rho"];
	m_HouLine_Theta = HouLineNode["m_HouLine_Theta"];
	m_HouLine_Thre = HouLineNode["m_HouLine_Thre"];
	m_HouLine_LineLen = HouLineNode["m_HouLine_LineLen"];
	m_HouLine_LineGap = HouLineNode["m_HouLine_LineGap"];
	m_HouLine_Thickness = HouLineNode["m_HouLine_Thickness"];
	m_HouLine_Color[2] = HouLineNode["m_HouLine_Color_R"];
	m_HouLine_Color[1] = HouLineNode["m_HouLine_Color_G"];
	m_HouLine_Color[0] = HouLineNode["m_HouLine_Color_B"];
	//MatchLineDect
	FileNode MatLineNode = fs["MatchLineDect"];
	m_MatLine_Cmin = MatLineNode["m_MatLine_Cmin"];
	m_MatLine_Cmax = MatLineNode["m_MatLine_Cmax"];
	m_MatLine_Dtype = MatLineNode["m_MatLine_Dtype"];
	m_MatLine_C = MatLineNode["m_MatLine_C"];
	m_MatLine_Reps = MatLineNode["m_MatLine_Reps"];
	m_MatLine_Aeps = MatLineNode["m_MatLine_Aeps"];
	m_MatLine_Cmax = MatLineNode["m_MatLine_Cmax"];
	m_MatLine_Color[2] = MatLineNode["m_MatLine_Color_R"];
	m_MatLine_Color[1] = MatLineNode["m_MatLine_Color_G"];
	m_MatLine_Color[0] = MatLineNode["m_MatLine_Color_B"];
	m_MatLine_Thickness = MatLineNode["m_MatLine_Thickness"];
	//RectangleDect
	FileNode RectangleNode = fs["RectangleDect"];
	m_Rectangle_Thickness = RectangleNode["m_Rectangle_Thickness"];
	m_Rectangle_Cmin = RectangleNode["m_Rectangle_Cmin"];
	m_Rectangle_Cmax = RectangleNode["m_Rectangle_Cmax"];
	m_Rectangle_Minarea = RectangleNode["m_Rectangle_Minarea"];
	m_Rectangle_Maxcos = RectangleNode["m_Rectangle_Maxcos"];
	m_Rectangle_Color[2] = RectangleNode["m_Rectangle_Color_R"];
	m_Rectangle_Color[1] = RectangleNode["m_Rectangle_Color_G"];
	m_Rectangle_Color[0] = RectangleNode["m_Rectangle_Color_B"];
	//CrossDect
	FileNode CrossNode = fs["CrossDect"];
	m_Cross_Cmin = CrossNode["m_Cross_Cmin"];
	m_Cross_Cmax = CrossNode["m_Cross_Cmax"];
	m_Cross_Rho = CrossNode["m_Cross_Rho"];
	m_Cross_Theta = CrossNode["m_Cross_Theta"];
	m_Cross_Thre = CrossNode["m_Cross_Thre"];
	m_Cross_Linlen = CrossNode["m_Cross_Linlen"];
	m_Cross_LineGap = CrossNode["m_Cross_LineGap"];
	m_Cross_Mindist = CrossNode["m_Cross_Mindist"];
	m_Cross_Mingap = CrossNode["m_Cross_Mingap"];
	m_Cross_Maxpix = CrossNode["m_Cross_Maxpix"];
	m_Cross_Maxrot = CrossNode["m_Cross_Maxrot"];
	m_Cross_Thickness = CrossNode["m_Cross_Thickness"];
	m_Cross_Color[2] = CrossNode["m_Cross_Color_R"];
	m_Cross_Color[1] = CrossNode["m_Cross_Color_G"];
	m_Cross_Color[0] = CrossNode["m_Cross_Color_B"];
	fs.release();
	return 0;
}

int __stdcall Shape::LoadXML(char* filename)
{
	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode HouCirNode = fs["HoughCircleDect"];
	m_HouCir_Method = HouCirNode["m_HouCir_Method"];
	m_HouCir_Thickness = HouCirNode["m_HouCir_Thickness"];
	m_HouCir_Minr = HouCirNode["m_HouCir_Minr"];
	m_HouCir_Maxr = HouCirNode["m_HouCir_Maxr"];
	m_HouCir_Dp = HouCirNode["m_HouCir_Dp"];
	m_HouCir_Mindist = HouCirNode["m_HouCir_Mindist"];
	m_HouCir_Thre = HouCirNode["m_HouCir_Thre"];
	m_HouCir_Vote = HouCirNode["m_HouCir_Vote"];
	m_HouCir_Color[2] = HouCirNode["m_HouCir_Color_R"];
	m_HouCir_Color[2] = HouCirNode["m_HouCir_Color_G"];
	m_HouCir_Color[2] = HouCirNode["m_HouCir_Color_B"];
	FileNode MatCirNode = fs["MatchCircleDect"];
	m_MatCir_Cmin = MatCirNode["m_MatCir_Cmin"];
	m_MatCir_Cmax = MatCirNode["m_MatCir_Cmax"];
	m_MatCir_Thickness = MatCirNode["m_MatCir_Thickness"];
	m_MatCir_Degree = MatCirNode["m_MatCir_Degree"];
	m_MatCir_Color[2] = MatCirNode["m_MatCir_Color_R"];
	m_MatCir_Color[1] = MatCirNode["m_MatCir_Color_G"];
	m_MatCir_Color[0] = MatCirNode["m_MatCir_Color_B"];
	FileNode EllipseNode = fs["EllipseDect"];
	m_Ellipse_Cmin = EllipseNode["m_Ellipse_Cmin"];
	m_Ellipse_Cmax = EllipseNode["m_Ellipse_Cmax"];
	m_Ellipse_Scale = EllipseNode["m_Ellipse_Scale"];
	m_Ellipse_Thickness = EllipseNode["m_Ellipse_Thickness"];
	m_Ellipse_Color[2] = EllipseNode["m_Ellipse_Color_R"];
	m_Ellipse_Color[1] = EllipseNode["m_Ellipse_Color_G"];
	m_Ellipse_Color[0] = EllipseNode["m_Ellipse_Color_B"];
	//HoughLineDect
	FileNode HouLineNode = fs["HoughLineDect"];
	m_HouLine_Cmin = HouLineNode["m_HouLine_Cmin"];
	m_HouLine_Cmax = HouLineNode["m_HouLine_Cmax"];
	m_HouLine_P = (int)HouLineNode["m_HouLine_P"];
	m_HouLine_Rho = HouLineNode["m_HouLine_Rho"];
	m_HouLine_Theta = HouLineNode["m_HouLine_Theta"];
	m_HouLine_Thre = HouLineNode["m_HouLine_Thre"];
	m_HouLine_LineLen = HouLineNode["m_HouLine_LineLen"];
	m_HouLine_LineGap = HouLineNode["m_HouLine_LineGap"];
	m_HouLine_Thickness = HouLineNode["m_HouLine_Thickness"];
	m_HouLine_Color[2] = HouLineNode["m_HouLine_Color_R"];
	m_HouLine_Color[1] = HouLineNode["m_HouLine_Color_G"];
	m_HouLine_Color[0] = HouLineNode["m_HouLine_Color_B"];
	//MatchLineDect
	FileNode MatLineNode = fs["MatchLineDect"];
	m_MatLine_Cmin = MatLineNode["m_MatLine_Cmin"];
	m_MatLine_Cmax = MatLineNode["m_MatLine_Cmax"];
	m_MatLine_Dtype = MatLineNode["m_MatLine_Dtype"];
	m_MatLine_C = MatLineNode["m_MatLine_C"];
	m_MatLine_Reps = MatLineNode["m_MatLine_Reps"];
	m_MatLine_Aeps = MatLineNode["m_MatLine_Aeps"];
	m_MatLine_Cmax = MatLineNode["m_MatLine_Cmax"];
	m_MatLine_Color[2] = MatLineNode["m_MatLine_Color_R"];
	m_MatLine_Color[1] = MatLineNode["m_MatLine_Color_G"];
	m_MatLine_Color[0] = MatLineNode["m_MatLine_Color_B"];
	m_MatLine_Thickness = MatLineNode["m_MatLine_Thickness"];
	//RectangleDect
	FileNode RectangleNode = fs["RectangleDect"];
	m_Rectangle_Thickness = RectangleNode["m_Rectangle_Thickness"];
	m_Rectangle_Cmin = RectangleNode["m_Rectangle_Cmin"];
	m_Rectangle_Cmax = RectangleNode["m_Rectangle_Cmax"];
	m_Rectangle_Minarea = RectangleNode["m_Rectangle_Minarea"];
	m_Rectangle_Maxcos = RectangleNode["m_Rectangle_Maxcos"];
	m_Rectangle_Color[2] = RectangleNode["m_Rectangle_Color_R"];
	m_Rectangle_Color[1] = RectangleNode["m_Rectangle_Color_G"];
	m_Rectangle_Color[0] = RectangleNode["m_Rectangle_Color_B"];
	//CrossDect
	FileNode CrossNode = fs["CrossDect"];
	m_Cross_Cmin = CrossNode["m_Cross_Cmin"];
	m_Cross_Cmax = CrossNode["m_Cross_Cmax"];
	m_Cross_Rho = CrossNode["m_Cross_Rho"];
	m_Cross_Theta = CrossNode["m_Cross_Theta"];
	m_Cross_Thre = CrossNode["m_Cross_Thre"];
	m_Cross_Linlen = CrossNode["m_Cross_Linlen"];
	m_Cross_LineGap = CrossNode["m_Cross_LineGap"];
	m_Cross_Mindist = CrossNode["m_Cross_Mindist"];
	m_Cross_Mingap = CrossNode["m_Cross_Mingap"];
	m_Cross_Maxpix = CrossNode["m_Cross_Maxpix"];
	m_Cross_Maxrot = CrossNode["m_Cross_Maxrot"];
	m_Cross_Thickness = CrossNode["m_Cross_Thickness"];
	m_Cross_Color[2] = CrossNode["m_Cross_Color_R"];
	m_Cross_Color[1] = CrossNode["m_Cross_Color_G"];
	m_Cross_Color[0] = CrossNode["m_Cross_Color_B"];
	fs.release();
	return 0;
}

//private:
int Shape::HoughCircleDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		dst = src.clone();
		cvtColor(src, gray, CV_BGR2GRAY);
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(gray, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	vector<Point3f> circles;
	HoughCircles(gray, circles, m_HouCir_Method, m_HouCir_Dp, m_HouCir_Mindist, 
		m_HouCir_Thre, m_HouCir_Vote, m_HouCir_Minr, m_HouCir_Maxr);
	if (circles.size() == 0)
	{
		return _NO_DECTION_;
	}
	for (size_t i = 0; i < circles.size(); i++)
	{
		circle(dst, cvPoint(circles[i].x, circles[i].y), circles[i].z, 
			m_HouCir_Color, m_HouCir_Thickness);
	}
	return 0;
}

int Shape::MatchCircleDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	Canny(gray, gray, m_MatCir_Cmin, m_MatCir_Cmax);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	if (contours.size() == 0)
	{
		return _NO_DECTION_;
	}
	for (size_t i = 0; i < contours.size(); i++)
	{
		//Point2d center;
		Point2f center;
		double radius;
		double Mat_val;
		//if (CircleInfo2(contours[i], center, radius) != 0)
		if (fitCircle(contours[i], center, radius, Mat_val) != 0)
		{
			continue;
		}
		if (Mat_val >= m_MatCir_Degree)
			continue;
		circle(dst, center, radius, m_MatCir_Color, m_MatCir_Thickness);
	}
	return 0;
}

int Shape::EllipseDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	Canny(gray, gray, m_Ellipse_Cmin, m_Ellipse_Cmax);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	if (contours.size() == 0)
	{
		return _NO_DECTION_;
	}
	for (size_t i = 0; i < contours.size(); i++)
	{
		//拟合的点至少为6
		size_t count = contours[i].size();
		if (count < 6)
			continue;
		//椭圆拟合
		RotatedRect box = fitEllipse(contours[i]);
		//如果长宽比大于30，则排除，不做拟合
		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * m_Ellipse_Scale)
			continue;
		//画出追踪出的轮廓
		//drawContours(dst, contours, (int)i, Scalar::all(255), 1, 8);
		//画出拟合的椭圆
		ellipse(dst, box, m_Ellipse_Color, m_Ellipse_Thickness, CV_AA);
	}
	return 0;
}

int Shape::HoughLineDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	Canny(gray, gray, m_HouLine_Cmin, m_HouLine_Cmax);
	if (m_HouLine_Thickness <= 0)
	{
		m_HouLine_Thickness = 1;
	}
	if (m_HouLine_P)
	{
		vector<Vec4i> lines;//储存着检测到的直线的参数对 (X1, Y1, X2, Y2) 的容器，也就是线段的两个端点
		HoughLinesP(gray, lines, m_HouLine_Rho, m_HouLine_Theta, m_HouLine_Thre, m_HouLine_LineLen, m_HouLine_LineGap);
		if (lines.size() == 0)
		{
			return _NO_DECTION_;
		}
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(dst, Point(l[0], l[1]), Point(l[2], l[3]), m_HouLine_Color, m_HouLine_Thickness, CV_AA);
		}
	}
	else
	{
		vector<Vec2f> lines;
		HoughLines(gray, lines, m_HouLine_Rho, m_HouLine_Theta, m_HouLine_Thre);
		if (lines.size() == 0)
		{
			return _NO_DECTION_;
		}
		for (size_t i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(dst, pt1, pt2, m_HouLine_Color, m_HouLine_Thickness, CV_AA);
		}
	}
	return 0;
}

int Shape::MatchLineDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	Canny(gray, gray, m_MatLine_Cmin, m_MatLine_Cmax);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	if (contours.size() == 0)
	{
		return _NO_DECTION_;
	}
	for (size_t i = 0; i < contours.size(); i++)
	{
		Vec4f l;
		//cv::Point point1, point2;
		cv::fitLine(contours[i], l, m_MatLine_Dtype, m_MatLine_C, m_MatLine_Reps, m_MatLine_Aeps);
		int x = l[2], y = l[3];
		double k;
		if (l[0] != 0)
		{
			k = l[1] / l[0];
			/*point1.x = 0;
			point1.y = k * (0 - x) + y;
			point2.x = src.cols;
			point2.y = k * (src.cols - x) + y;*/
		}
		else
		{
			//k = l[1] / l[0];
			k = nan("Nan");
			/*point1.x = 0;
			point1.y = k * (0 - x) + y;
			point2.x = src.cols;
			point2.y = k * (src.cols - x) + y;*/
		}
		DrawLineByKP(dst, k, Point(x, y), m_MatLine_Color, m_MatLine_Thickness);
		//line(dst, point1, point2, m_MatLine_Color, m_MatLine_Thickness);
	}
	return 0;
}

int Shape::RectangleDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	Canny(gray, gray, m_Rectangle_Cmin, m_Rectangle_Cmax);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	if (contours.size() == 0)
		return _NO_DECTION_;
	vector<Point> approx;
	vector<vector<Point>> squares;
	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(contours[i], approx, arcLength(contours[i], true)*0.02, true);
		double contourMax = contourArea(approx);
		if (approx.size() == 4 && fabs(contourMax) > m_Rectangle_Minarea &&isContourConvex(approx))
		{
			double maxCosine = 0;
			for (int j = 2; j < 5; j++)
			{
				double cosine = fabs(getAngle(approx[j % 4], approx[j - 1], approx[j - 2]));
				maxCosine  = MAX(maxCosine, cosine);
			}
			if (fabs(maxCosine-90) < m_Rectangle_Maxcos)
				squares.push_back(approx);
		}
	}
	if (squares.size() == 0)
		return _NO_DECTION_;
	if (m_Rectangle_Thickness == CV_FILLED)
	{
		fillPoly(dst, squares, m_Rectangle_Color);
	}
	else
	{
		polylines(dst, squares, true, m_Rectangle_Color, m_Rectangle_Thickness);
	}
	return 0;
}

int Shape::CrossDect(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	Mat gray;
	if (src.channels() == 3)
	{
		cv::cvtColor(src, gray, CV_BGR2GRAY);
		dst = src.clone();
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
		cvtColor(src, dst, CV_GRAY2BGR);
	}
	else
		return _PARAM_ERROR_;
	Canny(gray, gray, m_Cross_Cmin, m_Cross_Cmax);
	vector<Vec4i> lines;//储存着检测到的直线的参数对 (X1, Y1, X2, Y2) 的容器，也就是线段的两个端点
	HoughLinesP(gray, lines, m_Cross_Rho, m_Cross_Theta, m_Cross_Thre, m_Cross_Linlen, m_Cross_LineGap);
	if (lines.size() == 0)
	{
		return _NO_DECTION_;
	}
	vector<Vec3d> weight;
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		int lenx, leny;
		lenx = abs(l[0] - l[2]);
		leny = abs(l[1] - l[3]);
		Vec3d w;
		w[0] = sqrt(pow(lenx, 2) + pow(leny, 2));
		if (lenx < m_Cross_Maxpix && leny<m_Cross_Maxpix)
		{
			w[1] = nan("inf");
			w[2] = nan("inf");
			weight.push_back(w);
			continue;
		}
		double x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];
		if (x1 > x2)
		{
			int temp = x2;
			x2 = x1;
			x1 = temp;
			temp = y2;
			y2 = y1;
			y1 = temp;
		}
		if (lenx < m_Cross_Maxpix && w[0] > m_Cross_Mindist)
		{
			w[1] = nan("inf");
			w[2] = (x1 + x2) / 2;
		}
		else if (leny < m_Cross_Maxpix && w[0] > m_Cross_Mindist)
		{
			w[1] = 0;
			w[2] = (y1 + y2) / 2;
		}
		else
		{
			w[1] = (y1 - y2) / (x1 - x2);
			w[2] = (y2 * x1 - y1 * x2) / (x1 - x2);
		}
		weight.push_back(w);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 1; j < lines.size(); j++)
		{
			//判断检测到的直线是否有效
			if (isnan(weight[i][2]) || isnan(weight[j][2]))
			{
				continue;
			}
			//判断两直线是否长度接近
			if (fabs(weight[i][0] - weight[j][0]) > m_Cross_Mingap)
			{
				continue;
			}
			//判断两直线是否垂直
			if ((fabs(weight[i][1] * weight[j][1] + 1) < m_Cross_Maxrot)
				|| (isnan(weight[i][1]) && weight[j][1] == 0)
				|| (isnan(weight[j][1]) && weight[i][1] == 0))
			{
				line(dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), m_Cross_Color, m_Cross_Thickness);
				line(dst, Point(lines[j][0], lines[j][1]), Point(lines[j][2], lines[j][3]), m_Cross_Color, m_Cross_Thickness);
			}
		}
	}
	return 0;
}

int Shape::CircleInfo2(std::vector<cv::Point> pts, cv::Point2d& center, double& radius)
{
	center = cv::Point2d(0, 0);
	radius = 0.0;
	if (pts.size() < 3) return false;;

	double sumX = 0.0;
	double sumY = 0.0;
	double sumX2 = 0.0;
	double sumY2 = 0.0;
	double sumX3 = 0.0;
	double sumY3 = 0.0;
	double sumXY = 0.0;
	double sumX1Y2 = 0.0;
	double sumX2Y1 = 0.0;
	const double N = (double)pts.size();
	for (int i = 0; i < pts.size(); ++i)
	{
		double x = pts.at(i).x;
		double y = pts.at(i).y;
		double x2 = x * x;
		double y2 = y * y;
		double x3 = x2 *x;
		double y3 = y2 *y;
		double xy = x * y;
		double x1y2 = x * y2;
		double x2y1 = x2 * y;

		sumX += x;
		sumY += y;
		sumX2 += x2;
		sumY2 += y2;
		sumX3 += x3;
		sumY3 += y3;
		sumXY += xy;
		sumX1Y2 += x1y2;
		sumX2Y1 += x2y1;
	}
	double C = N * sumX2 - sumX * sumX;
	double D = N * sumXY - sumX * sumY;
	double E = N * sumX3 + N * sumX1Y2 - (sumX2 + sumY2) * sumX;
	double G = N * sumY2 - sumY * sumY;
	double H = N * sumX2Y1 + N * sumY3 - (sumX2 + sumY2) * sumY;
	double denominator = C * G - D * D;
	if (std::abs(denominator) < DBL_EPSILON) 
		return _PARAM_ERROR_;
	double a = (H * D - E * G) / (denominator);
	denominator = D * D - G * C;
	if (std::abs(denominator) < DBL_EPSILON) 
		return _PARAM_ERROR_;
	double b = (H * C - E * D) / (denominator);
	double c = -(a * sumX + b * sumY + sumX2 + sumY2) / N;

	center.x = a / (-2);
	center.y = b / (-2);
	radius = std::sqrt(a * a + b * b - 4 * c) / 2;
	return 0;
}

int Shape::fitCircle(vector<Point>& contour, Point2f& centor, double& radius, double &match_val)
{
	if (contour.empty())
		return _PARAM_ERROR_;

	double a1 = 0, a2 = 0, a3 = 0;
	double b1 = 0, b2 = 0, b3 = 0;
	double c11 = 0, c12 = 0, c21 = 0, c22 = 0;
	for (size_t i = 0; i < contour.size(); i++)
	{
		Point temp = contour[i];
		a1 += temp.x;
		a2 += temp.x * temp.x;
		a3 += temp.x * temp.x * temp.x;

		b1 += temp.y;
		b2 += temp.y * temp.y;
		b3 += temp.y * temp.y * temp.y;

		c11 += temp.x * temp.y;
		c12 += temp.x * temp.y * temp.y;
		c21 += temp.x * temp.x * temp.y;
		c22 += temp.x * temp.x + temp.x * temp.y;
	}
	double A1 = 2.0 * a1 * a1 / double(contour.size()) - 2.0 * a2;
	double B1 = 2.0 * a1 * b1 / double(contour.size()) - 2.0 * c11;
	double C1 = a3 + c12 - (a1 * (a2 + b2)) / double(contour.size());
	double A2 = B1;
	double B2 = 2.0 * b1 * b1 / double(contour.size()) - 2.0 * b2;
	double C2 = c21 + b3 - (b1 * (a2 + b2)) / double(contour.size());

	centor.x = (A2 * C2 - B2 * C1) / (A1 * B2 - A2 * A2);
	centor.y = (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * A2);
	radius = 0.0;
	for (size_t i = 0; i < contour.size(); i++)
	{
		radius += ((contour[i].x - centor.x) * (contour[i].x - centor.x) +
			(contour[i].y - centor.y) * (contour[i].y - centor.y)
			);
	}
	radius = sqrt(radius / double(contour.size()));

	//计算拟合度
	double approxDegree = 0.0;
	for (size_t i = 0; i < contour.size(); i++)
	{
		double temp = (contour[i].x - centor.x) * (contour[i].x - centor.x) +
			(contour[i].y - centor.y) * (contour[i].y - centor.y) -
			radius * radius;
		approxDegree += temp * temp;
	}
	match_val = approxDegree / double(contour.size()) / radius / radius;
	return 0;
}

double Shape::getAngle(cv::Point OutPt1, cv::Point ClosePt, cv::Point OutPt2)
{
	/*double ABlen = getDist(OutPt1, ClosePt);
	double CBlen = getDist(OutPt2, ClosePt);
	double deno = ABlen*CBlen;
	double mole1 = (OutPt1.x - ClosePt.x)*(OutPt2.x - ClosePt.x);
	double mole2 = (OutPt1.y - ClosePt.y)*(OutPt2.y - ClosePt.y);
	double mole = mole1 + mole2;
	double cos = mole / deno;
	return acos(cos) * 180.0 / CV_PI;*/

	double P1P2 = sqrt((double)((OutPt1.x - ClosePt.x) * (OutPt1.x - ClosePt.x) + (OutPt1.y - ClosePt.y) * (OutPt1.y - ClosePt.y)));
	double P1P3 = sqrt((double)((OutPt1.x - OutPt2.x) * (OutPt1.x - OutPt2.x) + (OutPt1.y - OutPt2.y) * (OutPt1.y - OutPt2.y)));
	double P2P3 = sqrt((double)((ClosePt.x - OutPt2.x) * (ClosePt.x - OutPt2.x) + (ClosePt.y - OutPt2.y) * (ClosePt.y - OutPt2.y)));
	return acos((P1P2 * P1P2 + P2P3 * P2P3 - P1P3 * P1P3) / (2 * P1P2 * P2P3)) * 180.0 / CV_PI;

	/*double SubxBA = (OutPt1.x - ClosePt.x);
	double SubxBC = (OutPt2.x - ClosePt.x);
	if (SubxBA == 0 || SubxBC == 0)
	{
		return 90.0;
	}
	double tmpBA = (OutPt1.y - ClosePt.y) / SubxBA;
	double angleBA = atan(tmpBA) * 180 / CV_PI;
	double tmpBC = (OutPt2.y - ClosePt.y) / SubxBC;
	double angleBC = atan(tmpBC) * 180 / CV_PI;
	return angleBA - angleBC;*/
}

double Shape::getDist(cv::Point Pt1, cv::Point Pt2)
{
	double dLinex = pow(Pt1.x - Pt2.x, 2);
	double dLiney = pow(Pt1.y - Pt2.y, 2);
	return sqrt(dLinex + dLiney);
}

void Shape::DrawLineByKP(cv::Mat &src, double k, cv::Point pt, cv::Scalar color, int thinkess)
{
	//当斜率无穷大时
	if (_isnan(k))
	{
		line(src, Point(pt.x, 0), Point(pt.x, src.rows), cv::Scalar(0, 255, 0), 2, 8, 0);
		circle(src, pt, 3, Scalar(0, 0, 255), CV_FILLED);
		return;
	}
	//当斜率为0时
	if (k == 0)
	{
		line(src, Point(0, pt.y), Point(src.cols, pt.y), cv::Scalar(0, 255, 0), 2, 8, 0);
		circle(src, pt, 3, Scalar(0, 0, 255), CV_FILLED);
		return;
	}
	cv::Point point1, point2;
	//当斜率比较小时，用x确定直线
	if (abs(k) <= 1)
	{
		point1.x = 0;
		point1.y = k * (0 - pt.x) + pt.y;
		point2.x = src.cols;
		point2.y = k * (src.cols - pt.x) + pt.y;
	}
	//当斜率比较大时，用y确定直线
	else
	{
		point1.y = 0;
		point1.x = ((0 - pt.y) / k) + pt.x;
		point2.y = src.rows;
		point2.x = ((src.rows - pt.y) / k) + pt.x;
	}
	cout << "Point 1:(" << point1.x << ", " << point1.y << ")" << endl;
	cout << "Point 2:(" << point2.x << ", " << point2.y << ")" << endl;
	cv::line(src, point1, point2, color, thinkess);
	//circle(src, pt, 3, Scalar(0, 0, 255), CV_FILLED);
}