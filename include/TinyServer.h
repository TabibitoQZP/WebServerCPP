#ifndef TMP_H
#define TMP_H

#include "common.h"

class TinyServer{
private:
    int serverFd, clientFd;
    struct sockaddr_in serverAddr, clientAddr;
    std::string send;
public:
    TinyServer(unsigned short int port) {
        send = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>fuck!</h1>";

        // 1. 设置server的文件描述符绑定socket
        serverFd = socket(AF_INET, SOCK_STREAM, 0);

        // 2. 设置server的地址, 端口
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        // 3. 绑定socket和地址端口
        bind(serverFd, (const sockaddr *) &serverAddr, sizeof(serverAddr));

        // 4. 监听地址端口, 最多支持8个请求
        listen(serverFd, 8);

        while (1) {
            // 5. 使用accept创建一个client的文件描述符
            socklen_t clientLen = sizeof(clientAddr);
            clientFd = accept(serverFd, (sockaddr *) &clientAddr, &clientLen);
            printf("%s %d\n", inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port);

            // 6. 写入, 注意这里buf如果不够大会很麻烦, 循环结束很难判断
            char buf[1024];
            read(clientFd, buf, sizeof(buf)); // 返回值是写入的字节数
            write(clientFd, send.c_str(), send.size()); // 写入到文件中
            close(clientFd);
        }
        close(serverFd);
    }
    ~TinyServer() { close(serverFd); close(clientFd); }
};

#endif