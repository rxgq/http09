#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include "server.h"

#pragma comment(lib, "ws2_32.lib")
#define BUFF_SIZE 1024

Http09Server *init_server(int port) {
    Http09Server *server = (Http09Server *)malloc(sizeof(Http09Server));
    server->port = port;

    return server;
}

void handle_request(SOCKET client_socket) {
    char request[BUFF_SIZE];
    int bytes_read = recv(client_socket, request, BUFF_SIZE - 1, 0);
    request[bytes_read] = '\0';
    
    if (strncmp(request, "GET ", 4) != 0) {
        printf("Method not supported.");
        closesocket(client_socket);
        return;
    }

    const char* response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 53\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";

    send(client_socket, response, strlen(response), 0);
    closesocket(client_socket);
}

void start(Http09Server *server) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server->port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    printf("HTTP/0.9 server listening on port %d\n", server->port);

    while (1) {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

        handle_request(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
}