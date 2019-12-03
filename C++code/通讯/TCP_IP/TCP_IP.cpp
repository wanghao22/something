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
		//str = "没有客户端连接";
		return -1;
	}
	int rst = send(socketClient, strBuf, strlen(strBuf), 0);
	if (rst != strlen(strBuf) || rst == SOCKET_ERROR)
	{
		//str = "消息发送失败";
		return -1;
	}

	//显示发送的消息
	//str = string(strBuf) + "发送成功";
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
	//初始化WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		//str = "初始化WSA失败！TCP连接失败！";
		return;
	}

	//创建套接字
	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (socketServer == INVALID_SOCKET)
	{
		tcpServerState = false;
		//str = "创建套接字失败！TCP连接失败！";
		return;
	}

	//绑定IP和端口
	u_short port = u_short(_TCP_SERVER_PORT_);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(socketServer, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		tcpServerState = false;
		//str = "绑定IP和端口失败！TCP连接失败！";
		return;
	}

	//开始监听
	if (listen(socketServer, 5) == SOCKET_ERROR)
	{
		tcpServerState = false;
		//str = "开启监听失败！TCP连接失败！";
		return;
	}

	//循环接收数据
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
			//str = "接受数据失败！";
			break;
		}
		else
		{
			tcpServerState = true;
			//发送一个消息显示客户端连接
			//str = "客户端" + string(inet_ntoa(remoteAddr.sin_addr)) + "已接入";
		}
		//创建接收数据线程
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
		//发送消息显示接收到的消息
		str = string(recvBuff);
	}
	tcpServerState = false;
	//发送一个消息显示客户端断开
	//str = "客户端" + string(inet_ntoa(remoteAddr.sin_addr)) + "已断开";
	return;
}

std::thread WINAPI TCP_IP::GetThreadRecv(SOCKET  sock, string &str)
{//return是因为运行时要获取线程句柄
	return std::thread(&TCP_IP::ThreadRecvData, this, sock, std::ref(str));
}