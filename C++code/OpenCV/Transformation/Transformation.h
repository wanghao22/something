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

#define _TRANS_XML_FILE_	"Transformation.xml"

enum Trans_op
{
	TRANS_ROTATE,
	TRANS_FLIP,
	TRANS_CUT,
	TRANS_DILATE,//����
	TRANS_ERODE,//��ʴ
	TRANS_ENHANCE,
	TRANS_MEAN_SHIFT,//��ֵƯ��
	TRANS_HIST,//ֱ��ͼ
	TRANS_GUASSIAN,
	TRANS_RESIZE_ROTATE
};

class __declspec(dllexport) Transformation
{
public:
	Transformation();
	~Transformation();
	//������
	bool __stdcall Excute(cv::Mat src, cv::Mat &dst, int option);
	int __stdcall Excute_(cv::Mat src, cv::Mat &dst, int option);
	//дXML
	int __stdcall SaveXML();
	int __stdcall SaveXML(char* filename);
	//��XML
	int __stdcall LoadXML();
	int __stdcall LoadXML(char* filename);
	int m_Rotate_Angle;//��ת�Ƕ�
	int m_Filp_flag;//��ת����(<0:x+y; ==0:x; >0:y)
	CvRect m_Cut_Size;//�ü��ߴ�
	int m_Resize_Rotate_Angle;//������ת�Ƕ�
private:
	//��ת
	int tRotate(cv::Mat src, cv::Mat &dst);
	//��ת
	int tFlip(cv::Mat src, cv::Mat &dst);
	//�ü�
	int tCut(cv::Mat src, cv::Mat &dst);
	//��ʴ
	int tDilate(cv::Mat src, cv::Mat &dst);
	//����
	int tErode(cv::Mat src, cv::Mat &dst);
	//ͼ����ǿ
	void LogEnhance(IplImage *src, IplImage *dst);
	int tEnhance(cv::Mat src, cv::Mat &dst);
	//��ֵƯ�Ʒָ�
	int tMeanShift(cv::Mat src, cv::Mat &dst);
	//ֱ��ͼ
	int tHist(cv::Mat src, cv::Mat &dst);
	//��˹ģ��
	int tGaussianBlur(cv::Mat src, cv::Mat &dst);
	//������ת
	int tResizeRotate(cv::Mat src, cv::Mat &dst);
};

