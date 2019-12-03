#include "stdafx.h"
#include "Match.h"

using namespace std;
using namespace cv;

Match::Match()
{
	/*m_Gray_Method = TM_CCOEFF_NORMED;
	m_Gray_Thickness = 1;
	m_Gray_Color = Scalar(0, 255, 0);

	m_Pyr_Scale = 0.5;
	m_Pyr_Method = TM_CCOEFF_NORMED;
	m_Pyr_Thickness = 1;
	m_Pyr_Color = Scalar(0, 255, 0);

	m_Rotate_Method = THRE_BK_WHITE;
	m_Rotate_Thickness = 3;
	m_Rotate_Color = Scalar(0, 255, 0);;*/
}

Match::~Match()
{
}

bool __stdcall Match::Excute(cv::Mat src, cv::Mat &dst, int method)
{
	switch (method)
	{
	case(MATCH_GRAY):
		if (MatchGrayImage(src, dst) != 0)
			return false;
		return true;
	case(MATCH_PYR) :
		if (MatchPyrImage(src, dst) != 0)
			return false;
		return true;
	case(MATCH_ROTATE) :
		if (MatchRotateImage(src, dst) != 0)
			return false;
		return true;
	default:
		return false;
	}
}

int __stdcall Match::Excute_(cv::Mat src, cv::Mat &dst, int method)
{
	switch (method)
	{
	case(MATCH_GRAY) :
		return MatchGrayImage(src, dst);
	case(MATCH_PYR) :
		return MatchPyrImage(src, dst);
	case(MATCH_ROTATE) :
		return MatchRotateImage(src, dst);
	default:
		return 0;
	}
}

int __stdcall Match::SaveXML()
{
	FileStorage fs(_MATCH_XML_FILE_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	//MatchGray
	fs << "MatchGray" << "{" << "name" << "MatchGray" << "type" << 5 << "suntype" << MATCH_GRAY;
	fs << "m_Gray_Method" << m_Gray_Method;
	fs << "m_Gray_Thickness" << m_Gray_Thickness;
	fs << "m_Gray_Color_B" << m_Gray_Color[0];
	fs << "m_Gray_Color_G" << m_Gray_Color[1];
	fs << "m_Gray_Color_R" << m_Gray_Color[2]<< "}";
	//MatchPyr
	fs << "MatchPyr" << "{" << "name" << "MatchPyr" << "type" << 5 << "suntype" << MATCH_PYR;
	fs << "m_Pyr_Scale" << m_Pyr_Scale;
	fs << "m_Pyr_Method" << m_Pyr_Method;
	fs << "m_Pyr_Thickness" << m_Pyr_Thickness;
	fs << "m_Pyr_Color_B" << m_Pyr_Color[0];
	fs << "m_Pyr_Color_G" << m_Pyr_Color[1];
	fs << "m_Pyr_Color_R" << m_Pyr_Color[2] << "}";
	//MatchRotate
	fs << "MatchRotate" << "{" << "name" << "MatchRotate" << "type" << 5 << "suntype" << MATCH_ROTATE;
	fs << "m_Rotate_Method" << m_Rotate_Method;
	fs << "m_Rotate_Thickness" << m_Rotate_Thickness;
	fs << "m_Rotate_Color_B" << m_Rotate_Color[0];
	fs << "m_Rotate_Color_G" << m_Rotate_Color[1];
	fs << "m_Rotate_Color_R" << m_Rotate_Color[2] << "}";
	fs.release();
	return 0;
}

int __stdcall Match::SaveXML(char* filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	fs << "Templ_Path" << m_Templ_Path;
	//MatchGray
	fs << "MatchGray" << "{" << "name" << "MatchGray" << "type" << 5 << "suntype" << MATCH_GRAY;
	fs << "m_Gray_Method" << m_Gray_Method;
	fs << "m_Gray_Thickness" << m_Gray_Thickness;
	fs << "m_Gray_Color_B" << m_Gray_Color[0];
	fs << "m_Gray_Color_G" << m_Gray_Color[1];
	fs << "m_Gray_Color_R" << m_Gray_Color[2] << "}";
	//MatchPyr
	fs << "MatchPyr" << "{" << "name" << "MatchPyr" << "type" << 5 << "suntype" << MATCH_PYR;
	fs << "m_Pyr_Scale" << m_Pyr_Scale;
	fs << "m_Pyr_Method" << m_Pyr_Method;
	fs << "m_Pyr_Thickness" << m_Pyr_Thickness;
	fs << "m_Pyr_Color_B" << m_Pyr_Color[0];
	fs << "m_Pyr_Color_G" << m_Pyr_Color[1];
	fs << "m_Pyr_Color_R" << m_Pyr_Color[2] << "}";
	//MatchRotate
	fs << "MatchRotate" << "{" << "name" << "MatchRotate" << "type" << 5 << "suntype" << MATCH_ROTATE;
	fs << "m_Rotate_Method" << m_Rotate_Method;
	fs << "m_Rotate_Thickness" << m_Rotate_Thickness;
	fs << "m_Rotate_Color_B" << m_Rotate_Color[0];
	fs << "m_Rotate_Color_G" << m_Rotate_Color[1];
	fs << "m_Rotate_Color_R" << m_Rotate_Color[2] << "}";
	fs.release();
	return 0;
}

int __stdcall Match::LoadXML()
{
	FileStorage fs(_MATCH_XML_FILE_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	FileNode GrayNode = fs["MatchGray"];
	m_Gray_Method = GrayNode["m_Gray_Method"];
	m_Gray_Thickness = GrayNode["m_Gray_Thickness"];
	m_Gray_Color[0] = GrayNode["m_Gray_Color_B"];
	m_Gray_Color[1] = GrayNode["m_Gray_Color_G"];
	m_Gray_Color[2] = GrayNode["m_Gray_Color_R"];
	FileNode PyrNode = fs["MatchPyr"];
	m_Pyr_Scale = PyrNode["m_Pyr_Scale"];
	m_Pyr_Method = PyrNode["m_Pyr_Method"];
	m_Pyr_Thickness = PyrNode["m_Pyr_Thickness"];
	m_Pyr_Color[0] = PyrNode["m_Pyr_Color_B"];
	m_Pyr_Color[1] = PyrNode["m_Pyr_Color_G"];
	m_Pyr_Color[2] = PyrNode["m_Pyr_Color_R"];
	FileNode RotateNode = fs["MatchRotate"];
	m_Rotate_Method = RotateNode["m_Rotate_Method"];
	m_Rotate_Thickness = RotateNode["m_Rotate_Thickness"];
	m_Rotate_Color[0] = RotateNode["m_Rotate_Color_B"];
	m_Rotate_Color[1] = RotateNode["m_Rotate_Color_G"];
	m_Rotate_Color[2] = RotateNode["m_Rotate_Color_R"];
	fs.release();
	return 0;
}

int __stdcall Match::LoadXML(char* filename)
{
	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	m_Templ_Path = fs["Templ_Path"];
	FileNode GrayNode = fs["MatchGray"];
	m_Gray_Method = GrayNode["m_Gray_Method"];
	m_Gray_Thickness = GrayNode["m_Gray_Thickness"];
	m_Gray_Color[0] = GrayNode["m_Gray_Color_B"];
	m_Gray_Color[1] = GrayNode["m_Gray_Color_G"];
	m_Gray_Color[2] = GrayNode["m_Gray_Color_R"];
	FileNode PyrNode = fs["MatchPyr"];
	m_Pyr_Scale = PyrNode["m_Pyr_Scale"];
	m_Pyr_Method = PyrNode["m_Pyr_Method"];
	m_Pyr_Thickness = PyrNode["m_Pyr_Thickness"];
	m_Pyr_Color[0] = PyrNode["m_Pyr_Color_B"];
	m_Pyr_Color[1] = PyrNode["m_Pyr_Color_G"];
	m_Pyr_Color[2] = PyrNode["m_Pyr_Color_R"];
	FileNode RotateNode = fs["MatchRotate"];
	m_Rotate_Method = RotateNode["m_Rotate_Method"];
	m_Rotate_Thickness = RotateNode["m_Rotate_Thickness"];
	m_Rotate_Color[0] = RotateNode["m_Rotate_Color_B"];
	m_Rotate_Color[1] = RotateNode["m_Rotate_Color_G"];
	m_Rotate_Color[2] = RotateNode["m_Rotate_Color_R"];
	fs.release();
	templ = imread(m_Templ_Path);
	if (templ.empty())
		return -1;
	return 0;
}

bool __stdcall Match::SetTemplate(char* file)
{
	m_Templ_Path = file;
	templ = imread(m_Templ_Path);
	if (templ.empty())
		return false;
	return true;
}

//private:
int Match::MatchGrayImage(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat src_g, templ_g;
	if (src.channels() == 3)
	{
		dst = src.clone();
		cvtColor(src, src_g, CV_BGR2GRAY);
	}
	else if (src.channels() == 1)
	{
		cvtColor(src, dst, CV_GRAY2BGR);
		src_g = src.clone();
	}
	else
		return _PARAM_ERROR_;
	if (templ.channels() == 3)
		cvtColor(templ, templ_g, CV_BGR2GRAY);
	else if (templ.channels() == 1)
		templ_g = templ.clone();
	else
		return _PARAM_ERROR_;
	Mat result;
	matchTemplate(src_g, templ_g, result, TM_CCOEFF_NORMED);
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	CvRect rect(maxLoc.x, maxLoc.y, templ.cols, templ.rows);
	rectangle(dst, rect, m_Gray_Color, m_Gray_Thickness);
	return 0;
}

int Match::MatchPyrImage(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	if (m_Pyr_Scale > 1.0)
		return _PARAM_ERROR_;
	Mat src_g, templ_g;
	if (src.channels() == 3)
	{
		dst = src.clone();
		cvtColor(src, src_g, CV_BGR2GRAY);
	}
	else if (src.channels() == 1)
	{
		cvtColor(src, dst, CV_GRAY2BGR);
		src_g = src.clone();
	}
	else
		return _PARAM_ERROR_;
	if (templ.channels() == 3)
		cvtColor(templ, templ_g, CV_BGR2GRAY);
	else if (templ.channels() == 1)
		templ_g = templ.clone();
	else
		return _PARAM_ERROR_;
	double scale = m_Pyr_Scale;
	Mat src_s = src_g.clone(), templ_s = templ_g.clone();
	while (true)
	{
		if (scale == 1)
		{
			break;
		}
		if (scale < 0.5)
		{
			pyrDown(src_s, src_s);
			pyrDown(templ_s, templ_s);
			scale = 2 * scale;
		}
		else
		{
			resize(src_s, src_s, cvSize(src_s.cols, src_s.rows));
			resize(templ_s, templ_s, cvSize(templ_s.cols, templ_s.rows));
			break;
		}
	}
	Mat result;
	matchTemplate(src_s, templ_s, result, TM_CCOEFF_NORMED);
	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	CvRect rect(maxLoc.x / m_Pyr_Scale, maxLoc.y / m_Pyr_Scale, templ.cols, templ.rows);
	rectangle(dst, rect, m_Pyr_Color, m_Pyr_Thickness);
	return 0;
}

int Match::MatchRotateImage(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
	if (src.channels() == 3)
		dst = src.clone();
	else if (src.channels() == 1)
		cv::cvtColor(src, dst, CV_GRAY2BGR);
	else
		return _PARAM_ERROR_;
	Mat src_b, templ_b;
	int blursz = 5;
	int Best_Count = 30;
	blur(src, src_b, cvSize(blursz, blursz));
	blur(templ, templ_b, cvSize(blursz, blursz));
	vector<KeyPoint> keyPoints_1, keyPoints_2;
	Mat descriptors_1, descriptors_2;
	//Ptr<FeatureDetector> orb = ORB::create();
	//Ptr<FeatureDetector> orb = FastFeatureDetector::create();
	orb->detectAndCompute(src_b, Mat(), keyPoints_1, descriptors_1);
	orb->detectAndCompute(templ_b, Mat(), keyPoints_2, descriptors_2);
	vector< DMatch > matches;
	matcher.match(descriptors_1, descriptors_2, matches);
	vector< DMatch > good_matches;
	
	//匹配结果筛选
	nth_element(matches.begin(), matches.begin() + Best_Count - 1, matches.end());   //提取出前30个最佳匹配结果     
	matches.erase(matches.begin() + Best_Count, matches.end());    //剔除掉其余的匹配结果
	int cen_x = 0, cen_y = 0;
	int cen_x2 = 0, cen_y2 = 0;
	vector<Point> pt1, pt2;
	for (int i = 0; i < Best_Count; i++)
	{
		pt1.push_back(keyPoints_1[matches[i].queryIdx].pt);
		pt2.push_back(keyPoints_2[matches[i].trainIdx].pt);
		cen_x += keyPoints_1[matches[i].queryIdx].pt.x;
		cen_y += keyPoints_1[matches[i].queryIdx].pt.y;
		cen_x2 += keyPoints_2[matches[i].trainIdx].pt.x;
		cen_y2 += keyPoints_2[matches[i].trainIdx].pt.y;
	}
	RotatedRect rt1, rt2;
	rt1 = minAreaRect(pt1);
	rt2 = minAreaRect(pt2);
	double sub = fabs(rt2.angle - rt1.angle);
	Mat templ_g;
	if (templ_b.channels() == 3)
		cv::cvtColor(templ_b, templ_g, CV_BGR2GRAY);
	else if (templ_b.channels() == 1)
		templ_g = templ_b.clone();
	else
		return _PARAM_ERROR_;
	if (m_Rotate_Method == THRE_BK_BALCK)
		cv::threshold(templ_g, templ_g, 50, 0xff, CV_THRESH_BINARY);
	else if (m_Rotate_Method == THRE_BK_WHITE)
		cv::threshold(templ_g, templ_g, 200, 0xff, CV_THRESH_BINARY_INV);
	else
		return _PARAM_ERROR_;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(templ_g, contours, CV_RETR_EXTERNAL,//检索外部轮廓
		CV_CHAIN_APPROX_NONE);//每个轮廓的全部像素
	double maxa = 0.0;
	int indx = 0;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area>maxa)
		{
			indx = 0;
			maxa = area;
		}
	}
	RotatedRect rt3 = minAreaRect(contours[indx]);
	RotatedRect Rrect;
	Rrect.size = rt3.size;
	Rrect.angle = rt3.angle - (rt2.angle - rt1.angle);
	Rrect.center.x = rt1.center.x + (templ_b.cols / 2) - rt2.center.x;
	Rrect.center.y = rt1.center.y + (templ_b.rows / 2) - rt2.center.y;
	rotateRect(dst, Rrect, m_Rotate_Color, m_Rotate_Thickness);
	return 0;
}

void Match::rotateRect(cv::Mat &dst, RotatedRect box, cv::Scalar color, int thickness)
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
	if (m_Rotate_Thickness == CV_FILLED)
	{
		fillPoly(dst, ppt, m_Rotate_Color);
	}
	else
	{
		polylines(dst, ppt, true, m_Rotate_Color, m_Rotate_Thickness);
	}
	return;
}
