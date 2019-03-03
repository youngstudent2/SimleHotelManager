#pragma once
#include <WINSOCK2.H>
#include <WS2tcpip.h>
#include <string>
//#pragma comment(lib,"ws2_32.lib")
//using namespace std;

class TcpServer
{
public:
	int init() {
		//创建套接字		
		myVersionRequest = MAKEWORD(1, 1);
		int err;
		err = WSAStartup(myVersionRequest, &wsaData);
		if (!err)
		{
			//printf("已打开套接字\n");
		}
		else
		{
			//进一步绑定套接字
			//printf("嵌套字未打开!");
			return 0;
		}
		serSocket = socket(AF_INET, SOCK_STREAM, 0);//创建了可识别套接字
		
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
		addr.sin_port = htons(6000);//绑定端口

		bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
		listen(serSocket, 5);//其中第二个参数代表能够接收的最多的连接数

		
	}
	void acceptSocket() {
		//开始监听		
		int len = sizeof(SOCKADDR);
		serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);

		char greetWord[100];//打招呼
		char IPdotdec[20];
		
		//sprintf_s(greetWord, "welcome %s", inet_ntoa(clientsocket.sin_addr));//找对对应的IP并且将这行字打印到那里
		inet_ntop(AF_INET, &clientsocket.sin_addr, IPdotdec, 16);
		sprintf_s(greetWord, "welcome %s", IPdotdec);
		/////////
		send(serConn, greetWord, strlen(greetWord) + 1, 0);
	}
	void sendHotelInfo(std::string hotelInfo) {
		hotelInfo += "#";//包的终止符
		send(serConn, hotelInfo.c_str(), hotelInfo.size() + 1, 0);
	}
	void close() {
		closesocket(serConn);//关闭	
		WSACleanup();//释放资源的操作
	}
private:
	WORD myVersionRequest;
	WSADATA wsaData;
	SOCKADDR_IN clientsocket;
	SOCKET serConn;
	SOCKET serSocket;
	//需要绑定的参数
	SOCKADDR_IN addr;
};