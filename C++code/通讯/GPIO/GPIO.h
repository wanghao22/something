#pragma once
#include <iostream>
#include <thread>
#include <Windows.h>
#include "../include/MvVisionControl.h"
#pragma comment(lib, "../lib/MvVisionControl.lib")

enum Com
{
	Com1,
	Com2,
	Com3,
	Com4,
	Com5,
	Com6,
	Com7,
	Com8
};

class __declspec(dllexport) GPIO
{
public:
	/*0	���ô���
	1��ӦCom1
	2��ӦCom2
	�Դ�����
	*/
	GPIO(int i);

	/*0	���ô���
	"Com1"��ӦCom1
	"Com2"��ӦCom2
	�Դ�����
	*/
	GPIO(char* com_num);

	GPIO();

	~GPIO();

	/*0	���ô���
	1��ӦCom1
	2��ӦCom2
	�Դ�����
	*/
	void __stdcall SetCom(int i);

	/*0	���ô���
	"Com1"��ӦCom1
	"Com2"��ӦCom2
	�Դ�����
	*/
	void __stdcall SetCom(char* com_num);

	/*1	�򿪴���
	@param1: ���ڹ���ģʽ���ⴥ��/�ڴ�������Ĭ��MV_VC_PATTERN_ALL
	@return: MV_OK/������*/
	int __stdcall OpenCom(UCHAR mod = MV_VC_PATTERN_ALL);

	/*1	���õ��������
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ����ʱ�䣨ms��
	@param3: �͵�ƽ/�ߵ�ƽ��MV_VC_LEVEL_LOW��
	@return: MV_OK/������*/
	int __stdcall SingleSetParam(UCHAR port, UINT duringTime, USHORT ValidLevel = MV_VC_LEVEL_LOW);

	/*1	���ö��������
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ����ms��
	@param3: ���ڣ�ms��
	@param4: ����ʱ�䣨ms��
	@return: MV_OK/������*/
	int __stdcall PWMSetParam(UCHAR Port, USHORT PulseWidth, USHORT CycleTime, UINT duringTime);

	/*1	�������Ȳ���
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ���Ȱٷֱȣ�%��
	@return: MV_OK/������*/
	int __stdcall LightSetParam(UCHAR Port, USHORT LightValue);

	/*2	�����幤��
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ��ʼ/������MV_VC_ENABLE_START/MV_VC_ENABLE_END��,Ĭ��MV_VC_ENABLE_START��
	@return: MV_OK/������*/
	int __stdcall SingleSetEnable(UCHAR port, UCHAR able = MV_VC_ENABLE_START);

	/*2	�����幤��
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ��ʼ/������MV_VC_ENABLE_START/MV_VC_ENABLE_END��,Ĭ��MV_VC_ENABLE_START��
	@return: MV_OK/������*/
	int __stdcall PWMSetEnable(UCHAR port, UCHAR able = MV_VC_ENABLE_START);

	/*2	���ȹ���
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ��ʼ/������MV_VC_ENABLE_START/MV_VC_ENABLE_END��,Ĭ��MV_VC_ENABLE_START��
	@return: MV_OK/������*/
	int __stdcall LightSetEnable(UCHAR port, UCHAR able = MV_VC_ENABLE_START);

	/*#	���÷�����
	@param1: ���ڣ�MV_VC_PORT_1 | MV_VC_PORT_2��
	@param2: ����ֵ��
	@return: MV_OK/������*/
	int __stdcall SetDebounceValue(UCHAR Port, USHORT DebounceValue);

	/*#	����ʮ�����Ƶ�����
	@param1: ʮ�����Ƶ����
	@param2: ����ĳ��ȡ�
	@return: MV_OK/������*/
	int __stdcall SendMsg(char msg[512], UINT Len);

	/*#	�������
	@param1: ��䡣
	@return: MV_OK/������*/
	int __stdcall SendMsg(char* str);

	/*	��ȡһ������
	@param1: �յ�����Ϣ��
	@param2: ��ʱʱ�䡣	
	@return: NULL*/
	void __stdcall ReadOnce(std::string &Msg, UINT timeout);

	/*	������ȡ�����߳�
	@param1: �˿�ֵ����������ǳ���{0x01, 0x02, 0x04, 0x08}����ġ�
	@return: NULL*/
	void __stdcall GetMsgTrdStart(UCHAR &Port);

	/*	������ȡ�����߳�
	@param1: �յ�����Ϣ��
	@return: NULL*/
	void __stdcall GetMsgTrdStart(std::string &str);

	/*	�����Ƿ�һֱ��ȡ��Ϣ
	@param1: true/false��
	@return: NULL*/
	void __stdcall SetReadFlag(bool flag);

	/*3	�ر����д���
	@param:  NULL;
	@return: NULL;
	*/
	void __stdcall Close();

	/*1	���ý���ģʽ
	@param1:  ����˿�;
	@param1:  ����˿�;
	@return: MV_OK/������;
	*/
	int __stdcall SetReceivePort(UCHAR INPort, UCHAR OUTPort);

private:

	/*	��ȡ���ݹ����߳�
	@param1: �˿�ֵ����������ǳ���{0x01, 0x02, 0x04, 0x08}����ġ�
	@return: NULL*/
	void __stdcall ThreadComRecv(UCHAR &Port);

	/*	��ȡ���ݹ����߳�
	@param1: �յ�����Ϣ��
	@return: NULL*/
	void __stdcall ThreadComRecvData(std::string &str);
	char* com;
	bool bStop;
	bool bRead;
	bool bThread;
};



