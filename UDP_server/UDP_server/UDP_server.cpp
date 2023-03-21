#define _CRT_SECURE_NO_WARNINGS
#include "UDP_server.h"

UDP_server::UDP_server() {
	s = 0;
	client_socket = 0;
	memset(&server_addr, 0x00, sizeof(SOCKADDR_IN));
	memset(&cilent_addr, 0x00, sizeof(SOCKADDR_IN));
	n_client_addr = 0;
}

int UDP_server::start_server(int port) {
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "WSA() 오류" << endl;
		return -1;
	}
	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) {
		cerr << "socket() 오류" << endl;
		return -1;
	}

	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	server_addr.sin_port = htons(port);
	if (bind(s, (SOCKADDR*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		cerr << "bind() 오류" << endl;
		return -1;
	}
	return 0;
}

int UDP_server::start_UDP() {
	char buf[MAX_SIZE];
	int len = 0;
	while (true) {
		ZeroMemory(buf, sizeof(buf));
		n_client_addr = sizeof(cilent_addr);
		len = recvfrom(s, buf, MAX_SIZE, 0, (SOCKADDR*)&cilent_addr, &n_client_addr);
		cout << buf << endl;
		sendto(s, buf, len, 0, (SOCKADDR*)&cilent_addr, sizeof(cilent_addr));
	}
	closesocket(s);
	return 0;
}

int main() {
	UDP_server server;
	if (server.start_server(9123) == -1) return -1;
	server.start_UDP();
	return 0;
}