#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
#define MAX_SIZE 1024
using namespace std;

WSADATA wsa;
SOCKET s, *client_socket;
SOCKADDR_IN* client;
int* client_size;
void recv_data(SOCKET& s, int client_num);
void accept_client();
void openSocket();