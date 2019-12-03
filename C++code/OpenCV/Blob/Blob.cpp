#include "stdafx.h"
#include "Blob.h"

using namespace std;
using namespace cv;

Blob::Blob()
{
}

Blob::~Blob()
{
}

bool __stdcall Blob::Excute(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(DRAW_CONTOURS):
		if (DrawContours(src, dst) != 0)
		{
			return false;
		}
		return true;
	case(DRAW_CONTOURS_CVBOX):
		if (DrawContourRotateRect(src, dst) != 0)
		{
			return false;
		}
		return true;
	default:
		return false;
	}
}

int __stdcall Blob::Excute_(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(DRAW_CONTOURS) :
		return DrawContours(src, dst);
	case(DRAW_CONTOURS_CVBOX) :
		return DrawContourRotateRect(src, dst);
	default:
		return _PARAM_ERROR_;
	}
}

int __stdcall Blob::SaveXML()
{
	FileStorage fs(_BLOB_XML_FILE_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//DrawContours
	fs << "DrawContours" << "{" << "name" << "DrawContours" << "type" << 1 << "suntype" << DRAW_CONTOURS;
	fs << "Contour_Thre" << m_Contour_Thre;
	fs << "Contour_Blur_Size" << m_Contour_BlurSize;
	fs << "Contour_Mode" << m_Contour_Mode;
	fs << "Contour_Color_B" << m_Contour_Color.val[0];
	fs << "Contour_Color_G" << m_Contour_Color.val[1];
	fs << "Contour_Color_R" << m_Contour_Color.val[2];
	fs << "Contour_Thickness" << m_Contour_Thickness << "}";
	//DrawCvBox
	fs << "DrawCvBox" << "{" << "name" << "DrawCvBox" << "type" << 1 << "suntype" << DRAW_CONTOURS_CVBOX;
	fs << "CvBox_Thre" << m_CvBox_Thre;
	fs << "CvBox_Blur_Size" << m_CvBox_BlurSize;
	fs << "CvBox_Mode" << m_CvBox_Mode;
	fs << "CvBox_Color_B" << m_CvBox_Color.val[0];
	fs << "CvBox_Color_G" << m_CvBox_Color.val[1];
	fs << "CvBox_Color_R" << m_CvBox_Color.val[2];
	fs << "CvBox_Thickness" << m_CvBox_Thickness << "}";
	fs.release();
	return 0;
}

int __stdcall Blob::SaveXML(char* filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//DrawContours
	fs << "DrawContours" << "{" << "name" << "DrawContours" << "type" << 1 << "suntype" << DRAW_CONTOURS;
	fs << "Contour_Thre" << m_Contour_Thre;
	fs << "Contour_Blur_Size" << m_Contour_BlurSize;
	fs << "Contour_Mode" << m_Contour_Mode;
	fs << "Contour_Color_B" << m_Contour_Color.val[0];
	fs << "Contour_Color_G" << m_Contour_Color.val[1];
	fs << "Contour_Color_R" << m_Contour_Color.val[2];
	fs << "Contour_Thickness" << m_Contour_Thickness << "}";
	//DrawCvBox
	fs << "DrawCvBox" << "{" << "name" << "DrawCvBox" << "type" << 1 << "suntype" << DRAW_CONTOURS_CVBOX;
	fs << "CvBox_Thre" << m_CvBox_Thre;
	fs << "CvBox_Blur_Size" << m_CvBox_BlurSize;
	fs << "CvBox_Mode" << m_CvBox_Mode;
	fs << "CvBox_Color_B" << m_CvBox_Color.val[0];
	fs << "CvBox_Color_G" << m_CvBox_Color.val[1];
	fs << "CvBox_Color_R" << m_CvBox_Color.val[2];
	fs << "CvBox_Thickness" << m_CvBox_Thickness << "}";
	fs.release();
	return 0;
}

int __stdcall Blob::LoadXML()
{
	FileStorage fs(_BLOB_XML_FILE_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode Contour_Draw = fs["DrawContours"];
	m_Contour_Thre = Contour_Draw["Contour_Thre"];
	m_Contour_BlurSize = Contour_Draw["Contour_Blur_Size"];
	m_Contour_Mode = Contour_Draw["Contour_Mode"];
	m_Contour_Thickness = Contour_Draw["Contour_Thickness"];
	int cb = Contour_Draw["Contour_Color_B"];
	int cg = Contour_Draw["Contour_Color_G"];
	int cr = Contour_Draw["Contour_Color_R"];
	m_Contour_Color = Scalar(cb, cg, cr);
	FileNode CvBox_Draw = fs["DrawCvBox"];
	m_CvBox_Thre = CvBox_Draw["CvBox_Thre"];
	m_CvBox_BlurSize = CvBox_Draw["CvBox_Blur_Size"];
	m_CvBox_Mode = CvBox_Draw["CvBox_Mode"];
	m_CvBox_Thickness = CvBox_Draw["CvBox_Thickness"];
	int rb = CvBox_Draw["CvBox_Color_B"];
	int rg = CvBox_Draw["CvBox_Color_G"];
	int rr = CvBox_Draw["CvBox_Color_R"];
	m_CvBox_Color = Scalar(rb, rg, rr);
	fs.release();
	return 0;
}

int __stdcall Blob::LoadXML(char* filename)
{
	FileStorage fs(_BLOB_XML_FILE_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode Contour_Draw = fs["DrawContours"];
	m_Contour_Thre = Contour_Draw["Contour_Thre"];
	m_Contour_BlurSize = Contour_Draw["Contour_Blur_Size"];
	m_Contour_Mode = Contour_Draw["Contour_Mode"];
	m_Contour_Thickness = Contour_Draw["Contour_Thickness"];
	int cb = Contour_Draw["Contour_Color_B"];
	int cg = Contour_Draw["Contour_Color_G"];
	int cr = Contour_Draw["Contour_Color_R"];
	m_Contour_Color = Scalar(cb, cg, cr);
	FileNode CvBox_Draw = fs["DrawCvBox"];
	m_CvBox_Thre = CvBox_Draw["CvBox_Thre"];
	m_CvBox_BlurSize = CvBox_Draw["CvBox_Blur_Size"];
	m_CvBox_Mode = CvBox_Draw["CvBox_Mode"];
	m_CvBox_Thickness = CvBox_Draw["CvBox_Thickness"];
	int rb = CvBox_Draw["CvBox_Color_B"];
	int rg = CvBox_Draw["CvBox_Color_G"];
	int rr = CvBox_Draw["CvBox_Color_R"];
	m_CvBox_Color = Scalar(rb, rg, rr);
	fs.release();
	return 0;
}

//private:
int Blob::DrawContours(cv::Mat src, cv::Mat &dst)
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
	cv::threshold(gray, gray, m_Contour_Thre, 0xff, m_Contour_Mode);
	if (m_Contour_BlurSize % 2 == 0)
	{
		m_Contour_BlurSize++;
	}
	cv::Mat element(m_Contour_BlurSize, m_Contour_BlurSize, CV_8U, cv::Scalar(1));
	cv::morphologyEx(gray, gray, cv::MORPH_OPEN, element);
	cv::morphologyEx(gray, gray, cv::MORPH_CLOSE, element);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	cv::drawContours(dst, contours,
		-1,//画全部轮廓
		m_Contour_Color,
		m_Contour_Thickness);//宽度为2
	return 0;
}

int Blob::DrawContourRotateRect(cv::Mat src, cv::Mat &dst)
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
	cv::threshold(gray, gray, m_CvBox_Thre, 0xff, m_CvBox_Mode);
	if (m_CvBox_BlurSize % 2 == 0)
	{
		m_CvBox_BlurSize++;
	}
	cv::Mat element(m_CvBox_BlurSize, m_CvBox_BlurSize, CV_8U, cv::Scalar(1));
	cv::morphologyEx(gray, gray, cv::MORPH_OPEN, element);
	cv::morphologyEx(gray, gray, cv::MORPH_CLOSE, element);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	RotatedRect rect;
	for (size_t i = 0; i < contours.size(); i++)
	{
		rect = cv::minAreaRect(contours[i]);
		DrawBox(rect, dst, m_CvBox_Color);
	}
	return 0;
}

void Blob::DrawBox(CvBox2D box, cv::Mat &dst, cv::Scalar color)
{
	CvPoint2D32f point[4];
	int i;
	for (i = 0; i<4; i++)

	{
		point[i].x = 0;
		point[i].y = 0;

	}
	cvBoxPoints(box, point); //计算二维盒子顶点
	vector<Point> pt;
	vector<vector<Point>> ppt;
	for (i = 0; i<4; i++)
	{
		pt.push_back(point[i]);
	}
	ppt.push_back(pt);
	if (m_CvBox_Thickness == CV_FILLED)
	{
		fillPoly(dst, ppt, m_CvBox_Color);
	}
	else
	{
		polylines(dst, ppt, true, m_CvBox_Color, m_CvBox_Thickness);
	}
	return;
}