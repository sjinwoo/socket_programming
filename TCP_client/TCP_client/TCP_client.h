#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
#define MAX_SIZE 1024
using namespace std;

void recv_data(SOCKET& s);
void openSocket();