#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFF 1024

int main() {
    WSADATA wsaData;
    SOCKET server, client;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("wsa failed to initialise");
        return 1;
    }

    // AF_INET specifies IPv4
    // SOCK_STREAM is is TCP for IPv4
    // IPROTO_TCP specifies TCP
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)

    return 0;
}
