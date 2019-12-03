#include "stdafx.h"
#include "ROI.h"

using namespace cv;
using namespace std;

//public:
ROI::ROI()
{
	//LoadXML();
}

ROI::~ROI()
{
}



//读取XML(NULL)
int __stdcall ROI::LoadXML()
{
	FileStorage fs(_XML_FILE_NAME_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	m_Polygon_X.clear();
	m_Polygon_Y.clear();
	FileNode Circle = fs["Circle"];
	m_Circle_Center.x = Circle["Circle_Center_X"];
	m_Circle_Center.y = Circle["Circle_Center_Y"];
	m_Circle_Radius = Circle["Circle_Radius"];
	m_Circle_Division = (int)Circle["Circle_Division"];
	m_Circle_Resize.width = Circle["Circle_Resize_Widht"];
	m_Circle_Resize.height = Circle["Circle_Resize_Height"];
	FileNode Annulus = fs["Annulus"];
	m_Annulus_Center.x = Annulus["Annulus_Center_X"];
	m_Annulus_Center.y = Annulus["Annulus_Center_Y"];
	m_Annulus_Radius_Min = Annulus["Annulus_Radius_Min"];
	m_Annulus_Radius_Max = Annulus["Annulus_Radius_Max"];
	m_Annulus_Division = (int)Annulus["Annulus_Division"];
	m_Annulus_Resize.width = Annulus["Annulus_Resize_Widht"];
	m_Annulus_Resize.height = Annulus["Annulus_Resize_Height"];
	FileNode Rectangl = fs["Rectangl"];
	m_Rectangl_Rect.x = Rectangl["Rectangl_Rect_X"];
	m_Rectangl_Rect.y = Rectangl["Rectangl_Rect_Y"];
	m_Rectangl_Rect.width = Rectangl["Rectangl_Rect_Width"];
	m_Rectangl_Rect.height = Rectangl["Rectangl_Rect_Height"];
	m_Rectangl_Division = (int)Rectangl["Rectangl_Division"];
	m_Rectangl_Resize.width = Rectangl["Rectangl_Resize_Widht"];
	m_Rectangl_Resize.height = Rectangl["Rectangl_Resize_Height"];
	FileNode Ring = fs["Ring"];
	m_Ring_Rect_Min.x = Ring["Ring_Rect_Min_X"];
	m_Ring_Rect_Min.y = Ring["Ring_Rect_Min_Y"];
	m_Ring_Rect_Min.width = Ring["Ring_Rect_Min_Width"];
	m_Ring_Rect_Min.height = Ring["Ring_Rect_Min_Height"];
	m_Ring_Rect_Max.x = Ring["Ring_Rect_Max_X"];
	m_Ring_Rect_Max.y = Ring["Ring_Rect_Max_Y"];
	m_Ring_Rect_Max.width = Ring["Ring_Rect_Max_Width"];
	m_Ring_Rect_Max.height = Ring["Ring_Rect_Max_Height"];
	m_Rectangl_Division = (int)Ring["Ring_Division"];
	m_Rectangl_Resize.width = Ring["Ring_Resize_Widht"];
	m_Rectangl_Resize.height = Ring["Ring_Resize_Height"];
	FileNode EllipseNode = fs["Ellipse"];
	m_Ellipse.angle = EllipseNode["Ellipse_Angle"];
	m_Ellipse.center.x = EllipseNode["Ellipse_Center_X"];
	m_Ellipse.center.y = EllipseNode["Ellipse_Center_Y"];
	m_Ellipse.size.width = EllipseNode["Ellipse_Size_Width"];
	m_Ellipse.size.height = EllipseNode["Ellipse_Size_Height"];
	m_Ellipse_Division = (int)EllipseNode["Ellipse_Division"];
	m_Ellipse_Resize.width = EllipseNode["Ellipse_Resize_Widht"];
	m_Ellipse_Resize.height = EllipseNode["Ellipse_Resize_Height"];
	FileNode RotateRectNode = fs["RotateRect"];
	m_RotateRect.angle = RotateRectNode["RotateRect_Angle"];
	m_RotateRect.center.x = RotateRectNode["RotateRect_Center_X"];
	m_RotateRect.center.y = RotateRectNode["RotateRect_Center_Y"];
	m_RotateRect.size.width = RotateRectNode["RotateRect_Size_Width"];
	m_RotateRect.size.height = RotateRectNode["RotateRect_Size_Height"];
	m_RotateRect_Division = (int)RotateRectNode["RotateRect_Division"];
	m_RotateRect_Resize.width = RotateRectNode["RotateRect_Resize_Widht"];
	m_RotateRect_Resize.height = RotateRectNode["RotateRect_Resize_Height"];
	FileNode PolygonNode = fs["Polygon"];
	FileNode Polygon_XNode = PolygonNode["Polygon_X"];
	FileNode Polygon_YNode = PolygonNode["Polygon_Y"];
	FileNodeIterator it = Polygon_XNode.begin(), it_end = Polygon_XNode.end();
	for (FileNodeIterator it = Polygon_XNode.begin(); it != Polygon_XNode.end(); it++)
	{
		m_Polygon_X.push_back(*it);
	}
	for (FileNodeIterator it = Polygon_YNode.begin(); it != Polygon_YNode.end(); it++)
	{
		m_Polygon_Y.push_back(*it);
	}
	fs.release();
	return 0;
}

//读取参数
int __stdcall ROI::LoadXML(char* filename)
{
	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	m_Polygon_X.clear();
	m_Polygon_Y.clear();
	FileNode Circle = fs["Circle"];
	m_Circle_Center.x = Circle["Circle_Center_X"];
	m_Circle_Center.y = Circle["Circle_Center_Y"];
	m_Circle_Radius = Circle["Circle_Radius"];
	m_Circle_Division = (int)Circle["Circle_Division"];
	m_Circle_Resize.width = Circle["Circle_Resize_Widht"];
	m_Circle_Resize.height = Circle["Circle_Resize_Height"];
	FileNode Annulus = fs["Annulus"];
	m_Annulus_Center.x = Annulus["Annulus_Center_X"];
	m_Annulus_Center.y = Annulus["Annulus_Center_Y"];
	m_Annulus_Radius_Min = Annulus["Annulus_Radius_Min"];
	m_Annulus_Radius_Max = Annulus["Annulus_Radius_Max"];
	m_Annulus_Division = (int)Annulus["Annulus_Division"];
	m_Annulus_Resize.width = Annulus["Annulus_Resize_Widht"];
	m_Annulus_Resize.height = Annulus["Annulus_Resize_Height"];
	FileNode Rectangl = fs["Rectangl"];
	m_Rectangl_Rect.x = Rectangl["Rectangl_Rect_X"];
	m_Rectangl_Rect.y = Rectangl["Rectangl_Rect_Y"];
	m_Rectangl_Rect.width = Rectangl["Rectangl_Rect_Width"];
	m_Rectangl_Rect.height = Rectangl["Rectangl_Rect_Height"];
	m_Rectangl_Division = (int)Rectangl["Rectangl_Division"];
	m_Rectangl_Resize.width = Rectangl["Rectangl_Resize_Widht"];
	m_Rectangl_Resize.height = Rectangl["Rectangl_Resize_Height"];
	FileNode Ring = fs["Ring"];
	m_Ring_Rect_Min.x = Ring["Ring_Rect_Min_X"];
	m_Ring_Rect_Min.y = Ring["Ring_Rect_Min_Y"];
	m_Ring_Rect_Min.width = Ring["Ring_Rect_Min_Width"];
	m_Ring_Rect_Min.height = Ring["Ring_Rect_Min_Height"];
	m_Ring_Rect_Max.x = Ring["Ring_Rect_Max_X"];
	m_Ring_Rect_Max.y = Ring["Ring_Rect_Max_Y"];
	m_Ring_Rect_Max.width = Ring["Ring_Rect_Max_Width"];
	m_Ring_Rect_Max.height = Ring["Ring_Rect_Max_Height"];
	m_Rectangl_Division = (int)Ring["Ring_Division"];
	m_Rectangl_Resize.width = Ring["Ring_Resize_Widht"];
	m_Rectangl_Resize.height = Ring["Ring_Resize_Height"];
	FileNode EllipseNode = fs["Ellipse"];
	m_Ellipse.angle = EllipseNode["Ellipse_Angle"];
	m_Ellipse.center.x = EllipseNode["Ellipse_Center_X"];
	m_Ellipse.center.y = EllipseNode["Ellipse_Center_Y"];
	m_Ellipse.size.width = EllipseNode["Ellipse_Size_Width"];
	m_Ellipse.size.height = EllipseNode["Ellipse_Size_Height"];
	m_Ellipse_Division = (int)EllipseNode["Ellipse_Division"];
	m_Ellipse_Resize.width = EllipseNode["Ellipse_Resize_Widht"];
	m_Ellipse_Resize.height = EllipseNode["Ellipse_Resize_Height"];
	FileNode RotateRectNode = fs["RotateRect"];
	m_RotateRect.angle = RotateRectNode["RotateRect_Angle"];
	m_RotateRect.center.x = RotateRectNode["RotateRect_Center_X"];
	m_RotateRect.center.y = RotateRectNode["RotateRect_Center_Y"];
	m_RotateRect.size.width = RotateRectNode["RotateRect_Size_Width"];
	m_RotateRect.size.height = RotateRectNode["RotateRect_Size_Height"];
	m_RotateRect_Division = (int)RotateRectNode["RotateRect_Division"];
	m_RotateRect_Resize.width = RotateRectNode["RotateRect_Resize_Widht"];
	m_RotateRect_Resize.height = RotateRectNode["RotateRect_Resize_Height"];
	FileNode PolygonNode = fs["Polygon"];
	FileNode Polygon_XNode = PolygonNode["Polygon_X"];
	FileNode Polygon_YNode = PolygonNode["Polygon_Y"];
	FileNodeIterator it = Polygon_XNode.begin(), it_end = Polygon_XNode.end();
	for (FileNodeIterator it = Polygon_XNode.begin(); it != Polygon_XNode.end(); it++)
	{
		m_Polygon_X.push_back(*it);
	}
	for (FileNodeIterator it = Polygon_YNode.begin(); it != Polygon_YNode.end(); it++)
	{
		m_Polygon_Y.push_back(*it);
	}
	fs.release();
	return 0;
}

//写XML(NULL)
int __stdcall ROI::SaveXML()
{
	FileStorage fs(_XML_FILE_NAME_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//Circle
	fs << "Circle" << "{" << "name" << "CircleROI" << "type" << 0 << "suntype" << CIRCLE_ROI;
	fs << "Circle_Center_X" << m_Circle_Center.x;
	fs << "Circle_Center_Y" << m_Circle_Center.y;
	fs << "Circle_Radius" << m_Circle_Radius;
	fs << "Circle_Division" << m_Circle_Division;
	fs << "Circle_Resize_Widht" << m_Circle_Resize.width;
	fs << "Circle_Resize_Height" << m_Circle_Resize.height << "}";
	//Annulus
	fs << "Annulus" << "{" << "name" << "AnnulusROI" << "type" << 0 << "suntype" << ANNULUS_ROI;
	fs << "Annulus_Center_X" << m_Annulus_Center.x;
	fs << "Annulus_Center_Y" << m_Annulus_Center.y;
	fs << "Annulus_Radius_Min" << m_Annulus_Radius_Min;
	fs << "Annulus_Radius_Max" << m_Annulus_Radius_Max;
	fs << "Annulus_Division" << m_Annulus_Division;
	fs << "Annulus_Resize_Widht" << m_Annulus_Resize.width;
	fs << "Annulus_Resize_Height" << m_Annulus_Resize.height << "}";
	//Rectangl
	fs << "Rectangl" << "{" << "name" << "RectanglROI" << "type" << 0 << "suntype" << RECTANGLE_ROI;
	fs << "Rectangl_Rect_X" << m_Rectangl_Rect.x;
	fs << "Rectangl_Rect_Y" << m_Rectangl_Rect.y;
	fs << "Rectangl_Rect_Width" << m_Rectangl_Rect.width;
	fs << "Rectangl_Rect_Height" << m_Rectangl_Rect.height;
	fs << "Rectangl_Division" << m_Rectangl_Division;
	fs << "Rectangl_Resize_Widht" << m_Rectangl_Resize.width;
	fs << "Rectangl_Resize_Height" << m_Rectangl_Resize.height << "}";
	//Ring
	fs << "Ring" << "{" << "name" << "RingROI" << "type" << 0 << "suntype" << RING_ROI;
	fs << "Ring_Rect_Min_X" << m_Ring_Rect_Min.x;
	fs << "Ring_Rect_Min_Y" << m_Ring_Rect_Min.y;
	fs << "Ring_Rect_Min_Width" << m_Ring_Rect_Min.width;
	fs << "Ring_Rect_Min_Height" << m_Ring_Rect_Min.height;
	fs << "Ring_Rect_Max_X" << m_Ring_Rect_Max.x;
	fs << "Ring_Rect_Max_Y" << m_Ring_Rect_Max.y;
	fs << "Ring_Rect_Max_Width" << m_Ring_Rect_Max.width;
	fs << "Ring_Rect_Max_Height" << m_Ring_Rect_Max.height;
	fs << "Ring_Division" << m_Ring_Division;
	fs << "Ring_Resize_Widht" << m_Ring_Resize.width;
	fs << "Ring_Resize_Height" << m_Ring_Resize.height << "}";
	//Ellipse
	fs << "Ellipse" << "{" << "name" << "EllipseROI" << "type" << 0 << "suntype" << ELLIPSE_ROI;
	fs << "Ellipse_Angle" << m_Ellipse.angle;
	fs << "Ellipse_Center_X" << m_Ellipse.center.x;
	fs << "Ellipse_Center_Y" << m_Ellipse.center.y;
	fs << "Ellipse_Size_Width" << m_Ellipse.size.width;
	fs << "Ellipse_Size_Height" << m_Ellipse.size.height;
	fs << "Ellipse_Division" << m_Ellipse_Division;
	fs << "Ellipse_Resize_Widht" << m_Ellipse_Resize.width;
	fs << "Ellipse_Resize_Height" << m_Ellipse_Resize.height << "}";
	//RotateRect
	fs << "RotateRect" << "{" << "name" << "RotateRectROI" << "type" << 0 << "suntype" << ROTATEDRECT_ROI;
	fs << "RotateRect_Angle" << m_RotateRect.angle;
	fs << "RotateRect_Center_X" << m_RotateRect.center.x;
	fs << "RotateRect_Center_Y" << m_RotateRect.center.y;
	fs << "RotateRect_Size_Width" << m_RotateRect.size.width;
	fs << "RotateRect_Size_Height" << m_RotateRect.size.height;
	fs << "RotateRect_Division" << m_RotateRect_Division;
	fs << "RotateRect_Resize_Widht" << m_RotateRect_Resize.width;
	fs << "RotateRect_Resize_Height" << m_RotateRect_Resize.height << "}";
	//Polygon
	fs << "Polygon" << "{" << "name" << "PolygonROI" << "type" << 0 << "suntype" << POLYGON_ROI;
	fs << "Polygon_X" << "[";
	for (size_t i = 0; i < m_Polygon_X.size(); i++)
	{
		fs << m_Polygon_X[i];
	}
	fs << "]";
	fs << "Polygon_Y" << "[";
	for (size_t i = 0; i < m_Polygon_Y.size(); i++)
	{
		fs << m_Polygon_Y[i];
	}
	fs << "]";
	fs << "Polygon_Division" << m_Polygon_Division;
	fs << "Polygon_Resize_Widht" << m_Polygon_Resize.width;
	fs << "Polygon_Resize_Height" << m_Polygon_Resize.height << "}";
	fs.release();
	return 0;
}

//写参数
int __stdcall ROI::SaveXML(char* filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//Circle
	fs << "Circle" << "{" << "name" << "CircleROI" << "type" << 0 << "suntype" << CIRCLE_ROI;
	fs << "Circle_Center_X" << m_Circle_Center.x;
	fs << "Circle_Center_Y" << m_Circle_Center.y;
	fs << "Circle_Radius" << m_Circle_Radius;
	fs << "Circle_Division" << m_Circle_Division;
	fs << "Circle_Resize_Widht" << m_Circle_Resize.width;
	fs << "Circle_Resize_Height" << m_Circle_Resize.height << "}";
	//Annulus
	fs << "Annulus" << "{" << "name" << "AnnulusROI" << "type" << 0 << "suntype" << ANNULUS_ROI;
	fs << "Annulus_Center_X" << m_Annulus_Center.x;
	fs << "Annulus_Center_Y" << m_Annulus_Center.y;
	fs << "Annulus_Radius_Min" << m_Annulus_Radius_Min;
	fs << "Annulus_Radius_Max" << m_Annulus_Radius_Max;
	fs << "Annulus_Division" << m_Annulus_Division;
	fs << "Annulus_Resize_Widht" << m_Annulus_Resize.width;
	fs << "Annulus_Resize_Height" << m_Annulus_Resize.height << "}";
	//Rectangl
	fs << "Rectangl" << "{" << "name" << "RectanglROI" << "type" << 0 << "suntype" << RECTANGLE_ROI;
	fs << "Rectangl_Rect_X" << m_Rectangl_Rect.x;
	fs << "Rectangl_Rect_Y" << m_Rectangl_Rect.y;
	fs << "Rectangl_Rect_Width" << m_Rectangl_Rect.width;
	fs << "Rectangl_Rect_Height" << m_Rectangl_Rect.height;
	fs << "Rectangl_Division" << m_Rectangl_Division;
	fs << "Rectangl_Resize_Widht" << m_Rectangl_Resize.width;
	fs << "Rectangl_Resize_Height" << m_Rectangl_Resize.height << "}";
	//Ring
	fs << "Ring" << "{" << "name" << "RingROI" << "type" << 0 << "suntype" << RING_ROI;
	fs << "Ring_Rect_Min_X" << m_Ring_Rect_Min.x;
	fs << "Ring_Rect_Min_Y" << m_Ring_Rect_Min.y;
	fs << "Ring_Rect_Min_Width" << m_Ring_Rect_Min.width;
	fs << "Ring_Rect_Min_Height" << m_Ring_Rect_Min.height;
	fs << "Ring_Rect_Max_X" << m_Ring_Rect_Max.x;
	fs << "Ring_Rect_Max_Y" << m_Ring_Rect_Max.y;
	fs << "Ring_Rect_Max_Width" << m_Ring_Rect_Max.width;
	fs << "Ring_Rect_Max_Height" << m_Ring_Rect_Max.height;
	fs << "Ring_Division" << m_Ring_Division;
	fs << "Ring_Resize_Widht" << m_Ring_Resize.width;
	fs << "Ring_Resize_Height" << m_Ring_Resize.height << "}";
	//Ellipse
	fs << "Ellipse" << "{" << "name" << "EllipseROI" << "type" << 0 << "suntype" << ELLIPSE_ROI;
	fs << "Ellipse_Angle" << m_Ellipse.angle;
	fs << "Ellipse_Center_X" << m_Ellipse.center.x;
	fs << "Ellipse_Center_Y" << m_Ellipse.center.y;
	fs << "Ellipse_Size_Width" << m_Ellipse.size.width;
	fs << "Ellipse_Size_Height" << m_Ellipse.size.height;
	fs << "Ellipse_Division" << m_Ellipse_Division;
	fs << "Ellipse_Resize_Widht" << m_Ellipse_Resize.width;
	fs << "Ellipse_Resize_Height" << m_Ellipse_Resize.height << "}";
	//RotateRect
	fs << "RotateRect" << "{" << "name" << "RotateRectROI" << "type" << 0 << "suntype" << ROTATEDRECT_ROI;
	fs << "RotateRect_Angle" << m_RotateRect.angle;
	fs << "RotateRect_Center_X" << m_RotateRect.center.x;
	fs << "RotateRect_Center_Y" << m_RotateRect.center.y;
	fs << "RotateRect_Size_Width" << m_RotateRect.size.width;
	fs << "RotateRect_Size_Height" << m_RotateRect.size.height;
	fs << "RotateRect_Division" << m_RotateRect_Division;
	fs << "RotateRect_Resize_Widht" << m_RotateRect_Resize.width;
	fs << "RotateRect_Resize_Height" << m_RotateRect_Resize.height << "}";
	//Polygon
	fs << "Polygon" << "{" << "name" << "PolygonROI" << "type" << 0 << "suntype" << POLYGON_ROI;
	fs << "Polygon_X" << "[";
	for (size_t i = 0; i < m_Polygon_X.size(); i++)
	{
		fs << m_Polygon_X[i];
	}
	fs << "]";
	fs << "Polygon_Y" << "[";
	for (size_t i = 0; i < m_Polygon_Y.size(); i++)
	{
		fs << m_Polygon_Y[i];
	}
	fs << "]";
	fs << "Polygon_Division" << m_Polygon_Division;
	fs << "Polygon_Resize_Widht" << m_Polygon_Resize.width;
	fs << "Polygon_Resize_Height" << m_Polygon_Resize.height << "}";
	fs.release();
	return 0;
}

int __stdcall ROI::Excute_(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(CIRCLE_ROI) :
		return CircleROI(src, dst);
	case(ANNULUS_ROI) :
		return AnnulusROI(src, dst);
	case(RECTANGLE_ROI) :
		return RectangleROI(src, dst);
	case(RING_ROI) :
		return RingROI(src, dst);
	case(ELLIPSE_ROI) :
		return EllipseROI(src, dst);
	case(ROTATEDRECT_ROI) :
		return RotateRectROI(src, dst);
	case(POLYGON_ROI) :
		return PolygonROI(src, dst);
	default:
		return _PARAM_ERROR_;
	}
	return _PARAM_ERROR_;
}

bool __stdcall ROI::Excute(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(CIRCLE_ROI):
		if (CircleROI(src, dst) != 0)
			return false;
		return true;
	case(ANNULUS_ROI) :
		if (AnnulusROI(src, dst) != 0)
			return false;
		return true;
	case(RECTANGLE_ROI) :
		if (RectangleROI(src, dst) != 0)
			return false;
		return true;
	case(RING_ROI) :
		if (RingROI(src, dst) != 0)
			return false;
		return true;
	case(ELLIPSE_ROI) :
		if (AnnulusROI(src, dst) != 0)
			return false;
		return true;
	case(ROTATEDRECT_ROI) :
		if (AnnulusROI(src, dst) != 0)
			return false;
		return true;
	case(POLYGON_ROI) :
		if (AnnulusROI(src, dst) != 0)
			return false;
		return true;
	default:
		return false;
	}
	return false;
}

//private:
int ROI::RectangleROI(Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (m_Rectangl_Rect.x < 0 || m_Rectangl_Rect.y < 0 || m_Rectangl_Rect.width <= 0
		|| m_Rectangl_Rect.height <= 0 || m_Rectangl_Rect.x >= src.cols || m_Rectangl_Rect.y >= src.rows)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	if (m_Rectangl_Rect.x + m_Rectangl_Rect.width > src.cols || m_Rectangl_Rect.y + m_Rectangl_Rect.height > src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::rectangle(mask, m_Rectangl_Rect, cvScalarAll(0xff), CV_FILLED);
	return DivisionResize(src, mask, dst, m_Rectangl_Division, m_Rectangl_Resize);
}

int ROI::RingROI(Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (m_Ring_Rect_Min.x < 0 || m_Ring_Rect_Min.y < 0 || m_Ring_Rect_Min.width <= 0 || m_Ring_Rect_Min.height <= 0
		|| m_Ring_Rect_Min.x >= src.cols || m_Ring_Rect_Min.y >= src.rows || m_Ring_Rect_Max.x < 0 || m_Ring_Rect_Max.y < 0
		|| m_Ring_Rect_Max.width <= 0 || m_Ring_Rect_Max.height <= 0 || m_Ring_Rect_Max.x >= src.cols || m_Ring_Rect_Max.y >= src.rows)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	if (m_Ring_Rect_Max.x + m_Ring_Rect_Max.width > src.cols || m_Ring_Rect_Max.y + m_Ring_Rect_Max.height > src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	int rc = CompareRect(m_Ring_Rect_Min, m_Ring_Rect_Max);
	if (rc != 0)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::rectangle(mask, m_Ring_Rect_Max, cvScalarAll(0xff), CV_FILLED);
	cv::rectangle(mask, m_Ring_Rect_Min, cvScalarAll(0x00), CV_FILLED);
	return DivisionResize(src, mask, dst, m_Ring_Division, m_Ring_Resize);
}

int ROI::CircleROI(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (m_Circle_Radius <= 0 || m_Circle_Center.x <= 0 || m_Circle_Center.y <= 0)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	CvRect rect;
	rect.x = m_Circle_Center.x - m_Circle_Radius;
	rect.y = m_Circle_Center.y - m_Circle_Radius;
	rect.width = 2 * m_Circle_Radius + 1;
	rect.height = 2 * m_Circle_Radius + 1;
	if (rect.x<0 || rect.y<0 || rect.x + rect.width>src.cols || rect.y + rect.height>src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::circle(mask, m_Circle_Center, m_Circle_Radius, cvScalarAll(0xff), CV_FILLED);
	return DivisionResize(src, mask, dst, m_Circle_Division, m_Circle_Resize);
}

int ROI::AnnulusROI(Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (m_Annulus_Radius_Min <= 0 || m_Annulus_Radius_Max <= 0 || m_Annulus_Center.x <= 0
		|| m_Annulus_Center.y <= 0 || m_Annulus_Radius_Min == m_Annulus_Radius_Max)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	if (m_Annulus_Radius_Min > m_Annulus_Radius_Max)
	{
		int temp = m_Annulus_Radius_Min;
		m_Annulus_Radius_Min = m_Annulus_Radius_Max;
		m_Annulus_Radius_Max = temp;
	}
	CvRect rect;
	rect.x = m_Annulus_Center.x - m_Annulus_Radius_Max;
	rect.y = m_Annulus_Center.y - m_Annulus_Radius_Max;
	rect.width = 2 * m_Annulus_Radius_Max + 1;
	rect.height = 2 * m_Annulus_Radius_Max + 1;
	if (rect.x<0 || rect.y<0 || rect.x + rect.width>src.cols || rect.y + rect.height>src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::circle(mask, m_Annulus_Center, m_Annulus_Radius_Max, cvScalarAll(0xff), CV_FILLED);
	cv::circle(mask, m_Annulus_Center, m_Annulus_Radius_Min, cvScalarAll(0x00), CV_FILLED);
	return DivisionResize(src, mask, dst, m_Annulus_Division, m_Annulus_Resize);
}

int ROI::EllipseROI(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (m_Ellipse.angle < 0 || m_Ellipse.angle > 360 || m_Ellipse.center.x <= 0
		|| m_Ellipse.center.y <= 0 || m_Ellipse.size.width <= 0 || m_Ellipse.size.height <= 0)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	CvRect rect;
	cv::ellipse(mask, m_Ellipse, cvScalar(255));
	floodFill(mask, m_Ellipse.center, 255, NULL, cvScalarAll(0), cvScalarAll(0), CV_FLOODFILL_FIXED_RANGE);
	int rc = GetRect(mask, rect);
	if (rc != 0)
	{
		return rc;
	}
	if (rect.x<0 || rect.y<0 || rect.x + rect.width>src.cols || rect.y + rect.height>src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	return DivisionResize(src, mask, dst, m_Annulus_Division, m_Annulus_Resize);
}

int ROI::RotateRectROI(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (m_RotateRect.angle < 0 || m_RotateRect.angle > 360 || m_RotateRect.center.x <= 0
		|| m_RotateRect.center.y <= 0 || m_RotateRect.size.width <= 0 || m_RotateRect.size.height <= 0)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	CvRect rect;
	/*DrawBox(RotateRect, mask);
	floodFill(mask, Ellipse.center, 255, NULL, cvScalarAll(0), cvScalarAll(0), CV_FLOODFILL_FIXED_RANGE);*/
	DrawFillBox(mask, m_RotateRect);
	int rc = GetRect(mask, rect);
	if (rc != 0)
	{
		return rc;
	}
	if (rect.x<0 || rect.y<0 || rect.x + rect.width>src.cols || rect.y + rect.height>src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	return DivisionResize(src, mask, dst, m_Annulus_Division, m_Annulus_Resize);
}

int ROI::PolygonROI(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	int len = m_Polygon_X.size();
	if (len < 3)
	{
		dst = src.clone();
		return _PARAM_ERROR_;
	}
	vector<Point> point;
	vector<vector<Point>> PPoint;
	for (int i = 0; i < len; i++)
	{
		point.push_back(Point(m_Polygon_X[i], m_Polygon_Y[i]));
	}
	PPoint.push_back(point);
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	CvRect rect;
	fillPoly(mask, PPoint, cvScalarAll(0xff));
	int rc = GetRect(mask, rect);
	if (rc != 0)
	{
		return rc;
	}
	if (rect.x<0 || rect.y<0 || rect.x + rect.width>src.cols || rect.y + rect.height>src.rows)
	{
		dst = src.clone();
		return _ROI_OVERTOP_;
	}
	return DivisionResize(src, mask, dst, m_Annulus_Division, m_Annulus_Resize);
}

int ROI::GetRect(cv::Mat src, CvRect &rect)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	int m_left = src.cols;
	int m_top = src.rows;
	int m_right = 0;
	int m_bottom = 0;
	cv::Mat gray;
	if (src.channels() == 3)
	{
		cvtColor(src, gray, CV_BGR2GRAY);
	}
	else if (src.channels() == 1)
	{
		gray = src.clone();
	}
	else
	{
		return -1;
	}
	for (int i = 0; i < gray.rows; i++)
	{
		for (int j = 0; j < gray.cols; j++)
		{
			if (gray.at<uchar>(i, j) != 0)
			{
				if (j > m_right)
				{
					m_right = j;
				}
				if (j < m_left)
				{
					m_left = j;
				}
				if (i > m_bottom)
				{
					m_bottom = i;
				}
				if (i < m_top)
				{
					m_top = i;
				}
			}
		}
	}
	rect.x = m_left;
	rect.y = m_top;
	rect.width = m_right - m_left + 1;
	rect.height = m_bottom - m_top + 1;
	return 0;
}

int ROI::DivisionResize(cv::Mat src, cv::Mat mask, cv::Mat &dst, bool bDivision, CvSize size)
{
	if (src.empty() || mask.empty())
	{
		dst = src.clone();
		return _NO_IMAGE_;
	}
	if (bDivision)
	{
		cv::Mat temp;
		src.copyTo(temp, mask);
		CvRect	rect;
		GetRect(temp, rect);
		dst = temp(rect).clone();
		if (size.height > 0 && size.width > 0)
		{
			resize(dst, dst, size);
		}
	}
	else
	{
		src.copyTo(dst, mask);
	}
	return 0;
}

int ROI::CompareRect(CvRect &rect_min, CvRect &rect_max)
{
	int left_min = rect_min.x;
	int right_min = rect_min.x + rect_min.width - 1;
	int top_min = rect_min.y;
	int bottom_min = rect_min.y + rect_min.height - 1;
	int left_max = rect_max.x;
	int right_max = rect_max.x + rect_max.width - 1;
	int top_max = rect_max.y;
	int bottom_max = rect_max.y + rect_max.height - 1;
	if (right_min > right_max && left_min < left_max && top_min < top_max && bottom_min > bottom_max)
	{
		CvRect temp = rect_max;
		rect_max = rect_min;
		rect_min = temp;
		return 0;
	}
	if (right_min < right_max && left_min > left_max && top_min > top_max && bottom_min < bottom_max)
	{
		return 0;
	}
	else
	{
		return _PARAM_ERROR_;
	}
}

void ROI::DrawBox(CvBox2D box, Mat &img)
{
	CvPoint2D32f point[4];
	int i;
	for (i = 0; i<4; i++)

	{
		point[i].x = 0;
		point[i].y = 0;

	}
	cvBoxPoints(box, point); //计算二维盒子顶点
	CvPoint pt[4];
	for (i = 0; i<4; i++)
	{
		pt[i].x = (int)point[i].x;
		pt[i].y = (int)point[i].y;

	}
	line(img, pt[0], pt[1], cvScalar(255), 2, 8, 0);
	line(img, pt[1], pt[2], cvScalar(255), 2, 8, 0);
	line(img, pt[2], pt[3], cvScalar(255), 2, 8, 0);
	line(img, pt[3], pt[0], cvScalar(255), 2, 8, 0);
}

void ROI::DrawFillBox(cv::Mat &img, cv::RotatedRect box)
{
	Point2f point[4];
	box.points(point);
	vector<Point> pt;
	vector<vector<Point>> ppt;
	for (int i = 0; i<4; i++)
	{
		pt.push_back(point[i]);
	}
	ppt.push_back(pt);
	fillPoly(img, ppt, cvScalarAll(255));
	return;
}