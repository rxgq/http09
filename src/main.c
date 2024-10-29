#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFF_SIZE 1024

int main() {
    WSADATA wsaData;

    SOCKET sock;
    struct sockaddr_in server;

    WSAStartup(MAKEWORD(2,2), &wsaData);

    // Creates a TCP socket (AF_INET for IPv4, SOCK_STREAM for TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    char buff[BUFF_SIZE];
    while (1) {
        printf("\nEnter message: ");
        fgets(buff, BUFF_SIZE, stdin);

        send(sock, buff, strlen(buff), 0);
        int recvSize = recv(sock, buff, BUFF_SIZE, 0);
        buff[recvSize] = '\0';

        printf("Recieved: %s", buff);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}