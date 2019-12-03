#include "WExtra.h"

int WExtra::DrawCvBox2D(CvBox2D box, cv::Mat & src)
{
	if (src.empty())
	{
		return _NO_IMAGE_;
	}
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
	line(src, pt[0], pt[1], cvScalar(255), 2, 8, 0);
	line(src, pt[1], pt[2], cvScalar(255), 2, 8, 0);
	line(src, pt[2], pt[3], cvScalar(255), 2, 8, 0);
	line(src, pt[3], pt[0], cvScalar(255), 2, 8, 0);
	return 0;
}

int WExtra::GetCvBox2DROI(CvBox2D box, CvRect& rect)
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
	int minh = 10000, maxh = 0, minw = 10000, maxw = 0;
	for (i = 0; i < 4; i++)
	{
		if (pt[i].x > maxw)
			maxw = pt[i].x;
		else if (pt[i].x < minw)
			minw = pt[i].x;
		//pass
		if (pt[i].y > maxh)
			maxh = pt[i].y;
		else if (pt[i].y < minh)
			minh = pt[i].y;
	}
	rect.x = minw;
	rect.y = minh;
	rect.width = maxw - minw + 1;
	rect.height = maxh - minh + 1;
	return 0;
}

void WExtra::GetStringSize(HDC hDC, const char* str, int* w, int* h)
{
	SIZE size;
	GetTextExtentPoint32A(hDC, str, strlen(str), &size);
	if (w != 0) *w = size.cx;
	if (h != 0) *h = size.cy;
}

void WExtra::putTextCH(cv::Mat &dst, const char* str, Point org, Scalar \
	color, int fontSize, const char* fn, bool italic, bool underline)
{
	CV_Assert(dst.data != 0 && (dst.channels() == 1 || dst.channels() == 3));

	int x, y, r, b;
	if (org.x > dst.cols || org.y > dst.rows) return;
	x = org.x < 0 ? -org.x : 0;
	y = org.y < 0 ? -org.y : 0;

	LOGFONTA lf;
	lf.lfHeight = -fontSize;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 5;
	lf.lfItalic = italic;
	lf.lfUnderline = underline;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = 0;
	strcpy_s(lf.lfFaceName, fn);

	HFONT hf = CreateFontIndirectA(&lf);
	HDC hDC = CreateCompatibleDC(0);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hf);

	int strBaseW = 0, strBaseH = 0;
	int singleRow = 0;
	char buf[1 << 12];
	strcpy_s(buf, str);
	char *bufT[1 << 12];

	{
		int nnh = 0;
		int cw, ch;

		const char* ln = strtok_s(buf, "\n", bufT);
		while (ln != 0)
		{
			GetStringSize(hDC, ln, &cw, &ch);
			strBaseW = max(strBaseW, cw);
			strBaseH = max(strBaseH, ch);

			ln = strtok_s(0, "\n", bufT);
			nnh++;
		}
		singleRow = strBaseH;
		strBaseH *= nnh;
	}

	if (org.x + strBaseW < 0 || org.y + strBaseH < 0)
	{
		SelectObject(hDC, hOldFont);
		DeleteObject(hf);
		DeleteObject(hDC);
		return;
	}

	r = org.x + strBaseW > dst.cols ? dst.cols - org.x - 1 : strBaseW - 1;
	b = org.y + strBaseH > dst.rows ? dst.rows - org.y - 1 : strBaseH - 1;
	org.x = org.x < 0 ? 0 : org.x;
	org.y = org.y < 0 ? 0 : org.y;

	BITMAPINFO bmp = { 0 };
	BITMAPINFOHEADER& bih = bmp.bmiHeader;
	int strDrawLineStep = strBaseW * 3 % 4 == 0 ? strBaseW * 3 : (strBaseW * 3 + 4 - ((strBaseW * 3) % 4));

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = strBaseW;
	bih.biHeight = strBaseH;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = strBaseH * strDrawLineStep;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	void* pDibData = 0;
	HBITMAP hBmp = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, &pDibData, 0, 0);

	CV_Assert(pDibData != 0);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);

	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, 0);

	strcpy_s(buf, str);
	const char* ln = strtok_s(buf, "\n", bufT);
	int outTextY = 0;
	while (ln != 0)
	{
		TextOutA(hDC, 0, outTextY, ln, strlen(ln));
		outTextY += singleRow;
		ln = strtok_s(0, "\n", bufT);
	}
	uchar* dstData = (uchar*)dst.data;
	int dstStep = dst.step / sizeof(dstData[0]);
	unsigned char* pImg = (unsigned char*)dst.data + org.x * dst.channels() + org.y * dstStep;
	unsigned char* pStr = (unsigned char*)pDibData + x * 3;
	for (int tty = y; tty <= b; ++tty)
	{
		unsigned char* subImg = pImg + (tty - y) * dstStep;
		unsigned char* subStr = pStr + (strBaseH - tty - 1) * strDrawLineStep;
		for (int ttx = x; ttx <= r; ++ttx)
		{
			for (int n = 0; n < dst.channels(); ++n) {
				double vtxt = subStr[n] / 255.0;
				int cvv = (int)(vtxt * color.val[n] + (1 - vtxt) * subImg[n]);
				subImg[n] = cvv > 255 ? 255 : (cvv < 0 ? 0 : cvv);
			}

			subStr += 3;
			subImg += dst.channels();
		}
	}

	SelectObject(hDC, hOldBmp);
	SelectObject(hDC, hOldFont);
	DeleteObject(hf);
	DeleteObject(hBmp);
	DeleteDC(hDC);
}

int WExtra::GetPureColorRect(Mat src, Mat & dst, int method)
{
	if (src.channels() != 3 || src.empty())
	{
		return _NO_IMAGE_;
	}
	if (method == PURE_COLOR_FULL)
	{
		dst = src.clone();
		return 0;
	}
	Mat imgHSV;
	cvtColor(src, imgHSV, COLOR_BGR2HSV);//转为HSV
	if (method == PURE_COLOR_RED)
	{
		int iLowH = RED_H1_MIN;
		int iHighH = RED_H1_MAX;
		int iLowH1 = RED_H2_MIN;
		int iHighH1 = RED_H2_MAX;
		int iLowS = COLOR_S_MIN;
		int iHighS = COLOR_S_MAX;
		int iLowV = COLOR_V_MIN;
		int iHighV = COLOR_V_MAX;
		Mat imgThresholded, imgThresholded1, imgThresholded2;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image  
		inRange(imgHSV, Scalar(iLowH1, iLowS, iLowV), Scalar(iHighH1, iHighS, iHighV), imgThresholded1); //Threshold the image
		bitwise_or(imgThresholded, imgThresholded1, imgThresholded2);//图像取或
		src.copyTo(dst, imgThresholded2);
		return 0;
	}
	else
	{
		if (method < 3)
		{
			int iLowH = GRAY_H_MIN;
			int iHighH = GRAY_H_MAX;
			int iLowS, iHighS;
			int iLowV, iHighV;
			switch (method)
			{
			case(PURE_COLOR_WHITE):
				iLowS = WITHE_S_MIN; iHighS = WITHE_S_MAX;
				iLowV = WITHE_V_MIN; iHighV = WITHE_V_MAX;
				break;
			case(PURE_COLOR_BLACK):
				iLowS = BLACK_S_MIN; iHighS = BLACK_S_MAX;
				iLowV = BLACK_V_MIN; iHighV = BLACK_V_MAX;
				break;
			case(PURE_COLOR_GRAY):
				iLowS = GRAY_S_MIN; iHighS = GRAY_S_MAX;
				iLowV = GRAY_V_MIN; iHighV = GRAY_V_MAX;
				break;
			default:
				return _PARAM_ERROR_;
			}
			Mat mask;
			inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), mask);
			src.copyTo(dst, mask);
			return 0;
		}
		else
		{
			int iLowH, iHighH;
			int iLowS = COLOR_S_MIN;
			int iHighS = COLOR_S_MAX;
			int iLowV = COLOR_V_MIN;
			int iHighV = COLOR_V_MAX;
			switch (method)
			{
			case(PURE_COLOR_ORANGE):
				iLowH = ORANGE_H_MIN; iHighH = ORANGE_H_MAX;
				break;
			case(PURE_COLOR_YELLOW):
				iLowH = YELLOW_H_MIN; iHighH = YELLOW_H_MAX;
				break;
			case(PURE_COLOR_GREEN):
				iLowH = GREEN_H_MIN; iHighH = GREEN_H_MAX;
				break;
			case(PURE_COLOR_CYAN):
				iLowH = CYAN_H_MIN; iHighH = CYAN_H_MAX;
				break;
			case(PURE_COLOR_BLUE):
				iLowH = BLUE_H_MIN; iHighH = BLUE_H_MAX;
				break;
			case(PURE_COLOR_VIOLET):
				iLowH = VIOLET_H_MIN; iHighH = VIOLET_H_MAX;
				break;
			case(PURE_COLOR_COLOR):
				iLowH = COLOR_H_MIN; iHighH = COLOR_H_MAX;
				break;
			default:
				return _PARAM_ERROR_;
			}
			Mat mask;
			inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), mask);
			src.copyTo(dst, mask);
			return 0;
		}
	}
}

int WExtra::GetDIYHSVRect(Mat src, Mat &dst, Scalar HSV_min, Scalar HSV_max)
{
	if (src.channels() != 3 || src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat imgHSV;
	cvtColor(src, imgHSV, COLOR_BGR2HSV);//转为HSV
	Mat mask;
	inRange(imgHSV, HSV_min, HSV_max, mask);
	src.copyTo(dst, mask);
	return 0;
}

int WExtra::GetDIYRGBRect(Mat src, Mat &dst, Scalar RGB_min, Scalar RGB_max)
{
	if (src.channels() != 3 || src.empty())
	{
		return _NO_IMAGE_;
	}
	Mat mask;
	inRange(src, RGB_min, RGB_max, mask);
	src.copyTo(dst, mask);
	return 0;
}

int WExtra::MatchingMethod(Mat img, Mat templ, CvRect &rect, int match_method, int nor)
{
	if (img.empty() || templ.empty())
	{
		return _NO_IMAGE_;
	}
	Mat img_play;
	Mat result;
	img.copyTo(img_play);
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	result.create(result_cols, result_rows, CV_32FC1);
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, nor, -1, Mat());
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	rect = cvRect(matchLoc.x, matchLoc.y, templ.cols, templ.rows);
	return 0;
}

void WExtra::LabelDisplayMat(QLabel *label, cv::Mat src, bool full_flag)
{
	cv::Mat Rgb;
	QImage Img;
	Mat temp;
	if (ImageResize(src, label, temp, full_flag) != 0)
	{
		return;
	}
	if (temp.channels() == 3)//RGB Img
	{
		cv::cvtColor(temp, Rgb, CV_BGR2RGB);//颜色空间转换
		Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
	}
	else//Gray Img
	{
		Img = QImage((const uchar*)(temp.data), temp.cols, temp.rows, temp.cols*temp.channels(), QImage::Format_Indexed8);
	}
	label->setPixmap(QPixmap::fromImage(Img));
}

int WExtra::ImageResize(cv::Mat src, QLabel *label, cv::Mat &dst, bool full_flag)
{
	if (src.empty())
	{
		return -1;
	}
	if (src.channels() == 1)
	{
		cvtColor(src, src, CV_GRAY2BGR);
	}
	Mat temp;
	int labelwidth = label->width();
	int labelheight = label->height();
	if (src.cols > labelwidth || src.rows > labelheight || full_flag)
	{
		double width = labelwidth;
		double scale = (double)src.rows / (double)src.cols;
		double height = width*scale;
		if (width > labelwidth || height > labelheight)
		{
			height = labelheight;
			scale = (double)src.cols / (double)src.rows;
			width = height*scale;
			if (width > labelwidth || height > labelheight)
			{
				return -1;
			}
		}
		resize(src, dst, cvSize((int)width, (int)height));
	}
	else
	{
		dst = src.clone();
	}
	return 0;
}

char* WExtra::string2p_char(std::string str)
{
	int sum = str.length();
	char* result = new char[sum];
	for (int i = 0; i < sum; i++)
	{
		result[i] = str[i];
	}
	result[sum] = '\0';
	return result;
}

char* WExtra::qstring2p_char(QString str)
{
	std::string strl = string((const char *)str.toLocal8Bit());
	return string2p_char(strl);
}

string WExtra::qstring2string(QString str)
{
	return string((const char *)str.toLocal8Bit());
}

QString WExtra::string2qstring(string str)
{
	return QString(QString::fromLocal8Bit(str.c_str()));
}

vector<char*> WExtra::QStrList2vtr_p_char(QStringList list)
{
	vector<char*> result;
	for (auto tmp : list)
	{
		result.push_back(qstring2p_char(tmp));
	}
	return result;
}

QStringList WExtra::SelectImageFiles()
{
	//定义文件对话框类
	QFileDialog *fileDialog = new QFileDialog();
	//定义文件对话框标题
	fileDialog->setWindowTitle("打开图片");
	//设置默认文件路径
	fileDialog->setDirectory(".");
	//设置文件过滤器
	fileDialog->setNameFilter("Images(*.png *.jpg *.jpeg *.bmp)");
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
		//fileNames = fileDialog->selectFile();
	}
	return fileNames;
}

QString WExtra::SelectImageFile()
{
	//定义文件对话框类
	QFileDialog *fileDialog = new QFileDialog();
	//定义文件对话框标题
	fileDialog->setWindowTitle("打开图片");
	//设置默认文件路径
	fileDialog->setDirectory(".");
	//设置文件过滤器
	fileDialog->setNameFilter("Images(*.png *.jpg *.jpeg *.bmp)");
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	//fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList fileName;
	if (fileDialog->exec())
	{
		fileName = fileDialog->selectedFiles();
		//fileDialog->selectFile(fileName);
	}
	if (fileName.size() == 0)
	{
		return "";
	}
	return fileName[0];
}