#pragma once
#ifndef PUTTEXT_H_
#define PUTTEXT_H_

#include <windows.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace putText {
/*
�������ܣ���ȡ�ַ�����Ҫ��rect
����������
@IN  hDC: ����
@IN  str: ��������
@OUT w: ��ȡ���Ŀ��
@OUT h: ��ȡ���ĸ߶�
*/
void GetStringSize(HDC hDC, const char* str, int* w, int* h);

/*
�������ܣ��������
����������
@OUT &dst��		�༭ͼ��
@IN  str��		�������
@IN	 org��		�������Ͻǵ�
@IN	 color��	��ɫ
@IN	 fontSize��	�����С
@IN	 fn��		����
@IN  italic��	�Ƿ�б�壿
@IN  underline���Ƿ��»��ߣ�
*/
void putTextZH(Mat & dst, const char * str, Point org, \
	Scalar color, int fontSize, const char * fn, bool \
	italic = false, bool underline = false);

}

#endif // PUTTEXT_H_