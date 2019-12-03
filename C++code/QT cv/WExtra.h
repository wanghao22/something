#pragma once
#include <QFileDialog>
#include "opencv2/opencv.hpp"
#include <QtWidgets/qlabel.h>
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
using namespace cv;
//Դ������������: UTF-8(BOM)    
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef OPENCV_EXTRA_W
#define OPENCV_EXTRA_W

#ifndef _NO_IMAGE_
#define _NO_IMAGE_		-1
#endif
#ifndef _PARAM_ERROR_
#define _PARAM_ERROR_	-2
#endif

enum PURE_COLOR_HSV
{
	PURE_COLOR_FULL = -1,//������
	PURE_COLOR_WHITE,	//��ɫ
	PURE_COLOR_BLACK,	//��ɫ
	PURE_COLOR_GRAY,	//��ɫ
	PURE_COLOR_RED,		//��ɫ
	PURE_COLOR_ORANGE,	//��ɫ
	PURE_COLOR_YELLOW,	//��ɫ
	PURE_COLOR_GREEN,	//��ɫ
	PURE_COLOR_CYAN,	//��ɫ
	PURE_COLOR_BLUE,	//��ɫ
	PURE_COLOR_VIOLET,	//��ɫ
	PURE_COLOR_COLOR	//��ɫ
};

#define COLOR_S_MIN		43
#define COLOR_S_MAX		255
#define COLOR_V_MIN		46
#define COLOR_V_MAX		255
#define RED_H1_MIN		0
#define RED_H1_MAX		10
#define RED_H2_MIN		156
#define RED_H2_MAX		180
#define ORANGE_H_MIN	11
#define ORANGE_H_MAX	25
#define YELLOW_H_MIN	26
#define YELLOW_H_MAX	34
#define GREEN_H_MIN		35
#define GREEN_H_MAX		77
#define CYAN_H_MIN		78
#define CYAN_H_MAX		99
#define BLUE_H_MIN		100
#define BLUE_H_MAX		124
#define VIOLET_H_MIN	125
#define VIOLET_H_MAX	155
#define COLOR_H_MIN		0
#define COLOR_H_MAX		180

#define GRAY_H_MIN		0
#define GRAY_H_MAX		180
#define WITHE_S_MIN		0
#define WITHE_S_MAX		30
#define WITHE_V_MIN		221
#define WITHE_V_MAX		255
#define BLACK_S_MIN		0
#define BLACK_S_MAX		255
#define BLACK_V_MIN		0
#define BLACK_V_MAX		46
#define GRAY_S_MIN		0
#define GRAY_S_MAX		43
#define GRAY_V_MIN		46
#define GRAY_V_MAX		220

namespace WExtra{
/*
	������ת����
	@Param 1(RotatedRect/CvBox2D): ��ת����
	@Param 2: Ҫ���Ƶ�ͼ��
	@return : OK/Error Code.
*/
	int DrawCvBox2D(CvBox2D box, cv::Mat& src);

/*
	��ȡ��ת���ε�ROI
	@Param 1(RotatedRect/CvBox2D): ��ת����
	@Param 2: ���ص�CvRect����
	@return : OK/Error Code.
*/
	int GetCvBox2DROI(CvBox2D box, CvRect& rect);

/*
	��ȡ�����С
	@Param 1: ��ˢ��
	@Param 2: �����ַ�����
	@Param 3: �ַ����ĳ��ȡ�
	@Param 4: �ַ����ĸ߶ȡ�
	@return : �ޡ�
*/
	void GetStringSize(HDC hDC, const char* str, int* w, int* h);

/*	��ͼ���ϼ�������
	@Param 1: ��������ͼ��
	@Param 2: �����ַ�����
	@Param 3: �����ַ�����λ�ã����Ͻǣ���
	@Param 4: �����ַ�������ɫ��
	@Param 5: �����С(18,20,22...)��
	@Param 6: ������ʽ("����","����","г��"...)��
	@Param 7: �Ƿ�б�塣
	@Param 8: �Ƿ��»��ߡ�
	@return : �ޡ�*/
	void putTextCH(cv::Mat &dst, const char* str, Point org, Scalar \
		color, int fontSize, const char* fn, bool italic, bool underline);

/*	����ɫ��ͼ
	@Param 1: ����ͼ��
	@Param 2: ���ͼ��
	@Param 3: ѡ��Ҫ�ٳ�����ɫ��
	@return : �ޡ�*/
	int GetPureColorRect(cv::Mat src, cv::Mat & dst, int method);

/*	�Զ���HSVɫ���ͼ
	@Param 1: ����ͼ��
	@Param 2: ���ͼ��
	@Param 3: HSVֵ����Сֵ��
	@Param 4: HSVֵ�����ֵ��
	@return : �ޡ�*/
	int GetDIYHSVRect(cv::Mat src, cv::Mat &dst, cv::Scalar HSV_min, cv::Scalar HSV_max);

/*	�Զ���HSVɫ���ͼ
	@Param 1: ����ͼ��
	@Param 2: ���ͼ��
	@Param 3: Rֵ����Сֵ��
	@Param 4: Rֵ�����ֵ��
	@Param 5: Gֵ����Сֵ��
	@Param 6: Gֵ�����ֵ��
	@Param 7: Bֵ����Сֵ��
	@Param 8: Bֵ�����ֵ��
	@return : �ޡ�*/
	int GetDIYRGBRect(cv::Mat src, cv::Mat &dst, cv::Scalar RGB_min, cv::Scalar RGB_max);

/*	�Ҷ�ƥ��
	@Param 1: ����ͼ��
	@Param 2: ģ��ͼ��
	@Param 3: �����ȡ��ROI����
	@Param 4: ƥ�䷽ʽ��
	@Param 5: norm��ʽ��
	@return : �ޡ�*/
	int MatchingMethod(cv::Mat img, cv::Mat templ, CvRect &rect, int match_method, \
		int norm_type = 4);

/*	��Matͼ����ʾ��QT��label�ؼ���
	@Param 1: ��ʾͼ���Label��
	@Param 2: Ҫ��ʾ��Mat��
	@Param 3: �Ƿ���䡣
	@return : �ޡ�*/
	void LabelDisplayMat(QLabel *label, cv::Mat mat, bool full_flag = false);

/*	����Ӧ�ؼ���С
	@Param 1: Դͼ��
	@Param 2: ��ʾͼ���Label��
	@Param 3: ������С���ͼ��
	@Param 4: �Ƿ���䡣
	@return : �ޡ�*/
	int ImageResize(cv::Mat src, QLabel *label, cv::Mat &dst, bool full_flag = false);

/*
	std::stringתchar*
	@Param 1: string���͵��ַ�����
	@return : char*���͵��ַ�����*/
	char* string2p_char(std::string str);

/*
	std::QStringתchar*
	@Param 1: QString���͵��ַ�����
	@return : char*���͵��ַ�����*/
	char* qstring2p_char(QString str);

/*
	std::QStringתstring
	@Param 1: QString���͵��ַ�����
	@return : string���͵��ַ�����*/
	std::string qstring2string(QString str);

/*
	std::stringתQString
	@Param 1: string���͵��ַ�����
	@return : QString���͵��ַ�����*/
	QString string2qstring(std::string str);

/*
	std::QStringListתvector<char*>
	@Param 1: QStringList���͵��ַ����б�
	@return : vector<char*>���͵��ַ���������*/
	std::vector<char*> QStrList2vtr_p_char(QStringList list);

	QStringList SelectImageFiles();

	QString SelectImageFile();
}
#endif // !OPENCV_EXTRA_W