#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define MAX_SIZE 1024

class UDP_server {
public:
	UDP_server();
	~UDP_server() {};
	int start_server(int port);
	int start_UDP();
	WSADATA wsa;
	SOCKET s;
	SOCKET client_socket;
	SOCKADDR_IN server_addr;
	SOCKADDR_IN cilent_addr;
	int n_client_addr;
};