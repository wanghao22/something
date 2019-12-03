#include "stdafx.h"
#include "GPIO.h"

GPIO::GPIO()
{
	SetCom(Com2);
	bStop = false;
	bThread = false;
}

GPIO::GPIO(int i)
{
	SetCom(i);
	bStop = false;
	bThread = false;
}

GPIO::GPIO(char* com_num)
{
	com = com_num;
	bStop = false;
	bThread = false;
}

GPIO::~GPIO()
{
	bStop = true;
	bThread = true;
	Close();
}

void __stdcall GPIO::SetCom(int i)
{
	switch (i)
	{
	case(Com1) :
		com = "Com1";
		break;
	case(Com2) :
		com = "Com2";
		break;
	case(Com3) :
		com = "Com3";
		break;
	case(Com4) :
		com = "Com4";
		break;
	case(Com5) :
		com = "Com5";
		break;
	case(Com6) :
		com = "Com6";
		break;
	case(Com7) :
		com = "Com7";
		break;
	case(Com8) :
		com = "Com8";
		break;
	default:
		break;
	}
}

void __stdcall GPIO::SetCom(char* com_num)
{
	com = com_num;
}

/*	Step1:初始化+设置参数
Step2:工作
Step3:关闭*/

int __stdcall GPIO::OpenCom(UCHAR mod)
{
	MV_VC_SERIAL serial = { 0 };
	sprintf_s(serial.strComName, MV_VC_MAX_COM_NAME_LENGTH, com);
	serial.enBaudRate = MV_VC_BAUD_RATE_115200;
	serial.enDataBits = MV_VC_DATA_BITS_8;
	serial.enParityScheme = MV_VC_PARITY_SCHEME_NONE;
	serial.enStopBits = MV_VC_STOP_BITS_1;
	int rc = MV_VC_Open(&serial);
	if (rc != MV_OK)
	{
		return rc;
	}

	MV_VC_PATTERN_SELECT stPatternSelect = { 0 };
	stPatternSelect.nPatternSelect = mod;
	rc = MV_VC_PATTERN_Select(&stPatternSelect);
	if (rc != MV_OK)
	{
		return rc;
	}
	//Sleep(3000);
	return MV_OK;
}

int __stdcall GPIO::SingleSetParam(UCHAR Port, UINT DuringTime, USHORT ValidLevel)
{
	MV_VC_SINGLE_PARAM param = { 0 };
	param.nDurationTime = DuringTime;
	param.nPortNumber = Port;
	param.nValidLevel = ValidLevel;
	int rc = MV_VC_SINGLE_SetParam(&param);
	if (rc != MV_OK)
	{
		return rc;
	}
	return MV_OK;
}

int __stdcall GPIO::PWMSetParam(UCHAR Port, USHORT PulseWidth, USHORT CycleTime, UINT duringTime)
{
	MV_VC_PWM_PARAM stPwmParam = { 0 };
	stPwmParam.nPortNumber = Port;
	stPwmParam.nPulseWidth = PulseWidth;
	stPwmParam.nCycleTime = CycleTime;
	stPwmParam.nDurationTime = duringTime;
	int nRet = MV_VC_PWM_SetParam(&stPwmParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	return MV_OK;
}

int __stdcall GPIO::LightSetParam(UCHAR Port, USHORT LightValue)
{
	MV_VC_LIGHT_PARAM stLightParam = { 0 };
	stLightParam.nPortNumber = Port;
	stLightParam.nLightValue = LightValue;
	int nRet = MV_VC_LIGHT_SetParam(&stLightParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	return MV_OK;
}

int __stdcall GPIO::SingleSetEnable(UCHAR Port, UCHAR able)
{
	MV_VC_SINGLE_ENABLE enable = { 0 };
	enable.nPortNumber = Port;
	enable.nType = able;
	int rc = MV_VC_SINGLE_Enable(&enable);
	if (rc != MV_OK)
	{
		return rc;
	}
	return MV_OK;
}

int __stdcall GPIO::PWMSetEnable(UCHAR port, UCHAR able)
{
	MV_VC_PWM_ENABLE stPwmEnable = { 0 };
	stPwmEnable.nPortNumber = port;
	stPwmEnable.nType = able;
	int nRet = MV_VC_PWM_Enable(&stPwmEnable);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	return MV_OK;
}

int __stdcall GPIO::LightSetEnable(UCHAR port, UCHAR able)
{
	MV_VC_LIGHT_ENABLE stLightEnable = { 0 };
	stLightEnable.nPortNumber = port;
	stLightEnable.nType = able;
	int nRet = MV_VC_LIGHT_Enable(&stLightEnable);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	return MV_OK;
}

int __stdcall GPIO::SetDebounceValue(UCHAR Port, USHORT DebounceValue)
{
	MV_VC_DEBOUNCE_PARAM stDebounceParam = { 0 };
	stDebounceParam.nPortNumber = Port;
	stDebounceParam.nDebounceValue = DebounceValue;
	int nRet = MV_VC_SetDebouncingEx(&stDebounceParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	return MV_OK;
}

int __stdcall GPIO::SendMsg(char msg[512], UINT Len)
{
	return MV_VC_Write(msg, Len);
}

int __stdcall GPIO::SendMsg(char* str)
{
	return MV_VC_Write(str, strlen(str));
}

void __stdcall GPIO::ReadOnce(std::string &Msg, UINT timeout)
{
	MV_VC_READ_PARAM stReadParam = { 0 };
	stReadParam.nTimeOut = timeout;
	MV_VC_Read(&stReadParam);
	Msg = stReadParam.pData;
}

void __stdcall GPIO::ThreadComRecv(UCHAR &Port)
{
	int nRet = MV_E_UNKNOW;
	while (!bStop)		  // 判断线程开启或者关闭
	{
		MV_VC_READ_PARAM stReadParam = { 0 };
		stReadParam.nTimeOut = 2000;//设置超时时间ms
		while (bRead)
		{
			stReadParam = { 0 };
			stReadParam.nTimeOut = rand() % 1000 + 1000;
			nRet = MV_VC_Read(&stReadParam);
			int len = stReadParam.nReadLen;
			if (stReadParam.pData[1] == 0x01)
			{
				Port = MV_VC_PORT_1;
				return;
			}
			if (stReadParam.pData[1] == 0x02)
			{
				Port = MV_VC_PORT_2;
				return;
			}
			if (stReadParam.pData[1] == 0x04)
			{
				Port = MV_VC_PORT_3;
				return;
			}
			if (stReadParam.pData[1] == 0x08)
			{
				Port = MV_VC_PORT_4;
				return;
			}
		}
		Sleep(10);
	}
	return;
}

void __stdcall GPIO::ThreadComRecvData(std::string &str)
{
	int nRet = MV_E_UNKNOW;
	while (!bStop)		  // 判断线程开启或者关闭
	{
		MV_VC_READ_PARAM stReadParam = { 0 };
		stReadParam.nTimeOut = 2000;//设置超时时间ms
		while (bRead)
		{
			stReadParam = { 0 };
			stReadParam.nTimeOut = rand() % 1000 + 1000;
			nRet = MV_VC_Read(&stReadParam);
			if (stReadParam.nReadLen != 0)
			{
				str = stReadParam.pData;
			}
		}
		Sleep(10);
	}
	return;
}

void __stdcall GPIO::GetMsgTrdStart(UCHAR &Port)
{
	if (!bThread)
	{
		std::thread task(&GPIO::ThreadComRecv, this, std::ref(Port));
		task.detach();
		bThread = true;
	}
}

void __stdcall GPIO::GetMsgTrdStart(std::string &str)
{
	if (!bThread)
	{
		std::thread task(&GPIO::ThreadComRecvData, this, std::ref(str));
		task.detach();
		bThread = true;
	}
}

void __stdcall GPIO::SetReadFlag(bool flag)
{
	bRead = flag;
}

void __stdcall GPIO::Close()
{
	SetReadFlag(false);
	Sleep(2000);
	MV_VC_Close();
}

int __stdcall GPIO::SetReceivePort(UCHAR INPort, UCHAR OUTPort)
{
	char pSendData[512] = { 0 };
	pSendData[0] = 0xA5;
	pSendData[1] = 0x00;
	pSendData[2] = INPort;
	pSendData[3] = 0x02;
	pSendData[4] = 0x00;
	pSendData[5] = 0x01;
	pSendData[6] = 0x01;
	pSendData[7] = OUTPort;
	pSendData[8] = 0x00;
	pSendData[9] = 0x00;
	pSendData[10] = 0x00;
	pSendData[11] = 0x00;
	int nRet = MV_VC_Write(pSendData, 12);
	if (MV_OK != nRet)
		return nRet;
	return 0;
}

