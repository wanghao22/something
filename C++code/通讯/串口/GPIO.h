#pragma once
#include <opencv2\opencv.hpp>
using namespace cv;
#ifndef GOIP_H_DEFINE
#define GOIP_H_DEFINE

enum PRUE_COLOR{
	PURE_COLOR_FULL = -1,
	PURE_COLOR_WHITE,
	PURE_COLOR_BLACK,
	PURE_COLOR_GRAY,
	PURE_COLOR_RED,
	PURE_COLOR_ORANGE,
	PURE_COLOR_YELLOW,
	PURE_COLOR_GREEN,
	PURE_COLOR_CYAN,
	PURE_COLOR_BLUE,
	PURE_COLOR_VIOLET,
	PURE_COLOR_BROWN,
	PURE_COLOR_COLOR,
	PURE_COLOR_GREYAN,	//青绿色
	PURE_COLOR_REDORG,	//橙红色
	PURE_COLOR_NXTGY	//浓香铁观音
};

class CSerialPort
{
public:
	//// 默认构造函数
	CSerialPort(void);
	//// 有参构造函数
	CSerialPort(HANDLE hCom, int baudRate, int dataBytes,
		int stopBytes, int chckBytes);
	~CSerialPort(void);

	//// 成员变量
public:
	HANDLE		sp_hCom;			///- 串口Handle
	DCB			sp_dcb;				///- device control block 设备控制块
	int			sp_baudRate;		///- 波特率
	int			sp_dataBytes;		///- 数据位
	int			sp_stopBytes;		///- 停止位
	int			sp_chekBytes;		///- 校验位
	CString		sp_cstrPort;		///- 串口号

	//// 成员函数
public:
	bool openCom(HANDLE* hCom, CString  cstrPort);		///- 打开串口
	bool openCom();
	bool setCom(HANDLE* hcom, DCB dcb, int baudRate, 	///- 设置通信参数
		int dataBytes, int stopBytes, int chckBytes);
	bool setCom();
	void sendMsg(char * msg);	///- 向串口发消息HANDLE hCom, 
	void receiveMsg(HANDLE hcom, char * msg);			///- 从串口接收消息
	bool closeCom(HANDLE hcom);	///- 关闭串口
	bool closeCom();	///- 关闭串口
};

//色域抠图
void GetPureColorRect(Mat src, Mat &dst, int method);

#endif