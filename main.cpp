#include "common.h"

int main() {
    int port = 5001;
    HTTPServer server(port);
    server.start();

    return 0;
}