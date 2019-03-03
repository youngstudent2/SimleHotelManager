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
		//�����׽���		
		myVersionRequest = MAKEWORD(1, 1);
		int err;
		err = WSAStartup(myVersionRequest, &wsaData);
		if (!err)
		{
			//printf("�Ѵ��׽���\n");
		}
		else
		{
			//��һ�����׽���
			//printf("Ƕ����δ��!");
			return 0;
		}
		serSocket = socket(AF_INET, SOCK_STREAM, 0);//�����˿�ʶ���׽���
		
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip��ַ
		addr.sin_port = htons(6000);//�󶨶˿�

		bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//�����
		listen(serSocket, 5);//���еڶ������������ܹ����յ�����������

		
	}
	void acceptSocket() {
		//��ʼ����		
		int len = sizeof(SOCKADDR);
		serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);

		char greetWord[100];//���к�
		char IPdotdec[20];
		
		//sprintf_s(greetWord, "welcome %s", inet_ntoa(clientsocket.sin_addr));//�ҶԶ�Ӧ��IP���ҽ������ִ�ӡ������
		inet_ntop(AF_INET, &clientsocket.sin_addr, IPdotdec, 16);
		sprintf_s(greetWord, "welcome %s", IPdotdec);
		/////////
		send(serConn, greetWord, strlen(greetWord) + 1, 0);
	}
	void sendHotelInfo(std::string hotelInfo) {
		hotelInfo += "#";//������ֹ��
		send(serConn, hotelInfo.c_str(), hotelInfo.size() + 1, 0);
	}
	void close() {
		closesocket(serConn);//�ر�	
		WSACleanup();//�ͷ���Դ�Ĳ���
	}
private:
	WORD myVersionRequest;
	WSADATA wsaData;
	SOCKADDR_IN clientsocket;
	SOCKET serConn;
	SOCKET serSocket;
	//��Ҫ�󶨵Ĳ���
	SOCKADDR_IN addr;
};