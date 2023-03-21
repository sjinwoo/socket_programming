#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define MAX_SIZE 1024

class UDP_Client
{
public:
	UDP_Client();
	~UDP_Client() {};
	int Init_socket(const char* ip, int port);
	int start_UDP();
	WSADATA wsa;
	SOCKET s;
	SOCKADDR_IN server_addr;
	int n_server_addr;
};