#pragma once
class SerialPort
{
public:
	SerialPort();
	~SerialPort();

	HANDLE m_hComm;//���ھ��
	OVERLAPPED m_overlappedWrite;
	OVERLAPPED m_overlappedRead;

	unsigned short CalcCrcFast(unsigned char*puchMsg, unsigned short usDataLen);//У��λ

	bool openComm(CString CommPort);//�򿪴���
	unsigned long WriteChar(unsigned long dwBufferLength, char *buff);//д
	unsigned long ReadChar(unsigned long dwBufferLength, char *buff, unsigned long dwWaitTime);//��

	//������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�
	char MODBUS_ReadMultiOptocoupler(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list);//ModBus������
	bool Write_Register(char data[],int dataLength);//д�̵���

};

