#include "stdafx.h"
#include "GPIO.h"

/// 默认构造函数
CSerialPort::CSerialPort()
{
	/*sp_baudRate = 9600;
	sp_dataBytes = 8;
	sp_stopBytes = 1;
	sp_chekBytes = 0;
	sp_cstrPort = CString("Com5");*/

	sp_hCom = NULL;
	sp_baudRate = CBR_9600;
	sp_dataBytes = DATABITS_8;
	sp_stopBytes = ONESTOPBIT;
	sp_chekBytes = NOPARITY;
	sp_cstrPort = CString("Com6");
}

//// 有参构造函数
CSerialPort::CSerialPort(HANDLE hCom, int baudRate,
	int dataBytes, int stopBytes, int chckBytes)
{
	sp_hCom = hCom;			///- 串口Handle
	sp_baudRate = baudRate;			///- 波特率
	sp_dataBytes = dataBytes;		///- 数据位
	sp_stopBytes = stopBytes;		///- 停止位
	sp_chekBytes = chckBytes;		///- 校验位
}

CSerialPort::~CSerialPort(void)
{
}

//// 打开串口
bool CSerialPort::openCom(HANDLE *hCom, CString  cstrPort)
{
	*hCom = CreateFile(cstrPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return setCom(hCom, sp_dcb, sp_baudRate, sp_dataBytes, sp_stopBytes, sp_chekBytes);
}

bool CSerialPort::openCom()
{
	sp_hCom = CreateFile(sp_cstrPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return setCom();
}

//// 设置串口通信参数
bool CSerialPort::setCom(HANDLE* hCom, DCB dcb, int baudRate,
	int dataBytes, int stopBytes, int chckBytes)
{
	BOOL comStat = SetupComm(*hCom, 1024, 1024);

	if (!comStat)
	{
		hCom = NULL;
		return false;
	}

	COMMTIMEOUTS Timeouts;
	Timeouts.ReadIntervalTimeout = 50;
	Timeouts.ReadTotalTimeoutConstant = 500;
	Timeouts.ReadTotalTimeoutMultiplier = 50;
	Timeouts.WriteTotalTimeoutConstant = 500;
	Timeouts.WriteTotalTimeoutMultiplier = 50;

	comStat = SetCommTimeouts(*hCom, &Timeouts);
	if (!comStat)	return false;

	comStat = GetCommState(*hCom, &dcb);
	if (!comStat)	return false;

	dcb.BaudRate = baudRate;
	dcb.ByteSize = 8;
	dcb.StopBits = stopBytes;
	dcb.Parity = NOPARITY;		//// 无校验

	comStat = SetCommState(*hCom, &dcb);

	if (!comStat)	return false;

	return true;
}

bool CSerialPort::setCom()
{
	BOOL comStat = SetupComm(sp_hCom, 1024, 1024);

	if (!comStat)
	{
		sp_hCom = NULL;
		return false;
	}

	COMMTIMEOUTS Timeouts;
	Timeouts.ReadIntervalTimeout = 50;
	Timeouts.ReadTotalTimeoutConstant = 500;
	Timeouts.ReadTotalTimeoutMultiplier = 50;
	Timeouts.WriteTotalTimeoutConstant = 500;
	Timeouts.WriteTotalTimeoutMultiplier = 50;

	comStat = SetCommTimeouts(sp_hCom, &Timeouts);
	if (!comStat)	return false;

	comStat = GetCommState(sp_hCom, &sp_dcb);
	if (!comStat)	return false;

	sp_dcb.BaudRate = sp_baudRate;
	sp_dcb.ByteSize = 8;
	sp_dcb.StopBits = sp_stopBytes;
	sp_dcb.Parity = NOPARITY;		//// 无校验

	comStat = SetCommState(sp_hCom, &sp_dcb);

	if (!comStat)	return false;

	return true;
}

//// 关闭串口
bool CSerialPort::closeCom(HANDLE hCom)
{
	BOOL comStat = CloseHandle(hCom);
	return (comStat) ? true : false;
}

bool CSerialPort::closeCom()
{
	BOOL comStat = CloseHandle(sp_hCom);
	return (comStat) ? true : false;
}

//// 向串口设备发消息HANDLE hCom,
void CSerialPort::sendMsg(char* msgs)
{
	unsigned char wirteBuf[8] = { 0 };
	int hi = -1, lo = -1;///- hi 高4位 lo 低4位
	int msgVal_1 = -1, msgVal_2 = -1;
	//// msgs是16进制的16位字符串 writeBuf是16进制的无符号char数组
	for (int id_1 = 0, id_2 = 0; id_1<16, id_2<8; id_1 = id_1 + 2, id_2++)
	{
		msgVal_1 = msgs[id_1];
		msgVal_2 = msgs[id_1 + 1];

		hi = (msgVal_1>64) ? (msgVal_1 - 55) : (msgVal_1 - 48);
		lo = (msgVal_2>64) ? (msgVal_2 - 55) : (msgVal_2 - 48);

		wirteBuf[id_2] = hi * 16 + lo;
	}
	unsigned long length = 0;

	BOOL writeStat = WriteFile(sp_hCom, wirteBuf, 8, &length, NULL);
	if (!writeStat)
	{
		//=====	MessageBox(NULL, TEXT("串口通信失败"), TEXT("提示"), MB_ICONEXCLAMATION|MB_OK);
	}
}

//// 接收串口状态的返回
void CSerialPort::receiveMsg(HANDLE hCom, char* msgs)
{
	unsigned long length = 0;
	unsigned char readBuf[8] = { 0 };
	ReadFile(hCom, readBuf, 8, &length, NULL);

	char hexA[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	int msgVal = -1;
	for (int id_1 = 0, id_2 = 0; id_1<8, id_2<16; id_1++, id_2++)
	{
		msgVal = readBuf[id_1];
		if (msgVal<16)	msgs[id_2] = '0', msgs[++id_2] = hexA[msgVal];
		else			msgs[id_2] = hexA[(msgVal / 16)], msgs[++id_2] = hexA[(msgVal % 16)];
	}

	SetCommMask(hCom, EV_TXEMPTY);
}

void GetPureColorRect(Mat src, Mat &dst, int method)
{
	if (method == PURE_COLOR_FULL)
	{
		dst = src.clone();
		return;
	}
	Mat imgHSV;
	cvtColor(src, imgHSV, COLOR_BGR2HSV);//转为HSV
	int iLowH, iHighH;
	int iLowS, iHighS;
	int iLowV, iHighV;
	if (method == PURE_COLOR_BROWN)
	{
		iLowH = 0;iHighH = 20;
		iLowS = 110;iHighS = 210;
		iLowV = 20;iHighV = 60;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), dst);
		return;
	}
	if (method == PURE_COLOR_NXTGY)
	{
		iLowH = 25; iHighH = 40;
		iLowS = 80;iHighS = 160;
		iLowV = 40;iHighV = 70;
		Mat temp, elem;
		elem = getStructuringElement(MORPH_RECT, cvSize(3, 3));//3
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), temp);
		Mat elem1 = getStructuringElement(MORPH_RECT, cvSize(7, 7));//7
		dilate(temp, temp, elem);
		erode(temp, dst, elem1);
		//morphologyEx(temp, temp, MORPH_CLOSE, elem);//开运算
		//bitwise_not(temp, dst);
		return;
	}
	if (method == PURE_COLOR_RED)
	{
		iLowH = 0;iHighH = 10;
		iLowS = 43;iHighS = 255;
		iLowV = 46;iHighV = 255;
		int iLowH1 = 156;
		int iHighH1 = 180;
		Mat imgThresholded, imgThresholded1, imgThresholded2;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image  
		inRange(imgHSV, Scalar(iLowH1, iLowS, iLowV), Scalar(iHighH1, iHighS, iHighV), imgThresholded1); //Threshold the image
		bitwise_or(imgThresholded, imgThresholded1, imgThresholded2);//图像取或
		src.copyTo(dst, imgThresholded2);
		return;
	}
	if (method < 3)
	{
		iLowH = 0;
		iHighH = 180;
		switch (method)
		{
		case(PURE_COLOR_WHITE) :
			iLowS = 0; iHighS = 30;
			iLowV = 221; iHighV = 255;
			break;
		case(PURE_COLOR_BLACK) :
			iLowS = 0; iHighS = 255;
			iLowV = 0; iHighV = 46;
			break;
		case(PURE_COLOR_GRAY) :
			iLowS = 0; iHighS = 43;
			iLowV = 46; iHighV = 220;
			break;
		default:
			dst = src.clone();
			return;
		}
	}
	else
	{
		iLowS = 43;
		iHighS = 255;
		iLowV = 46;
		iHighV = 255;
		switch (method)
		{
		case(PURE_COLOR_REDORG) :
			iLowH = 0; iHighH = 25; 
			iLowS = 240; iHighS = 255;
			iLowV = 110; iHighV = 190;
			break;
		case(PURE_COLOR_ORANGE) :
			iLowH = 11; iHighH = 25;
			break;
		case(PURE_COLOR_YELLOW) :
			iLowH = 26; iHighH = 40;//(36)已更改
			break;
		case(PURE_COLOR_GREEN) :
			iLowH = 35; iHighH = 77;
			break;
		case(PURE_COLOR_GREYAN) :
			iLowH = 65; iHighH = 99;
			break;
		case(PURE_COLOR_CYAN) :
			iLowH = 78; iHighH = 99;
			break;
		case(PURE_COLOR_BLUE) :
			iLowH = 100; iHighH = 124;
			break;
		case(PURE_COLOR_VIOLET) :
			iLowH = 125; iHighH = 155;
			break;
		case(PURE_COLOR_COLOR) :
			iLowH = 0; iHighH = 180;
			break;
		default:
			dst = src.clone();
			return;
		}
	}
	Mat mask;
	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), mask);
	src.copyTo(dst, mask);
	return;
}