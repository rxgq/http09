#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h> 

typedef struct {
    int port;
    SOCKET socket;
} HttpServer;

int init_server(HttpServer *server);
int start_server(HttpServer *server);

#endif