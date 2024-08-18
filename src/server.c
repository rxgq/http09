#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "server.h"

int init_server(HttpServer *server) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup Failed");
        return 1;
    }

    server->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->socket == INVALID_SOCKET) {
        printf("Socket creation failed");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(server->port);

    if (bind(server->socket, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("Socket binding failed");
        closesocket(server->socket);
        WSACleanup();
        return 1;
    }

    if (listen(server->socket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Socket listening failed");
        closesocket(server->socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port: %d", server->port);
    return 0;
}

int start_server(HttpServer *server) {
    while (1) {
        SOCKET client_socket;
        struct sockaddr_in client_addr;
        int client_addr_size = sizeof(client_addr);
        client_socket = accept(server->socket, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == INVALID_SOCKET) {
            printf("Client accept failed");
            return 1;
        }

        char buffer[1024];
        int bytes_recieved = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recieved > 0) {
            buffer[bytes_recieved] = '\0';

            const char* response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 13\r\n"
                "\r\n"
                "Hello, World!";

            send(client_socket, response, strlen(response), 0);
        }

        closesocket(client_socket);
    }

    closesocket(server->socket);
    WSACleanup();
    return 0;
}