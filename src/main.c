#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main() {
    HttpServer *server = (HttpServer *)malloc(sizeof(HttpServer));
    server->port = 8080;

    if (init_server(server) != 0) {
        free(server);
        return 1;
    }

    if (start_server(server) != 0) {
        free(server);
        return 1;
    }
    
    free(server);
    return 0;
}
