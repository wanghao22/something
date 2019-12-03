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
如果，用到这个类程序编译出现inet_ntoa的问题时，将配置属性->C++->SDL检测更改位否即可
*/

class __declspec(dllexport) TCP_IP
{
public:
	TCP_IP();
	~TCP_IP();
	/*发送数据
	@param1:要发送的命令
	@return:发送成功(0)/失败(-1)*/
	int WINAPI tcpServerSendMessage(char strBuf[TCP_STR_LEN]);
	
	/*开启TCP连接线程
	@param1:NULL
	@return:返回当前TCP连接状态*/
	bool WINAPI  GetTCPState();
	
	/*开启TCP连接线程
	@param1:返回的字符串
	@return:NULL*/
	void WINAPI ThreadTcpServerStart(string &str);

	/*获取当前客户端地址
	@param1:NULL
	@return:返回当前客户端地址*/
	IN_ADDR WINAPI GetAddr();
private:
	/*TCP连接线程
	@param1:返回的字符串
	@return:NULL*/
	void WINAPI ThreadTcpServer(string &str);
	
	/*接收数据线程
	@param1:客户段嵌套字
	@param2:返回的字符串
	@return:NULL*/
	void WINAPI ThreadRecvData(SOCKET  sock, string &str);

	/*返回接收数据线程
	@param1:客户段嵌套字
	@param2:返回的字符串
	@return:NULL*/
	std::thread WINAPI GetThreadRecv(SOCKET  sock, string &str);
	SOCKET socketServer, socketClient;
	char recvBuff[TCP_STR_LEN];
	bool tcpServerState;
	bool bThreadTcpComm;
	sockaddr_in remoteAddr;
	
};