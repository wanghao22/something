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
	/*0	设置串口
	1对应Com1
	2对应Com2
	以此类推
	*/
	GPIO(int i);

	/*0	设置串口
	"Com1"对应Com1
	"Com2"对应Com2
	以此类推
	*/
	GPIO(char* com_num);

	GPIO();

	~GPIO();

	/*0	设置串口
	1对应Com1
	2对应Com2
	以此类推
	*/
	void __stdcall SetCom(int i);

	/*0	设置串口
	"Com1"对应Com1
	"Com2"对应Com2
	以此类推
	*/
	void __stdcall SetCom(char* com_num);

	/*1	打开串口
	@param1: 串口工作模式（外触发/内触发），默认MV_VC_PATTERN_ALL
	@return: MV_OK/错误码*/
	int __stdcall OpenCom(UCHAR mod = MV_VC_PATTERN_ALL);

	/*1	设置单脉冲参数
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 持续时间（ms）
	@param3: 低电平/高电平（MV_VC_LEVEL_LOW）
	@return: MV_OK/错误码*/
	int __stdcall SingleSetParam(UCHAR port, UINT duringTime, USHORT ValidLevel = MV_VC_LEVEL_LOW);

	/*1	设置多脉冲参数
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 脉宽（ms）
	@param3: 周期（ms）
	@param4: 持续时间（ms）
	@return: MV_OK/错误码*/
	int __stdcall PWMSetParam(UCHAR Port, USHORT PulseWidth, USHORT CycleTime, UINT duringTime);

	/*1	设置亮度参数
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 亮度百分比（%）
	@return: MV_OK/错误码*/
	int __stdcall LightSetParam(UCHAR Port, USHORT LightValue);

	/*2	单脉冲工作
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 开始/结束（MV_VC_ENABLE_START/MV_VC_ENABLE_END）,默认MV_VC_ENABLE_START。
	@return: MV_OK/错误码*/
	int __stdcall SingleSetEnable(UCHAR port, UCHAR able = MV_VC_ENABLE_START);

	/*2	多脉冲工作
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 开始/结束（MV_VC_ENABLE_START/MV_VC_ENABLE_END）,默认MV_VC_ENABLE_START。
	@return: MV_OK/错误码*/
	int __stdcall PWMSetEnable(UCHAR port, UCHAR able = MV_VC_ENABLE_START);

	/*2	亮度工作
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 开始/结束（MV_VC_ENABLE_START/MV_VC_ENABLE_END）,默认MV_VC_ENABLE_START。
	@return: MV_OK/错误码*/
	int __stdcall LightSetEnable(UCHAR port, UCHAR able = MV_VC_ENABLE_START);

	/*#	设置防抖动
	@param1: 串口（MV_VC_PORT_1 | MV_VC_PORT_2）
	@param2: 抖动值。
	@return: MV_OK/错误码*/
	int __stdcall SetDebounceValue(UCHAR Port, USHORT DebounceValue);

	/*#	发送十六进制的命令
	@param1: 十六进制的命令。
	@param2: 命令的长度。
	@return: MV_OK/错误码*/
	int __stdcall SendMsg(char msg[512], UINT Len);

	/*#	发送语句
	@param1: 语句。
	@return: MV_OK/错误码*/
	int __stdcall SendMsg(char* str);

	/*	读取一次数据
	@param1: 收到的消息。
	@param2: 超时时间。	
	@return: NULL*/
	void __stdcall ReadOnce(std::string &Msg, UINT timeout);

	/*	开启读取数据线程
	@param1: 端口值，输入最好是除了{0x01, 0x02, 0x04, 0x08}以外的。
	@return: NULL*/
	void __stdcall GetMsgTrdStart(UCHAR &Port);

	/*	开启读取数据线程
	@param1: 收到的消息。
	@return: NULL*/
	void __stdcall GetMsgTrdStart(std::string &str);

	/*	设置是否一直读取消息
	@param1: true/false。
	@return: NULL*/
	void __stdcall SetReadFlag(bool flag);

	/*3	关闭所有串口
	@param:  NULL;
	@return: NULL;
	*/
	void __stdcall Close();

	/*1	设置接收模式
	@param1:  输入端口;
	@param1:  输出端口;
	@return: MV_OK/错误码;
	*/
	int __stdcall SetReceivePort(UCHAR INPort, UCHAR OUTPort);

private:

	/*	读取数据工作线程
	@param1: 端口值，输入最好是除了{0x01, 0x02, 0x04, 0x08}以外的。
	@return: NULL*/
	void __stdcall ThreadComRecv(UCHAR &Port);

	/*	读取数据工作线程
	@param1: 收到的消息。
	@return: NULL*/
	void __stdcall ThreadComRecvData(std::string &str);
	char* com;
	bool bStop;
	bool bRead;
	bool bThread;
};



