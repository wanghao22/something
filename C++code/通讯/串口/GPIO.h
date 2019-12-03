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
	PURE_COLOR_GREYAN,	//����ɫ
	PURE_COLOR_REDORG,	//�Ⱥ�ɫ
	PURE_COLOR_NXTGY	//Ũ��������
};

class CSerialPort
{
public:
	//// Ĭ�Ϲ��캯��
	CSerialPort(void);
	//// �вι��캯��
	CSerialPort(HANDLE hCom, int baudRate, int dataBytes,
		int stopBytes, int chckBytes);
	~CSerialPort(void);

	//// ��Ա����
public:
	HANDLE		sp_hCom;			///- ����Handle
	DCB			sp_dcb;				///- device control block �豸���ƿ�
	int			sp_baudRate;		///- ������
	int			sp_dataBytes;		///- ����λ
	int			sp_stopBytes;		///- ֹͣλ
	int			sp_chekBytes;		///- У��λ
	CString		sp_cstrPort;		///- ���ں�

	//// ��Ա����
public:
	bool openCom(HANDLE* hCom, CString  cstrPort);		///- �򿪴���
	bool openCom();
	bool setCom(HANDLE* hcom, DCB dcb, int baudRate, 	///- ����ͨ�Ų���
		int dataBytes, int stopBytes, int chckBytes);
	bool setCom();
	void sendMsg(char * msg);	///- �򴮿ڷ���ϢHANDLE hCom, 
	void receiveMsg(HANDLE hcom, char * msg);			///- �Ӵ��ڽ�����Ϣ
	bool closeCom(HANDLE hcom);	///- �رմ���
	bool closeCom();	///- �رմ���
};

//ɫ���ͼ
void GetPureColorRect(Mat src, Mat &dst, int method);

#endif