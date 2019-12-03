#pragma once
#include <QFileDialog>
#include "opencv2/opencv.hpp"
#include <QtWidgets/qlabel.h>
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
using namespace cv;
//源代码编码必须是: UTF-8(BOM)    
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
	PURE_COLOR_FULL = -1,//不处理
	PURE_COLOR_WHITE,	//白色
	PURE_COLOR_BLACK,	//黑色
	PURE_COLOR_GRAY,	//灰色
	PURE_COLOR_RED,		//红色
	PURE_COLOR_ORANGE,	//橘色
	PURE_COLOR_YELLOW,	//黄色
	PURE_COLOR_GREEN,	//绿色
	PURE_COLOR_CYAN,	//青色
	PURE_COLOR_BLUE,	//蓝色
	PURE_COLOR_VIOLET,	//紫色
	PURE_COLOR_COLOR	//彩色
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
	绘制旋转矩形
	@Param 1(RotatedRect/CvBox2D): 旋转矩形
	@Param 2: 要绘制的图像。
	@return : OK/Error Code.
*/
	int DrawCvBox2D(CvBox2D box, cv::Mat& src);

/*
	获取旋转矩形的ROI
	@Param 1(RotatedRect/CvBox2D): 旋转矩形
	@Param 2: 返回的CvRect区域。
	@return : OK/Error Code.
*/
	int GetCvBox2DROI(CvBox2D box, CvRect& rect);

/*
	获取字体大小
	@Param 1: 画刷。
	@Param 2: 输入字符串。
	@Param 3: 字符串的长度。
	@Param 4: 字符串的高度。
	@return : 无。
*/
	void GetStringSize(HDC hDC, const char* str, int* w, int* h);

/*	再图像上加入中文
	@Param 1: 输入和输出图像。
	@Param 2: 输入字符串。
	@Param 3: 附加字符串的位置（左上角）。
	@Param 4: 附加字符串的颜色。
	@Param 5: 字体大小(18,20,22...)。
	@Param 6: 字体样式("黑体","宋体","谐体"...)。
	@Param 7: 是否斜体。
	@Param 8: 是否下划线。
	@return : 无。*/
	void putTextCH(cv::Mat &dst, const char* str, Point org, Scalar \
		color, int fontSize, const char* fn, bool italic, bool underline);

/*	按颜色抠图
	@Param 1: 输入图像。
	@Param 2: 输出图像。
	@Param 3: 选择要抠出的颜色。
	@return : 无。*/
	int GetPureColorRect(cv::Mat src, cv::Mat & dst, int method);

/*	自定义HSV色域抠图
	@Param 1: 输入图像。
	@Param 2: 输出图像。
	@Param 3: HSV值的最小值。
	@Param 4: HSV值的最大值。
	@return : 无。*/
	int GetDIYHSVRect(cv::Mat src, cv::Mat &dst, cv::Scalar HSV_min, cv::Scalar HSV_max);

/*	自定义HSV色域抠图
	@Param 1: 输入图像。
	@Param 2: 输出图像。
	@Param 3: R值的最小值。
	@Param 4: R值的最大值。
	@Param 5: G值的最小值。
	@Param 6: G值的最大值。
	@Param 7: B值的最小值。
	@Param 8: B值的最大值。
	@return : 无。*/
	int GetDIYRGBRect(cv::Mat src, cv::Mat &dst, cv::Scalar RGB_min, cv::Scalar RGB_max);

/*	灰度匹配
	@Param 1: 输入图像。
	@Param 2: 模板图像。
	@Param 3: 输出获取的ROI区域。
	@Param 4: 匹配方式。
	@Param 5: norm方式。
	@return : 无。*/
	int MatchingMethod(cv::Mat img, cv::Mat templ, CvRect &rect, int match_method, \
		int norm_type = 4);

/*	将Mat图像显示再QT的label控件上
	@Param 1: 显示图像的Label。
	@Param 2: 要显示的Mat。
	@Param 3: 是否填充。
	@return : 无。*/
	void LabelDisplayMat(QLabel *label, cv::Mat mat, bool full_flag = false);

/*	自适应控件大小
	@Param 1: 源图像。
	@Param 2: 显示图像的Label。
	@Param 3: 调整大小后的图像。
	@Param 4: 是否填充。
	@return : 无。*/
	int ImageResize(cv::Mat src, QLabel *label, cv::Mat &dst, bool full_flag = false);

/*
	std::string转char*
	@Param 1: string类型的字符串。
	@return : char*类型的字符串。*/
	char* string2p_char(std::string str);

/*
	std::QString转char*
	@Param 1: QString类型的字符串。
	@return : char*类型的字符串。*/
	char* qstring2p_char(QString str);

/*
	std::QString转string
	@Param 1: QString类型的字符串。
	@return : string类型的字符串。*/
	std::string qstring2string(QString str);

/*
	std::string转QString
	@Param 1: string类型的字符串。
	@return : QString类型的字符串。*/
	QString string2qstring(std::string str);

/*
	std::QStringList转vector<char*>
	@Param 1: QStringList类型的字符串列表。
	@return : vector<char*>类型的字符串容器。*/
	std::vector<char*> QStrList2vtr_p_char(QStringList list);

	QStringList SelectImageFiles();

	QString SelectImageFile();
}
#endif // !OPENCV_EXTRA_W