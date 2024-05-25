#include "common.h"

HTTPServer::HTTPServer(int port) {
    // 创建socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Cannot open socket" << std::endl;
        exit(1);
    }

    // 配置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // 绑定socket到服务器地址
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Cannot bind" << std::endl;
        exit(1);
    }

    // 开始监听
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Cannot listen" << std::endl;
        exit(1);
    }

    std::cout << "Server listening on port " << port << std::endl;
}

void HTTPServer::start() {
    // 接受连接
    while (true) {
        int client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_len);
        if (client_fd < 0) {
            std::cerr << "Cannot accept connection" << std::endl;
            continue;
        }

        // 处理请求
        handleClient(client_fd);
        close(client_fd);
    }
}

void HTTPServer::handleClient(int client_fd) {
    std::string request;
    char buffer[1024];

    // 读取请求
    read(client_fd, buffer, sizeof(buffer));
    request = std::string(buffer);

    // 简单的请求解析，仅用于示例
    if (request.find("GET / HTTP/1.1") != std::string::npos) {
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        response += "<h1>Hello, World!</h1>";

        // 发送响应
        write(client_fd, response.c_str(), response.size());
    } else {
        // 发送错误响应
        std::string response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
        response += "<h1>404 Not Found</h1>";

        write(client_fd, response.c_str(), response.size());
    }
}