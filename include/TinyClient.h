#ifndef TINY_CLIENT_H
#define TINY_CLIENT_H
#include "common.h"

class TinyClient {
private:
    int sock;
public:
    TinyClient():sock(socket(AF_INET, SOCK_STREAM, 0)) {}
    ~TinyClient() { close(sock); }

    void call(const char *domain, unsigned short int port, const char *message) {
        // 获取域名对应信息, 这里需要的是IP信息
        hostent *host = gethostbyname(domain); // netdb.h

        // 将请求地址, 端口写入到server_addr中
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);
        server_addr.sin_port = htons(port); // 注意转化大小端

        // 连接阻塞
        connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

        // 连接后传输内容
        write(sock, message, strlen(message));
        char buf[10240];
        // 保存返回内容
        read(sock, buf, sizeof(buf));
        printf("%s\n", buf);
    }
};

#endif