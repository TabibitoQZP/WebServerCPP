#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

int main(int argc, char **argv) {
    // 1. create socket
    int listenSoc = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSoc < 0) {
        printf("can not create socket.");
        return -1;
    }

    // 2. bind
    unsigned int port = 5001;
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    bind(listenSoc, (sockaddr *)&sin, sizeof(sin));

    // 3. listen
    listen(listenSoc, 1024);

    // 4. stuck
    struct sockaddr_in cliaddr;
    int clilen = sizeof(cliaddr);
    int cfd = accept(listenSoc, (struct sockaddr*)&cliaddr, (socklen_t *)&clilen);

    while(1) {
        // 接收数据
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        int len = read(cfd, buf, sizeof(buf));
        if(len > 0) {
            printf("客户端say: %s\n", buf);
            write(cfd, buf, len);
        }
        else if(len  == 0) {
            printf("客户端断开了连接...\n");
            break;
        }
        else {
            perror("read");
            break;
        }
    }
    close(cfd);
    close(listenSoc);
    return 0;
}