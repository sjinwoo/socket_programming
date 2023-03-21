#pragma once
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define MAX_BUFFER 1024

class LocalClient
{
public:
	LocalClient();
	~LocalClient() {};
	int InitSocket(const char* ip, int port);
	int Running();
	WSADATA wsaData;
	SOCKET hClient;
	SOCKADDR_IN servAddr;
	int nservAddr;
};