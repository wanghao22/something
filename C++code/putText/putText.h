#pragma once
#ifndef PUTTEXT_H_
#define PUTTEXT_H_

#include <windows.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace putText {
/*
函数功能：获取字符串需要的rect
函数参数：
@IN  hDC: 画笔
@IN  str: 输入的语句
@OUT w: 获取语句的宽度
@OUT h: 获取语句的高度
*/
void GetStringSize(HDC hDC, const char* str, int* w, int* h);

/*
函数功能：输出汉字
函数参数：
@OUT &dst：		编辑图像
@IN  str：		输入语句
@IN	 org：		语句的左上角点
@IN	 color：	颜色
@IN	 fontSize：	字体大小
@IN	 fn：		字体
@IN  italic：	是否斜体？
@IN  underline：是否下划线？
*/
void putTextZH(Mat & dst, const char * str, Point org, \
	Scalar color, int fontSize, const char * fn, bool \
	italic = false, bool underline = false);

}

#endif // PUTTEXT_H_