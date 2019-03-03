#pragma once

#include <WINSOCK2.H>
#include <WS2tcpip.h>
#include <string>
//#pragma comment(lib,"ws2_32.lib")

using namespace std;

class TcpClient
{
public:
	int init(string ip) {
		int err;
		versionRequired = MAKEWORD(1, 1);
		err = WSAStartup(versionRequired, &wsaData);//Э���İ汾��Ϣ
		if (!err)
		{
			//printf("�ͻ���Ƕ�����Ѿ���!\n");
		}
		else
		{
			//printf("�ͻ��˵�Ƕ���ִ�ʧ��!\n");
			return 0;//����
		}
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);	
		//clientsock_in.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		inet_pton(AF_INET,ip.c_str(), &clientsock_in.sin_addr.s_addr);//�ַ��������·��ַ
		//clientsock_in.sin_addr.s_addr = htonl(INADDR_ANY);
		clientsock_in.sin_family = AF_INET;
		clientsock_in.sin_port = htons(6000);
		connect(clientSocket, (SOCKADDR*)&clientsock_in, sizeof(SOCKADDR));//��ʼ����
		recv(clientSocket, greetWord, 101, 0);
		return 1;
	}
	string recvMessage() {  //������"EOF"��ʾ������Ϣ�������
		char receiveBuf[1024];
		string Buff;
		int len = 1024, flag = 0;
		while (len > 0)
		{
			memset(receiveBuf, 0, len);
			recv(clientSocket, receiveBuf, strlen(receiveBuf) + 1, 0);
			len = strlen(receiveBuf);
			if (len <= 0) {
				if (flag > 1024)return "error";
				flag++;
				continue;
			}
			if (receiveBuf[len - 1] == '#')//error:����\0 ��Ҫ�����������Ϊ��ֹ��
			{
				Buff.append(receiveBuf, len - 1);
				return Buff;
			}
			else
				Buff.append(receiveBuf, len);			
		}
		return "error";
	}
	void close() {
		closesocket(clientSocket);
		WSACleanup();
	}
	char* getGreetWord() {
		return greetWord;
	}
private:
	WORD versionRequired;
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN clientsock_in;
	char greetWord[100];
};