#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "UDP_client_1.h"

LocalClient::LocalClient() {
	hClient = 0;
	nservAddr = 0;
	memset(&servAddr, 0x00, sizeof(SOCKADDR_IN));
}
int LocalClient::InitSocket(const char* ip, int port) {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cerr << "소켓 초기화 실패" << endl;
		return -1;
	}
	hClient = socket(PF_INET, SOCK_DGRAM, 0);
	if (hClient == INVALID_SOCKET) {
		cerr << "소켓 생성 실패" << endl;
		return -1;
	}
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &servAddr.sin_addr);
	servAddr.sin_port = htons(port);

	return 0;
}

int LocalClient::Running() {
	char buf[MAX_BUFFER];
	char sendData[MAX_BUFFER];
	const char* temp = "th message received : ";
	int msg = 0;
	nservAddr = sizeof(servAddr);
	while (true) {
		ZeroMemory(sendData, sizeof(sendData));
		ZeroMemory(buf, sizeof(buf));
		nservAddr = sizeof(servAddr);
		fseek(stdin, 0, SEEK_END);
		cout << " >> ";
		cin.getline(sendData, MAX_BUFFER, '\n');
		msg++;
		strcat(itoa(msg, buf, 10), temp);
		strcat(buf, sendData);
		sendto(hClient, buf, strlen(buf), 0, (SOCKADDR*)&servAddr, sizeof(servAddr));
		recvfrom(hClient, buf, MAX_BUFFER, 0, (SOCKADDR*)&servAddr, &nservAddr);
		cout << "[SERVER] ";
		cout << buf << endl;
	}
	closesocket(hClient);
	return 0;
}

int main() {
	LocalClient echoClient;
	if (echoClient.InitSocket("127.0.0.1", 9123) == -1) return -1;
	echoClient.Running();

	return 0;
}