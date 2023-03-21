#include "TCP_server.h"

int main() {
	client_socket = new SOCKET[10];
	client = new SOCKADDR_IN[10];
	client_size = new int[10];
	ZeroMemory(client_socket, sizeof(client_socket));
	ZeroMemory(client, sizeof(client));
	ZeroMemory(client_size, sizeof(client_size));
	openSocket();
	delete[] client_socket, client, client_size;
	return 0;
}

void recv_data(SOCKET& s, int client_num) {
	char buf[MAX_SIZE];
	int msg = 0;
	while (true) {
		ZeroMemory(buf, MAX_SIZE);
		if (recv(s, buf, MAX_SIZE, 0) == -1) break;
		msg++;
		cout << "Client #" << client_num << " >> " << msg 
			<< "th message received : " << buf << endl;
	}
	return;
}


void accept_client() {
	char client_num[10];
	for (int i = 0; i < 10; i++) {
		client_size[i] = sizeof(client[i]);
		client_socket[i] = accept(s, (SOCKADDR*)&client[i], &client_size[i]);
		if (client_socket[i] == INVALID_SOCKET) {
			cerr << "accept() 오류";
			closesocket(client_socket[i]);
			closesocket(s);
			WSACleanup();
			return;
		}
		cout << "Client #" << i << " is Joined!" << endl;
		ZeroMemory(client_num, sizeof(client_num));
		_itoa(i, client_num, 10);
		send(client_socket[i], client_num, strlen(client_num), 0);
		thread(recv_data, ref(client_socket[i]), i).detach();
	}
	return;
}
void openSocket() {
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
		cerr << "WSA() 오류";
		return;
	}
	s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		cerr << "socket() 오류";
		closesocket(s);
		WSACleanup();
		return;
	}

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9123);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (SOCKADDR*)&addr, sizeof(addr))) {
		cout << "bind() 오류";
		closesocket(s);
		WSACleanup();
		return;
	}
	if (listen(s, SOMAXCONN)) {
		cout << "listen() 오류";
		closesocket(s);
		WSACleanup();
		return;
	}
	thread(accept_client).detach();
	char msg[MAX_SIZE];
	while (true) {
		ZeroMemory(msg, MAX_SIZE);
		int i = 0;
		for (i = 0; i < 10; i++) {
			recv(client_socket[i], msg, strlen(msg), 0);
			if (msg != NULL) send(client_socket[i], msg, strlen(msg), 0);
		}
	}
	for (int i = 0; i < 10; i++) closesocket(client_socket[i]);
	closesocket(s);
	WSACleanup();
	return;
}

