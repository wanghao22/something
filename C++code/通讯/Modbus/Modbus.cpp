#include "stdafx.h"
#include "Modbus.h"

//public:
Modbus::Modbus()
{
	bStop = false;
	bRead = false;
}

Modbus::~Modbus()
{
	bStop = true;
	this->Close();
}

int WINAPI Modbus::Open(ULONG xPort, ULONG xBabd, UCHAR xDataSize, UCHAR xParity, UCHAR xStopBit, UCHAR station_num,
	USHORT register_start, USHORT register_num)
{
	stationnum = station_num;
	registerstart = register_start;
	registernum = register_num;
	return (OpenPort(xPort, xBabd, xDataSize, xParity, xStopBit, _INPUT_BUF_SIZE_, _OUTPUT_BUF_SIZE_, _DW_TIME_OUT_));
}

void WINAPI Modbus::Close()
{
	bRead = false;
	if (IsOpen())
	{
		CloseHandle(hCom);
		hCom = INVALID_HANDLE_VALUE;
	}
	/*if (m_overlappedRead.hEvent != NULL)
	{
		CloseHandle(m_overlappedRead.hEvent);
	}
	if (m_overlappedWrite.hEvent != NULL)
	{
		CloseHandle(m_overlappedWrite.hEvent);
	}*/
}

void WINAPI Modbus::ReadThrdStart(short* &list)
{
	bRead = true;
	thread task(&Modbus::ReadThread, this, ref(list));
	task.detach();
}

int WINAPI Modbus::SendMsg(string Msg)
{
	bRead = false;
	//short registerData[registernum + 1] = { 0 };
	short *registerData = new short[registernum + 1];
	string Data;
	std::vector<int> index;
	for (int i = 0; i < Msg.length(); i++){
		if (Msg[i] == '"' || Msg[i] == '"'){
			index.push_back(i);
		}
	}
	if (2 * registernum != index.size())
	{
		//AfxMessageBox(L"输入数据错误！");
		index.clear();
		return -1;
	}
	for (int i = 0; i < index.size() / 2; i++){
		for (int j = 0; j < index[2 * i + 1] - index[2 * i] - 1; j++){
			Data += Msg[index[2 * i] + j + 1];
		}
		registerData[i] = atoi(Data.c_str());
		Data = "";
	}
	while (1){
		if (0 == MODBUS_S_ReadMultiRegD_Slave(stationnum, registerstart, registernum, registerData))
		{
			break;
		}
		Sleep(100);
	}
	delete[] registerData;
	bRead = true;
}

//private:
void WINAPI Modbus::ReadThread(short* &list)
{
	while (!bStop)
	{
		while(bRead)
		{
			if (0 != MODBUS_S_WriteMultiRegD_Slave(stationnum, registerstart, registernum, list))
			{
				continue;
			}
			//::PostMessage(pWnd->m_hWnd, WM_SHOWRECIEVE, (WPARAM)list, 0);
		}
		Sleep(10);
	}
	return;
}

int WINAPI Modbus::MODBUS_S_ReadMultiRegD_Slave(UCHAR rtu, USHORT RegAdd, USHORT RegCount, short *list)
{
	UCHAR buff[256];
	USHORT crc16;
	USHORT crctmp;

	//读取数据
	ULONG strlen;
	if (IsOpen())
	{
		//读数据
		memset(buff, 0x00, 255);
		strlen = ReadChar(8, (char *)buff, 1000);
		if (strlen == 0)
		{
			//无返回
			return -2;
		}
		else
		{
			//返回长度有效,解析接收缓冲区
			if (strlen == 8 && buff[0] == rtu && buff[1] == 0x03)
			{

				crc16 = CalcCrcFast(buff, 6);
				crctmp = buff[strlen - 2];
				crctmp = crctmp << 8 | buff[strlen - 1];
				if (crc16 != crctmp)
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}

		memset(buff, 0x00, 255);
		buff[0] = rtu;
		buff[1] = 0x03;
		buff[2] = (UCHAR)(RegCount * 2);
		buff[3] = (UCHAR)((list[0]) >> 8);
		buff[4] = (UCHAR)(list[0]);
		buff[5] = (UCHAR)(list[1] >> 8);
		buff[6] = (UCHAR)list[1];
		buff[7] = (UCHAR)(list[2] >> 8);
		buff[8] = (UCHAR)list[2];
		buff[9] = (UCHAR)(list[3] >> 8);
		buff[10] = (UCHAR)list[3];
		crc16 = CalcCrcFast(buff, 3 + (RegCount * 2));
		buff[11] = (UCHAR)(crc16 >> 8);
		buff[12] = (UCHAR)crc16;

		Sleep(50);
		//发送数据
		strlen = WriteChar(3 + (RegCount * 2) + 2, (char *)buff);
		if (strlen == (3 + (RegCount * 2) + 2))
		{
			return 0;
		}
		else
		{
			return -2;
		}
	}
	else
		return -2;
}

int WINAPI Modbus::MODBUS_S_WriteMultiRegD_Slave(UCHAR rtu, USHORT RegAdd, USHORT RegCount, short* &list)
{
	USHORT crc16;
	USHORT crctmp;
	short vartmp;

	//发送数据
	ULONG strlen;
	UCHAR buff[256];
	if (IsOpen())
	{
		//读数据
		memset(buff, 0x00, 255);
		strlen = ReadChar(2 * RegCount + 9, (char *)buff, 1000);
		if (strlen == 0)
		{
			//无返回
			return(-2);
		}
		else
		{
			//返回长度有效,解析接收缓冲区
			if (strlen == 2 * RegCount + 9 && buff[0] == rtu && buff[1] == 0x10)
			{
				crc16 = CalcCrcFast(buff, 7 + (RegCount * 2));
				crctmp = buff[strlen - 2];
				crctmp = crctmp << 8 | buff[strlen - 1];
				if (list == NULL)
				{
					list = new short[RegCount];
				}
				if (crc16 == crctmp)
				{
					for (int i = 0; i< RegCount; i++)
					{
						vartmp = buff[7 + (2 * i)];
						vartmp = vartmp << 8;
						vartmp = vartmp | buff[7 + ((2 * i) + 1)];
						list[i] = vartmp;
					}
				}
				else
				{
					return -1;
				}
			}
			else
				return -1;
		}

		memset(buff, 0x00, 255);
		buff[0] = rtu;
		buff[1] = 0x10;
		buff[2] = (UCHAR)((RegAdd) >> 8);
		buff[3] = (UCHAR)(RegAdd);
		buff[4] = (UCHAR)(RegCount >> 8);
		buff[5] = (UCHAR)RegCount;
		crc16 = CalcCrcFast(buff, 6);
		buff[6] = (UCHAR)(crc16 >> 8);
		buff[7] = (UCHAR)crc16;

		Sleep(50);
		//发送数据
		strlen = WriteChar(8, (char *)buff);
		if (strlen == 8)
		{

			return 0;
		}
		else
		{
			return -2;
		}
	}
	else
		return -2;
}

USHORT WINAPI Modbus::CalcCrcFast(UCHAR *puchMsg, USHORT usDataLen)
{
	UCHAR uchCRCHi = 0xFF;
	UCHAR uchCRCLo = 0xFF;
	USHORT uIndex;

	while (usDataLen--)
	{
		uIndex = uchCRCHi^*puchMsg++;
		uchCRCHi = uchCRCLo^m_auchCRCHi[uIndex];
		uchCRCLo = m_auchCRCLo[uIndex];
	}
	return(uchCRCHi << 8 | uchCRCLo);
}

int WINAPI Modbus::OpenPort(ULONG xPort, ULONG xBabd, UCHAR xDataSize, UCHAR xParity, UCHAR xStopBit,
	ULONG InputBuffSize, ULONG OutputBuffSize, ULONG dwTimerOut)
{
	if (IsOpen())
	{
		Close();
	}
	//设置事件 
	memset(&m_overlappedRead, 0, sizeof(OVERLAPPED));
	m_overlappedRead.hEvent = CreateEvent(NULL, FALSE, TRUE, L"portread");
	if (m_overlappedRead.hEvent == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	memset(&m_overlappedWrite, 0, sizeof(OVERLAPPED));
	m_overlappedWrite.hEvent = CreateEvent(NULL, FALSE, TRUE, L"portwrite");
	if(m_overlappedWrite.hEvent == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	//取得串口字符
	/*char com_str[255];
	strcpy_s(com_str, "COM");
	_ltoa(xPort, com_str + 3, 10);*/
	wchar_t com_str[255] = L"COM";
	//_ltow(xPort, com_str + 3, 10);
	_ltow_s(xPort, com_str + 3, 100, 10);
	//打开通讯端口 
	hCom = CreateFileW(com_str,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL
		);
	if (hCom == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	SetPortBuffSize(InputBuffSize, OutputBuffSize);
	SetDCBParm(xBabd, xDataSize, xParity, xStopBit);
	SetTimerOut(dwTimerOut);
	//GetInBuffCount();
	//清理缓冲器
	PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	return 0;
}

bool WINAPI Modbus::IsOpen()
{
	return hCom != INVALID_HANDLE_VALUE;
}

void WINAPI Modbus::SetTimerOut(ULONG dwTimerOut)
{
	if (!IsOpen())
	{
		return;
	}
	CommTimerOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimerOuts.ReadTotalTimeoutConstant = 0;
	CommTimerOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimerOuts.WriteTotalTimeoutConstant = dwTimerOut;
	CommTimerOuts.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(hCom, &CommTimerOuts);
}

bool WINAPI Modbus::SetDCBParm(ULONG xBabd, UCHAR xDataSize, UCHAR xParity, UCHAR xStopBit)
{
	if (!IsOpen())
	{
		return false;
	}
	if (!GetCommState(hCom, &dcb))
	{
		Close();
		return false;
	}
	//设置通讯参数   	
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = xBabd;     // set the baud rate
	dcb.ByteSize = xDataSize; // data size, xmit, and rcv
	dcb.Parity = xParity;   // no parity bit
	dcb.StopBits = xStopBit;  // one stop bit	
	if (!SetCommState(hCom, &dcb))
	{
		Close();
		return false;
	}
	return true;
}

bool WINAPI Modbus::SetPortBuffSize(ULONG InputBuffSize, ULONG OutputBuffSize)
{
	if (!IsOpen())
	{
		return false;
	}
	if (!SetupComm(hCom, InputBuffSize, OutputBuffSize))
	{
		Close();
		return false;
	}
	return true;
}

void WINAPI Modbus::ClearBuffer()
{
	if (!IsOpen())
	{
		return;
	}
	PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
}

ULONG WINAPI Modbus::GetInBuffCount()

{
	if (!IsOpen())
	{
		return(0);
	}
	DWORD     dwErrorFalgs;
	COMSTAT   Comstat;
	ClearCommError(hCom, &dwErrorFalgs, &Comstat);
	return Comstat.cbInQue;
}

ULONG WINAPI Modbus::GetOutBuffCount()
{
	if (!IsOpen())
	{
		return false;
	}
	DWORD     dwErrorFalgs;
	COMSTAT   Comstat;
	ClearCommError(hCom, &dwErrorFalgs, &Comstat);
	return Comstat.cbOutQue;
}

ULONG WINAPI Modbus::ReadChar(ULONG dwBufferLength, char *buff, ULONG dwWaitTime = 500)
{
	if (!IsOpen())
	{
		return(0);
	}

	DWORD		dwError;
	COMSTAT		Stat;
	if (::ClearCommError(hCom, &dwError, &Stat) && dwError > 0)	//清除错误
	{
		::PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR); /*清除输入缓冲区*/
		return 0;
	}

	if (!Stat.cbInQue)// 缓冲区无数据
	{
		return 0;
	}

	unsigned long uReadLength = 0;
	//dwBufferLength = dwBufferLength - 1 > Stat.cbInQue ? Stat.cbInQue : dwBufferLength - 1;
	if (!::ReadFile(hCom, buff, dwBufferLength, &uReadLength, &m_overlappedRead)) //2000 下 ReadFile 始终返回 True
	{
		if (::GetLastError() == ERROR_IO_PENDING) // 结束异步I/O
		{
			WaitForSingleObject(m_overlappedRead.hEvent, dwWaitTime);	//等待20ms
			if (!::GetOverlappedResult(hCom, &m_overlappedRead, &uReadLength, false))
			{
				if (::GetLastError() != ERROR_IO_INCOMPLETE)//其他错误
				{
					uReadLength = 0;
				}
			}
		}
		else
		{
			uReadLength = 0;
		}
	}
	//TRACE("%d,%d,%d,%d,%d,%d",buff[0],buff[1],buff[2],buff[3],buff[4],buff[5]);
	return uReadLength;
}

ULONG WINAPI Modbus::WriteChar(ULONG dwBufferLength, char *buff)
{
	if (!IsOpen())
	{
		return 0;
	}

	DWORD dwError;
	if (ClearCommError(hCom, &dwError, NULL) && dwError > 0)	//清除错误
	{
		PurgeComm(hCom, PURGE_TXABORT | PURGE_TXCLEAR);
	}

	unsigned long uWriteLength = 0;
	if (!WriteFile(hCom, buff, dwBufferLength, &uWriteLength, &m_overlappedWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			DWORD m_tmp = 0;
			m_tmp = WaitForSingleObject(m_overlappedWrite.hEvent, 1000);
			if (m_tmp == WAIT_TIMEOUT || m_tmp == WAIT_ABANDONED)
			{
				return(0);
			}
			else if (m_tmp == WAIT_OBJECT_0)
			{
				if (!GetOverlappedResult(hCom, &m_overlappedWrite, &uWriteLength, false))
				{
					return(0);
				}
				else
				{
					return uWriteLength;
				}
			}

			uWriteLength = 0;
		}
	}

	return uWriteLength;
}
