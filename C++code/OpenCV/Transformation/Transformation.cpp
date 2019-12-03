#include "stdafx.h"
#include "Transformation.h"
using namespace std;
using namespace cv;

Transformation::Transformation()
{

}


Transformation::~Transformation()
{
}

bool __stdcall Transformation::Excute(cv::Mat src, cv::Mat & dst, int option)
{
	switch (option)
	{
	case(TRANS_ROTATE):
		if (tRotate(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_FLIP):
		if (tFlip(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_CUT):
		if (tCut(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_DILATE):
		if (tDilate(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_ERODE):
		if (tErode(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_ENHANCE):
		if (tEnhance(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_MEAN_SHIFT):
		if (tMeanShift(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_HIST):
		if (tHist(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_GUASSIAN):
		if (tGaussianBlur(src, dst) != 0)
			return false;
		return true;
		break;
	case(TRANS_RESIZE_ROTATE):
		if (tResizeRotate(src, dst) != 0)
			return false;
		return true;
		break;
	default:
		break;
	}
	return false;
}

int __stdcall Transformation::Excute_(cv::Mat src, cv::Mat & dst, int option)
{
	switch (option)
	{
	case(TRANS_ROTATE):
		return tRotate(src, dst);
		break;
	case(TRANS_FLIP):
		return tFlip(src, dst);
		break;
	case(TRANS_CUT):
		return tCut(src, dst);
		break;
	case(TRANS_DILATE):
		return tDilate(src, dst);
		break;
	case(TRANS_ERODE):
		return tErode(src, dst);
		break;
	case(TRANS_ENHANCE):
		return tEnhance(src, dst);
		break;
	case(TRANS_MEAN_SHIFT):
		return tMeanShift(src, dst);
		break;
	case(TRANS_HIST):
		return tHist(src, dst);
		break;
	case(TRANS_GUASSIAN):
		return tGaussianBlur(src, dst);
		break;
	case(TRANS_RESIZE_ROTATE):
		return tResizeRotate(src, dst);
		break;
	default:
		break;
	}
	return _PARAM_ERROR_;
}

int __stdcall Transformation::SaveXML()
{
	FileStorage fs(_TRANS_XML_FILE_, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	fs << "m_Rotate_Angle" << m_Rotate_Angle;
	fs << "m_Filp_flag" << m_Filp_flag;
	fs << "m_Cut_Size_X" << m_Cut_Size.x;
	fs << "m_Cut_Size_Y" << m_Cut_Size.y;
	fs << "m_Cut_Size_W" << m_Cut_Size.width;
	fs << "m_Cut_Size_H" << m_Cut_Size.height;
	fs << "m_Resize_Rotate_Angle" << m_Resize_Rotate_Angle;
	fs.release();
	return 0;
}

int __stdcall Transformation::SaveXML(char * filename)
{
	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	fs << "m_Rotate_Angle" << m_Rotate_Angle;
	fs << "m_Filp_flag" << m_Filp_flag;
	fs << "m_Cut_Size_X" << m_Cut_Size.x;
	fs << "m_Cut_Size_Y" << m_Cut_Size.y;
	fs << "m_Cut_Size_W" << m_Cut_Size.width;
	fs << "m_Cut_Size_H" << m_Cut_Size.height;
	fs << "m_Resize_Rotate_Angle" << m_Resize_Rotate_Angle;
	fs.release();
	return 0;
}

int __stdcall Transformation::LoadXML()
{
	FileStorage fs(_TRANS_XML_FILE_, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	fs["m_Rotate_Angle"] >> m_Rotate_Angle;
	fs["m_Filp_flag"] >> m_Filp_flag;
	fs["m_Cut_Size_X"] >> m_Cut_Size.x;
	fs["m_Cut_Size_Y"] >> m_Cut_Size.y;
	fs["m_Cut_Size_W"] >> m_Cut_Size.width;
	fs["m_Cut_Size_H"] >> m_Cut_Size.height;
	fs["m_Resize_Rotate_Angle"] >> m_Resize_Rotate_Angle;
	fs.release();
	return 0;
}

int __stdcall Transformation::LoadXML(char * filename)
{
	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		return _OPEN_XML_ERROR_;
	}
	fs["m_Rotate_Angle"] >> m_Rotate_Angle;
	fs["m_Filp_flag"] >> m_Filp_flag;
	fs["m_Cut_Size_X"] >> m_Cut_Size.x;
	fs["m_Cut_Size_Y"] >> m_Cut_Size.y;
	fs["m_Cut_Size_W"] >> m_Cut_Size.width;
	fs["m_Cut_Size_H"] >> m_Cut_Size.height;
	fs["m_Resize_Rotate_Angle"] >> m_Resize_Rotate_Angle;
	fs.release();
	return 0;
}

//private:

int Transformation::tRotate(cv::Mat src, cv::Mat & dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	while (m_Rotate_Angle<0)
		m_Rotate_Angle += 360;
	while (m_Rotate_Angle>359)
		m_Rotate_Angle -= 360;
	cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
	cv::Mat rot = cv::getRotationMatrix2D(center, m_Rotate_Angle, 1.0);
	warpAffine(src, dst, rot, src.size());
	return 0;
}

int Transformation::tFlip(cv::Mat src, cv::Mat & dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	flip(src, dst, m_Filp_flag);
	return 0;
}

int Transformation::tCut(cv::Mat src, cv::Mat & dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	if (m_Cut_Size.x<0 || m_Cut_Size.y<0 || m_Cut_Size.width + m_Cut_Size.x>src.cols \
		|| m_Cut_Size.y + m_Cut_Size.height>src.rows)
		return _ROI_OVERTOP_;
	Mat roi = src(m_Cut_Size);
	dst = roi.clone();
	return 0;
}

int Transformation::tDilate(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	Mat element = getStructuringElement(MORPH_RECT, cvSize(3, 3));
	dilate(src, dst, element);
	return 0;
}

int Transformation::tErode(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	Mat element = getStructuringElement(MORPH_RECT, cvSize(3, 3));
	erode(src, dst, element);
	return 0;
}

void Transformation::LogEnhance(IplImage *src, IplImage *dst)
{//对数图像增强法	
	uchar lut[256] = { 0 };
	double temp = 255 / log(256);
	for (int i = 0; i < 255; i++)
	{
		lut[i] = (uchar)(temp*log(i + 1) + 0.5);
	}
	for (int row = 0; row < src->height; row++)
	{
		uchar *data = (uchar*)src->imageData + row*src->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row*dst->widthStep;
		for (int col = 0; col < src->width; col++)
		{
			for (int k = 0; k < src->nChannels; k++)
			{
				uchar t1 = data[col*src->nChannels + k];
				dstData[col*src->nChannels + k] = lut[t1];
			}
		}
	}
}

int Transformation::tEnhance(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	IplImage *in = &(IplImage)src, *out;
	out = cvCloneImage(in);
	LogEnhance(in, out);
	dst = cvarrToMat(out);
	return 0;
}

int Transformation::tMeanShift(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	Mat bgr;
	if (src.channels() == 1)
		cvtColor(src, bgr, CV_GRAY2BGR);
	else if (src.channels() == 3)
		bgr = src.clone();
	else
		return _PARAM_ERROR_;
	IplImage *img = &(IplImage)bgr;
	IplImage *hsv = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, hsv, CV_BGR2HSV);
	IplImage *h_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage *s_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage *v_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage *planes[] = { h_plane,s_plane };
	cvSplit(hsv, h_plane, s_plane, v_plane, 0);
	int h_bins = 30, s_bins = 32;
	CvHistogram *hist = NULL;
	{
		int hist_size[] = { h_bins,s_bins };
		float h_ranges[] = { 0,180 };
		float s_ranges[] = { 0,255 };
		float *ranges[] = { h_ranges,s_ranges };
		hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
	}
	cvCalcHist(planes, hist, 0, 0);
	cvNormalizeHist(hist, 1);
	int scale = 10;
	IplImage *hist_image = cvCreateImage(cvSize(h_bins*scale, s_bins*scale), 8, 3);
	cvZero(hist_image);
	float max_value = 0;
	cvGetMinMaxHistValue(hist, 0, &max_value);
	for (int h = 0; h < h_bins; h++)
	{
		for (int s = 0; s < s_bins; s++)
		{
			//float bin_val = cvQueryHistValue_2D(hist,h,s)//cvQueryHistValue_2D编译器找不到
			double bin_val = cvGetReal2D(hist->bins, h, s);
			int intensity = cvRound(bin_val * 255 / (double)max_value);
			cvRectangle(hist_image, cvPoint(h*scale, s*scale), cvPoint((h + 1)*scale - 1,
				(s + 1)*scale - 1), CV_RGB(intensity, intensity, intensity), CV_FILLED);
		}
	}
	dst = cvarrToMat(hsv);
	cvReleaseImage(&h_plane);
	cvReleaseImage(&s_plane);
	cvReleaseImage(&v_plane);
	cvReleaseImage(&hist_image);
	return 0;
}

int Transformation::tHist(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	Mat bgr;
	if (src.channels() == 1)
		cvtColor(src, bgr, CV_GRAY2BGR);
	else if (src.channels() == 3)
		bgr = src.clone();
	else
		return _PARAM_ERROR_;
	pyrMeanShiftFiltering(bgr, dst, 2, 40, 3);
	return 0;
}

int Transformation::tGaussianBlur(cv::Mat src, cv::Mat &dst)
{
	if (src.empty())
		return _NO_IMAGE_;
	GaussianBlur(src, dst, Size(5, 5), 0, 0);
	return 0;
}

int Transformation::tResizeRotate(cv::Mat src, cv::Mat & dst)
{
	float radian = (float)(m_Resize_Rotate_Angle / 180.0 * CV_PI);

	//填充图像
	int maxBorder = (int)(max(src.cols, src.rows)* 1.414); //即为sqrt(2)*max
	int dx = (maxBorder - src.cols) / 2;
	int dy = (maxBorder - src.rows) / 2;
	copyMakeBorder(src, dst, dy, dy, dx, dx, BORDER_CONSTANT);

	//旋转
	Point2f center((float)(dst.cols / 2), (float)(dst.rows / 2));
	Mat affine_matrix = getRotationMatrix2D(center, m_Resize_Rotate_Angle, 1.0);//求得旋转矩阵
	warpAffine(dst, dst, affine_matrix, dst.size());

	//计算图像旋转之后包含图像的最大的矩形
	float sinVal = abs(sin(radian));
	float cosVal = abs(cos(radian));
	Size targetSize((int)(src.cols * cosVal + src.rows * sinVal),
		(int)(src.cols * sinVal + src.rows * cosVal));

	//剪掉多余边框
	int x = (dst.cols - targetSize.width) / 2;
	int y = (dst.rows - targetSize.height) / 2;
	Rect rect(x, y, targetSize.width, targetSize.height);
	dst = Mat(dst, rect);
	return 0;
}
