#include "stdafx.h"
#include "Distance.h"

using namespace std;
using namespace cv;

Distance::Distance()
{
	m_pt2pt_Result = 0;
	m_pt2ln_Result = 0;
	m_ln2ln_Result = 0;
}

Distance::~Distance()
{
}

bool __stdcall Distance::Excute(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(POINT_2_POINT):
		if (CalcPt2PtDist(src, dst) < 0)
			return false;
		return true;
	case(POINT_2_LINE) :
		if (CalcPt2LnDist(src, dst) < 0)
			return false;
		return true;
	case(LINE_2_LINE) :
		if (CalcLn2LnDist(src, dst) < 0)
			return false;
		return true;
	default:
		break;
	}
}

int __stdcall Distance::Excute_(cv::Mat src, cv::Mat &dst, int option)
{
	switch (option)
	{
	case(POINT_2_POINT) :
		return CalcPt2PtDist(src, dst);
	case(POINT_2_LINE) :
		return CalcPt2LnDist(src, dst);
	case(LINE_2_LINE) :
		return CalcLn2LnDist(src, dst);
	default:
		break;
	}
}

int __stdcall Distance::SaveXML()
{
	FileStorage fs(_DIST_XML_FILE_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//Point2Point
	fs << "Point2Point" << "{" << "name" << "Point2Point" << "type" << 4 << "suntype" << POINT_2_POINT;
	fs << "m_pt2pt_ptS_X" << m_pt2pt_ptS.x;
	fs << "m_pt2pt_ptS_Y" << m_pt2pt_ptS.y;
	fs << "m_pt2pt_ptE_X" << m_pt2pt_ptE.x;
	fs << "m_pt2pt_ptE_Y" << m_pt2pt_ptE.y;
	fs << "m_pt2pt_AFlag" << m_pt2pt_AFlag;
	fs << "m_pt2pt_Angle" << m_pt2pt_Angle << "}";
	//Point2Line
	fs << "Point2Line" << "{" << "name" << "Point2Line" << "type" << 4 << "suntype" << POINT_2_LINE;
	fs << "m_pt2ln_ptS_X" << m_pt2ln_ptS.x;
	fs << "m_pt2ln_ptS_Y" << m_pt2ln_ptS.y;
	fs << "m_pt2ln_lnS_X" << m_pt2ln_lnS.x;
	fs << "m_pt2ln_lnS_Y" << m_pt2ln_lnS.y;
	fs << "m_pt2ln_lnE_X" << m_pt2ln_lnE.x;
	fs << "m_pt2ln_lnE_Y" << m_pt2ln_lnE.y;
	fs << "m_pt2ln_AFlag" << m_pt2ln_AFlag;
	fs << "m_pt2ln_Angle" << m_pt2ln_Angle << "}";
	//Line2Line
	fs << "Line2Line" << "{" << "name" << "Line2Line" << "type" << 4 << "suntype" << LINE_2_LINE;
	fs << "m_ln2ln_lnSS_X" << m_ln2ln_lnSS.x;
	fs << "m_ln2ln_lnSS_Y" << m_ln2ln_lnSS.y;
	fs << "m_ln2ln_lnSE_X" << m_ln2ln_lnSE.x;
	fs << "m_ln2ln_lnSE_Y" << m_ln2ln_lnSE.y;
	fs << "m_ln2ln_lnES_X" << m_ln2ln_lnES.x;
	fs << "m_ln2ln_lnES_Y" << m_ln2ln_lnES.y;
	fs << "m_ln2ln_lnEE_X" << m_ln2ln_lnEE.x;
	fs << "m_ln2ln_lnEE_Y" << m_ln2ln_lnEE.y;
	fs << "m_ln2ln_Gap" << m_ln2ln_Gap << "}";
	fs.release();
	return 0;
}

int __stdcall Distance::SaveXML(char* filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//Point2Point
	fs << "Point2Point" << "{" << "name" << "Point2Point" << "type" << 4 << "suntype" << POINT_2_POINT;
	fs << "m_pt2pt_ptS_X" << m_pt2pt_ptS.x;
	fs << "m_pt2pt_ptS_Y" << m_pt2pt_ptS.y;
	fs << "m_pt2pt_ptE_X" << m_pt2pt_ptE.x;
	fs << "m_pt2pt_ptE_Y" << m_pt2pt_ptE.y;
	fs << "m_pt2pt_AFlag" << m_pt2pt_AFlag;
	fs << "m_pt2pt_Angle" << m_pt2pt_Angle << "}";
	//Point2Line
	fs << "Point2Line" << "{" << "name" << "Point2Line" << "type" << 4 << "suntype" << POINT_2_LINE;
	fs << "m_pt2ln_ptS_X" << m_pt2ln_ptS.x;
	fs << "m_pt2ln_ptS_Y" << m_pt2ln_ptS.y;
	fs << "m_pt2ln_lnS_X" << m_pt2ln_lnS.x;
	fs << "m_pt2ln_lnS_Y" << m_pt2ln_lnS.y;
	fs << "m_pt2ln_lnE_X" << m_pt2ln_lnE.x;
	fs << "m_pt2ln_lnE_Y" << m_pt2ln_lnE.y;
	fs << "m_pt2ln_AFlag" << m_pt2ln_AFlag;
	fs << "m_pt2ln_Angle" << m_pt2ln_Angle << "}";
	//Line2Line
	fs << "Line2Line" << "{" << "name" << "Line2Line" << "type" << 4 << "suntype" << LINE_2_LINE;
	fs << "m_ln2ln_lnSS_X" << m_ln2ln_lnSS.x;
	fs << "m_ln2ln_lnSS_Y" << m_ln2ln_lnSS.y;
	fs << "m_ln2ln_lnSE_X" << m_ln2ln_lnSE.x;
	fs << "m_ln2ln_lnSE_Y" << m_ln2ln_lnSE.y;
	fs << "m_ln2ln_lnES_X" << m_ln2ln_lnES.x;
	fs << "m_ln2ln_lnES_Y" << m_ln2ln_lnES.y;
	fs << "m_ln2ln_lnEE_X" << m_ln2ln_lnEE.x;
	fs << "m_ln2ln_lnEE_Y" << m_ln2ln_lnEE.y;
	fs << "m_ln2ln_Gap" << m_ln2ln_Gap << "}";
	fs.release();
	return 0;
}

int __stdcall Distance::LoadXML()
{
	FileStorage fs(_DIST_XML_FILE_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode pt2pt = fs["Point2Point"];
	m_pt2pt_ptS.x = pt2pt["m_pt2pt_ptS_X"];
	m_pt2pt_ptS.y = pt2pt["m_pt2pt_ptS_Y"];
	m_pt2pt_ptE.x = pt2pt["m_pt2pt_ptE_X"];
	m_pt2pt_ptE.y = pt2pt["m_pt2pt_ptE_Y"];
	m_pt2pt_AFlag = (int)pt2pt["m_pt2pt_AFlag"];
	m_pt2pt_Angle = pt2pt["m_pt2pt_Angle"];
	FileNode pt2ln = fs["Point2Line"];
	m_pt2ln_ptS.x = pt2ln["m_pt2ln_ptS_X"];
	m_pt2ln_ptS.y = pt2ln["m_pt2ln_ptS_Y"];
	m_pt2ln_lnS.x = pt2ln["m_pt2ln_lnS_X"];
	m_pt2ln_lnS.y = pt2ln["m_pt2ln_lnS_Y"];
	m_pt2ln_lnE.x = pt2ln["m_pt2ln_lnE_X"];
	m_pt2ln_lnE.y = pt2ln["m_pt2ln_lnE_Y"];
	m_pt2ln_AFlag = (int)pt2ln["m_pt2ln_AFlag"];
	m_pt2ln_Angle = pt2ln["m_pt2ln_Angle"];
	FileNode ln2ln = fs["Line2Line"];
	m_ln2ln_lnSS.x = ln2ln["m_ln2ln_lnSS_X"];
	m_ln2ln_lnSS.y = ln2ln["m_ln2ln_lnSS_Y"];
	m_ln2ln_lnSE.x = ln2ln["m_ln2ln_lnSE_X"];
	m_ln2ln_lnSE.y = ln2ln["m_ln2ln_lnSE_Y"];
	m_ln2ln_lnES.x = ln2ln["m_ln2ln_lnES_X"];
	m_ln2ln_lnES.y = ln2ln["m_ln2ln_lnES_Y"];
	m_ln2ln_lnEE.x = ln2ln["m_ln2ln_lnEE_X"];
	m_ln2ln_lnEE.y = ln2ln["m_ln2ln_lnEE_Y"];
	m_ln2ln_Gap = ln2ln["m_ln2ln_Gap"];
	fs.release();
	return 0;
}

int __stdcall Distance::LoadXML(char* filename)
{
	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode pt2pt = fs["Point2Point"];
	m_pt2pt_ptS.x = pt2pt["m_pt2pt_ptS_X"];
	m_pt2pt_ptS.y = pt2pt["m_pt2pt_ptS_Y"];
	m_pt2pt_ptE.x = pt2pt["m_pt2pt_ptE_X"];
	m_pt2pt_ptE.y = pt2pt["m_pt2pt_ptE_Y"];
	m_pt2pt_AFlag = (int)pt2pt["m_pt2pt_AFlag"];
	m_pt2pt_Angle = pt2pt["m_pt2pt_Angle"];
	FileNode pt2ln = fs["Point2Line"];
	m_pt2ln_ptS.x = pt2ln["m_pt2ln_ptS_X"];
	m_pt2ln_ptS.y = pt2ln["m_pt2ln_ptS_Y"];
	m_pt2ln_lnS.x = pt2ln["m_pt2ln_lnS_X"];
	m_pt2ln_lnS.y = pt2ln["m_pt2ln_lnS_Y"];
	m_pt2ln_lnE.x = pt2ln["m_pt2ln_lnE_X"];
	m_pt2ln_lnE.y = pt2ln["m_pt2ln_lnE_Y"];
	m_pt2ln_AFlag = (int)pt2ln["m_pt2ln_AFlag"];
	m_pt2ln_Angle = pt2ln["m_pt2ln_Angle"];
	FileNode ln2ln = fs["Line2Line"];
	m_ln2ln_lnSS.x = ln2ln["m_ln2ln_lnSS_X"];
	m_ln2ln_lnSS.y = ln2ln["m_ln2ln_lnSS_Y"];
	m_ln2ln_lnSE.x = ln2ln["m_ln2ln_lnSE_X"];
	m_ln2ln_lnSE.y = ln2ln["m_ln2ln_lnSE_Y"];
	m_ln2ln_lnES.x = ln2ln["m_ln2ln_lnES_X"];
	m_ln2ln_lnES.y = ln2ln["m_ln2ln_lnES_Y"];
	m_ln2ln_lnEE.x = ln2ln["m_ln2ln_lnEE_X"];
	m_ln2ln_lnEE.y = ln2ln["m_ln2ln_lnEE_Y"];
	m_ln2ln_Gap = ln2ln["m_ln2ln_Gap"];
	fs.release();
	return 0;
}

//private:
int Distance::CalcPt2PtDist(cv::Mat src, cv::Mat &dst)
{
	if (m_pt2pt_AFlag)
	{
		double len = sqrt(pow(m_pt2pt_ptS.x - m_pt2pt_ptE.x, 2) + pow(m_pt2pt_ptS.y - m_pt2pt_ptE.y, 2));
		m_pt2pt_Result = len*cos(m_pt2pt_Angle*CV_PI / 180);
	}
	else
	{
		m_pt2pt_Result = sqrt(pow(m_pt2pt_ptS.x - m_pt2pt_ptE.x, 2) + pow(m_pt2pt_ptS.y - m_pt2pt_ptE.y, 2));
	}
	if (src.empty())
		dst = Mat::Mat(500, 1000, CV_8UC3, cvScalarAll(0xff));
	if (src.channels() == 3)
		dst = src.clone();
	else if (src.channels() == 1)
		cvtColor(src, dst, CV_GRAY2BGR);
	else 
		dst = Mat::Mat(500, 1000, CV_8UC3, cvScalarAll(0xff));
	line(dst, m_pt2pt_ptS, m_pt2pt_ptE, CV_RGB(255, 0, 0), 2);
	return 0;
}

int Distance::CalcPt2LnDist(cv::Mat src, cv::Mat &dst)
{
	double AB = sqrt(pow(m_pt2ln_ptS.x - m_pt2ln_lnS.x, 2) + pow(m_pt2ln_ptS.y - m_pt2ln_lnS.y, 2));
	double AC = sqrt(pow(m_pt2ln_ptS.x - m_pt2ln_lnE.x, 2) + pow(m_pt2ln_ptS.y - m_pt2ln_lnE.y, 2));
	double BC = sqrt(pow(m_pt2ln_lnS.x - m_pt2ln_lnE.x, 2) + pow(m_pt2ln_lnS.y - m_pt2ln_lnE.y, 2));
	double S = (sqrt((AB + AC + BC)*(AB + AC - BC)*(AB + BC - AC)*(AC + BC - AB))) / 4;
	double h = 2 * S / BC;
	//S = 0.5*BC*h;
	if (m_pt2ln_AFlag)
	{
		h = h*cos(m_pt2ln_Angle*CV_PI / 180);
	}
	m_pt2ln_Result = h;
	if (src.empty())
		dst = Mat::Mat(500, 1000, CV_8UC3, cvScalarAll(0xff));
	if (src.channels() == 3)
		dst = src.clone();
	else if (src.channels() == 1)
		cvtColor(src, dst, CV_GRAY2BGR);
	else
		dst = Mat::Mat(500, 1000, CV_8UC3, cvScalarAll(0xff));
	line(dst, m_pt2pt_ptS, m_pt2pt_ptE, CV_RGB(255, 0, 0), 2);
	return 0;
}

int Distance::CalcLn2LnDist(cv::Mat src, cv::Mat &dst)
{
	double AB = sqrt(pow(m_ln2ln_lnSS.x - m_ln2ln_lnES.x, 2) + pow(m_ln2ln_lnSS.y - m_ln2ln_lnES.y, 2));
	double AC = sqrt(pow(m_ln2ln_lnSS.x - m_ln2ln_lnEE.x, 2) + pow(m_ln2ln_lnSS.y - m_ln2ln_lnEE.y, 2));
	double BC = sqrt(pow(m_ln2ln_lnES.x - m_ln2ln_lnEE.x, 2) + pow(m_ln2ln_lnES.y - m_ln2ln_lnEE.y, 2));
	double DB = sqrt(pow(m_ln2ln_lnSE.x - m_ln2ln_lnES.x, 2) + pow(m_ln2ln_lnSE.y - m_ln2ln_lnES.y, 2));
	double DC = sqrt(pow(m_ln2ln_lnSE.x - m_ln2ln_lnEE.x, 2) + pow(m_ln2ln_lnSE.y - m_ln2ln_lnEE.y, 2));
	double Sabc = (sqrt((AB + AC + BC)*(AB + AC - BC)*(AB + BC - AC)*(AC + BC - AB))) / 4;
	double Sbcd = (sqrt((DB + DC + BC)*(DB + DC - BC)*(DB + BC - DC)*(DC + BC - DB))) / 4;
	double habc = 2 * Sabc / BC;
	double hbcd = 2 * Sbcd / BC;
	if (fabs(habc - hbcd) < m_ln2ln_Gap)
	{
		m_ln2ln_Result = (habc + hbcd) / 2;
		if (src.empty())
			dst = Mat::Mat(500, 1000, CV_8UC3, cvScalarAll(0xff));
		if (src.channels() == 3)
			dst = src.clone();
		else if (src.channels() == 1)
			cvtColor(src, dst, CV_GRAY2BGR);
		else
			dst = Mat::Mat(500, 1000, CV_8UC3, cvScalarAll(0xff));
		line(dst, m_pt2pt_ptS, m_pt2pt_ptE, CV_RGB(255, 0, 0), 2);
		return 0;
	}
	else 
		return _PARAM_ERROR_;
}