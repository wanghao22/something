#pragma once
class SerialPort
{
public:
	SerialPort();
	~SerialPort();

	HANDLE m_hComm;//串口句柄
	OVERLAPPED m_overlappedWrite;
	OVERLAPPED m_overlappedRead;

	unsigned short CalcCrcFast(unsigned char*puchMsg, unsigned short usDataLen);//校验位

	bool openComm(CString CommPort);//打开串口
	unsigned long WriteChar(unsigned long dwBufferLength, char *buff);//写
	unsigned long ReadChar(unsigned long dwBufferLength, char *buff, unsigned long dwWaitTime);//读

	//参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功
	char MODBUS_ReadMultiOptocoupler(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list);//ModBus读光耦
	bool Write_Register(char data[],int dataLength);//写继电器

};

