#include "server.h"

// https://www.iana.org/assignments/http-status-codes/http-status-codes.txt
int main() {
    Http09Server *server = init_server(8080);
    start(server);

    return 0;
}