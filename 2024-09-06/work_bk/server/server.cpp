#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <vector>
#include <fcntl.h>

const int PORT = 8080;

// Function for handling client connections
void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = 0;
    std::string request;

    // 读取 Headers
    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        request.append(buffer, bytes_read);
        if (request.find("\r\n\r\n") != std::string::npos) {
            break; // Headers 读取完成
        }
    }

    std::cout << "Headers:\n" << request.substr(0, request.find("\r\n\r\n")) << "\n"; 

    if (bytes_read < 0) {
        std::cerr << "Failed to read from socket\n";
        close(client_socket);
        return;
    }

    std::istringstream request_stream(request);
    std::string method;
    std::string path;
    std::string version;

    request_stream >> method >> path >> version;

    std::string response;

    if (method == "GET") {
        if (path == "/") {
            response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 13\r\n"
                "\r\n"
                "Hello, World!";
        } else {
            response = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 9\r\n"
                "\r\n"
                "Not Found";
        }
    } else if (method == "POST" && path == "/upload") {
        // 获取 Content-Length
        size_t contentLength = 0;
        size_t contentLengthPos = request.find("Content-Length: ");
        if (contentLengthPos != std::string::npos) {
            size_t endPos = request.find("\r\n", contentLengthPos);
            std::string contentLengthStr = request.substr(contentLengthPos + 16, endPos - (contentLengthPos + 16));
            contentLength = std::stoul(contentLengthStr);
        }

        // 跳过 Headers，找到数据起始位置
        size_t bodyStartPos = request.find("\r\n\r\n") + 4;
        size_t alreadyRead = request.length() - bodyStartPos; 
        size_t remaining = contentLength - alreadyRead;

        // 写入文件
        std::ofstream file("uploaded_image.jpeg", std::ios::binary);
        if (!file) {
            // ... (处理文件打开失败) ...
        }

        // 写入已读取的部分数据
        file.write(request.c_str() + bodyStartPos, alreadyRead);

        // 读取剩余数据
        while (remaining > 0) {
            bytes_read = read(client_socket, buffer, std::min((size_t)sizeof(buffer), remaining));
            if (bytes_read > 0) {
                file.write(buffer, bytes_read);
                remaining -= bytes_read;
            } else if (bytes_read == 0) {
                break; // 客户端关闭连接
            } else {
                // ... (处理读取错误) ...
                break;
            }
        }

        file.close();

        response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/plain\r\n"
                   "Content-Length: 11\r\n"
                   "\r\n"
                   "File saved.";
    } else if (method == "POST") {
        std::string header;
        std::string request_body;
        while (std::getline(request_stream, header) && header != "\r") {
            // Process headers if needed
        }

        if (request_stream.rdbuf()->in_avail()) {
            request_body.assign((std::istreambuf_iterator<char>(request_stream)), std::istreambuf_iterator<char>());
        }

        response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(request_body.length()) + "\r\n"
            "\r\n" + request_body;
    } else {
        response = 
            "HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 18\r\n"
            "\r\n"
            "Method Not Allowed";
    }

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket failed\n";
        exit(EXIT_FAILURE);
    }

    // 设置 socket属性 // socket => 套接字
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "setsockopt failed\n";
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); // host to network

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed\n";
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening on port " << PORT << "...\n";

    while (true) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            std::cerr << "Accept failed\n";
            continue;
        }

        // Handle each client in a separate thread
        std::thread(handle_client, client_socket).detach();
    }

    return 0;
}
