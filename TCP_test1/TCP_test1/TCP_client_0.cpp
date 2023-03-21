#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
#define MAX_SIZE 1024
using namespace std;

void recv_data(SOCKET& s) {
	char buf[MAX_SIZE];
	while (true) {
		ZeroMemory(buf, MAX_SIZE);
		recv(s, buf, MAX_SIZE, 0);
	}
	return;
}

void openSocket() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
		cout << "WSA error";
		WSACleanup();
		return;
	}

	SOCKET skt;
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET) {
		cout << "socket error";
		closesocket(skt);
		WSACleanup();
		return;
	}

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9123);
	addr.sin_addr.s_addr = inet_addr("192.168.0.100");

	while (connect(skt, (SOCKADDR*)&addr, sizeof(addr)));

	thread(recv_data, ref(skt)).detach();
	char buf[MAX_SIZE];
	int msg = 0;
	while (!WSAGetLastError()) {
		ZeroMemory(buf, sizeof(buf));
		fseek(stdin, 0, SEEK_END);
		cout << " >> ";
		cin.getline(buf, MAX_SIZE, '\n');
		send(skt, buf, strlen(buf), 0);
		msg++;
		cout << "[SERVER]" << msg << "th message received : " << buf << endl;
	}
	closesocket(skt);
	WSACleanup();
}

int main() {

	openSocket();
	return 0;
}