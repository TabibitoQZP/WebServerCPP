#include "common.h"

int main(int argc, char **argv) {
    int port = 5001;
    if (argc > 1) {
        TinyServer server(port);
    }
    else {
        TinyClient tc;
        tc.call("127.0.0.1", port, "sdfa");
    }

    return 0;
}