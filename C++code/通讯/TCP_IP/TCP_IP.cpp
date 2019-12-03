#include "stdafx.h"
#include "TCP_IP.h"

//public:
TCP_IP::TCP_IP()
{
	bThreadTcpComm = false;
	tcpServerState = false;
}

TCP_IP::~TCP_IP()
{
	bThreadTcpComm = true;
}

int WINAPI TCP_IP::tcpServerSendMessage(char strBuf[TCP_STR_LEN])
{
	if (!socketClient)
	{
		//str = "û�пͻ�������";
		return -1;
	}
	int rst = send(socketClient, strBuf, strlen(strBuf), 0);
	if (rst != strlen(strBuf) || rst == SOCKET_ERROR)
	{
		//str = "��Ϣ����ʧ��";
		return -1;
	}

	//��ʾ���͵���Ϣ
	//str = string(strBuf) + "���ͳɹ�";
	return 0;
}

bool WINAPI  TCP_IP::GetTCPState()
{
	return tcpServerState;
}

void WINAPI TCP_IP::ThreadTcpServerStart(string &str)
{
	thread task(&TCP_IP::ThreadTcpServer, this, ref(str));
	task.detach();
}

IN_ADDR WINAPI TCP_IP::GetAddr()
{
	return remoteAddr.sin_addr;
}

//private:
void WINAPI TCP_IP::ThreadTcpServer(string &str)
{
	//��ʼ��WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		//str = "��ʼ��WSAʧ�ܣ�TCP����ʧ�ܣ�";
		return;
	}

	//�����׽���
	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (socketServer == INVALID_SOCKET)
	{
		tcpServerState = false;
		//str = "�����׽���ʧ�ܣ�TCP����ʧ�ܣ�";
		return;
	}

	//��IP�Ͷ˿�
	u_short port = u_short(_TCP_SERVER_PORT_);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(socketServer, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		tcpServerState = false;
		//str = "��IP�Ͷ˿�ʧ�ܣ�TCP����ʧ�ܣ�";
		return;
	}

	//��ʼ����
	if (listen(socketServer, 5) == SOCKET_ERROR)
	{
		tcpServerState = false;
		//str = "��������ʧ�ܣ�TCP����ʧ�ܣ�";
		return;
	}

	//ѭ����������
	int nAddrlen = sizeof(remoteAddr);
	HANDLE hThread;
	vector<HANDLE> hThreadArr;
	vector<SOCKET> sClientArr;
	while (!bThreadTcpComm)
	{
		socketClient = accept(socketServer, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (socketClient == INVALID_SOCKET)
		{
			tcpServerState = false;
			//str = "��������ʧ�ܣ�";
			break;
		}
		else
		{
			tcpServerState = true;
			//����һ����Ϣ��ʾ�ͻ�������
			//str = "�ͻ���" + string(inet_ntoa(remoteAddr.sin_addr)) + "�ѽ���";
		}
		//�������������߳�
		thread task = GetThreadRecv(socketClient, str);
		hThread = task.native_handle();
		task.detach();

		hThreadArr.push_back(hThread);
		sClientArr.push_back(socketClient);
	}

	for (size_t i = 0; i < hThreadArr.size(); i++)
	{
		if (hThreadArr[i])
		{
			shutdown(sClientArr[i], 2);
			closesocket(sClientArr[i]);
			WaitForSingleObject(hThreadArr[i], INFINITE);
			CloseHandle(hThreadArr[i]);
		}
	}
	WSACleanup();
	return;
}

void WINAPI TCP_IP::ThreadRecvData(SOCKET  sock, string &str)
{
	int  ret;
	while (!bThreadTcpComm)
	{
		memset(recvBuff, 0, TCP_STR_LEN);
		ret = recv(sock, recvBuff, TCP_STR_LEN, 0);
		if (SOCKET_ERROR == ret || INVALID_SOCKET == ret || 0 == recvBuff[0] || strlen(recvBuff) == 0)
		{
			tcpServerState = false;
			break;
		}
		//������Ϣ��ʾ���յ�����Ϣ
		str = string(recvBuff);
	}
	tcpServerState = false;
	//����һ����Ϣ��ʾ�ͻ��˶Ͽ�
	//str = "�ͻ���" + string(inet_ntoa(remoteAddr.sin_addr)) + "�ѶϿ�";
	return;
}

std::thread WINAPI TCP_IP::GetThreadRecv(SOCKET  sock, string &str)
{//return����Ϊ����ʱҪ��ȡ�߳̾��
	return std::thread(&TCP_IP::ThreadRecvData, this, sock, std::ref(str));
}