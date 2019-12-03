#pragma once
#include <iostream>
#include <winsock2.h>
#include <vector>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define TCP_STR_LEN	100
#define _TCP_SERVER_PORT_ 3000

/*
������õ���������������inet_ntoa������ʱ������������->C++->SDL������λ�񼴿�
*/

class __declspec(dllexport) TCP_IP
{
public:
	TCP_IP();
	~TCP_IP();
	/*��������
	@param1:Ҫ���͵�����
	@return:���ͳɹ�(0)/ʧ��(-1)*/
	int WINAPI tcpServerSendMessage(char strBuf[TCP_STR_LEN]);
	
	/*����TCP�����߳�
	@param1:NULL
	@return:���ص�ǰTCP����״̬*/
	bool WINAPI  GetTCPState();
	
	/*����TCP�����߳�
	@param1:���ص��ַ���
	@return:NULL*/
	void WINAPI ThreadTcpServerStart(string &str);

	/*��ȡ��ǰ�ͻ��˵�ַ
	@param1:NULL
	@return:���ص�ǰ�ͻ��˵�ַ*/
	IN_ADDR WINAPI GetAddr();
private:
	/*TCP�����߳�
	@param1:���ص��ַ���
	@return:NULL*/
	void WINAPI ThreadTcpServer(string &str);
	
	/*���������߳�
	@param1:�ͻ���Ƕ����
	@param2:���ص��ַ���
	@return:NULL*/
	void WINAPI ThreadRecvData(SOCKET  sock, string &str);

	/*���ؽ��������߳�
	@param1:�ͻ���Ƕ����
	@param2:���ص��ַ���
	@return:NULL*/
	std::thread WINAPI GetThreadRecv(SOCKET  sock, string &str);
	SOCKET socketServer, socketClient;
	char recvBuff[TCP_STR_LEN];
	bool tcpServerState;
	bool bThreadTcpComm;
	sockaddr_in remoteAddr;
	
};