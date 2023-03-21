#include "TCP_client.h"

int main() {
	openSocket();
	return 0;
}

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
		cerr << "Client: WSA() 오류";
		WSACleanup();
		return;
	}

	SOCKET s;
	s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		cerr << "Client: socket() 오류";
		closesocket(s);
		WSACleanup();
		return;
	}

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9123);
	addr.sin_addr.s_addr = inet_addr("192.168.0.100");

	while (connect(s, (SOCKADDR*)&addr, sizeof(addr)));

	thread(recv_data, ref(s)).detach();
	char buf[MAX_SIZE];
	int msg = 0;
	while (!WSAGetLastError()) {
		ZeroMemory(buf, sizeof(buf));
		fseek(stdin, 0, SEEK_END);
		cout << " >> ";
		cin.getline(buf, MAX_SIZE, '\n');
		send(s, buf, strlen(buf), 0);
		msg++;
		cout << "[SERVER] " << msg << "th message received : " << buf << endl;
	}
	closesocket(s);
	WSACleanup();
}

