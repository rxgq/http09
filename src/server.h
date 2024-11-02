typedef struct {
    int port;
} Http09Server;

Http09Server *init_server(int port);
void start(Http09Server *server);