#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "UDP_client.h"

UDP_Client::UDP_Client() {
	s = 0;
	n_server_addr = 0;
	memset(&n_server_addr, 0x00, sizeof(SOCKADDR_IN));
}
int UDP_Client::Init_socket(const char* ip, int port) {
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "Client: WSA() 오류" << endl;
		return -1;
	}
	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET) {
		cerr << "Client: socket() 오류" << endl;
		return -1;
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);

	return 0;
}

int UDP_Client::start_UDP() {
	char buf[MAX_SIZE];
	char temp[MAX_SIZE];
	const char* user_msg = "th message received : ";
	int msg = 0;
	n_server_addr = sizeof(server_addr);
	while (true) {
		ZeroMemory(temp, sizeof(temp));
		ZeroMemory(buf, sizeof(buf));
		n_server_addr = sizeof(server_addr);
		fseek(stdin, 0, SEEK_END);
		cout << " >> ";
		cin.getline(temp, MAX_SIZE, '\n');
		msg++;
		strcat(itoa(msg, buf, 10), user_msg);
		strcat(buf, temp);
		sendto(s, buf, strlen(buf), 0, (SOCKADDR*)&server_addr, sizeof(server_addr));
		recvfrom(s, buf, MAX_SIZE, 0, (SOCKADDR*)&server_addr, &n_server_addr);
		cout << "[SERVER] ";
		cout << buf << endl;
	}
	closesocket(s);
	return 0;
}

int main() {
	UDP_Client client;
	if (client.Init_socket("127.0.0.1", 9123) == -1) return -1;
	client.start_UDP();
	return 0;
}