#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "common.h"

class HTTPServer {
public:
    HTTPServer(int port);
    void start();

private:
    int server_fd;
    struct sockaddr_in server_addr, client_addr;

    void handleClient(int client_fd);
};

#endif