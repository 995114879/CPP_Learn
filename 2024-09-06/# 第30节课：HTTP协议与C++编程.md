# 第30节课：HTTP协议与C++编程

## 课程目标
- 理解HTTP协议的基本概念和结构
- 学习如何使用命令行工具 `curl` 来测试HTTP请求
- 编写C++程序实现简单的HTTP请求
- 解析和处理HTTP响应

---

## 章节1：HTTP协议基础

### 1.1 什么是HTTP协议？
HTTP（HyperText Transfer Protocol）是用于万维网上的分布式、协作式和超媒体信息系统的应用层协议。

### 1.2 HTTP请求结构
一个HTTP请求由下列部分组成：
- 请求行（Request Line）
- 请求头（Request Headers）
- 空行
- 可选的请求体（Request Body）

### 1.3 HTTP响应结构
一个HTTP响应由下列部分组成：
- 状态行（Status Line）
- 响应头（Response Headers）
- 空行
- 可选的响应体（Response Body）

---

## 章节2：使用curl命令行工具

### 2.1 GET请求示例
使用GET请求来获取网页内容。

```bash
curl -X GET http://www.example.com
~~~

### 2.2 POST请求示例

使用POST请求来提交表单数据。



```bash
curl -X POST http://www.example.com/form -d "key1=value1&key2=value2"
```

### 2.3 设置自定义头信息

添加自定义头信息以发送不同类型的请求。



```bash
curl -X GET http://www.example.com -H "Authorization: Bearer <token>"
```

### 2.4 下载文件

将服务返回的数据保存到文件中。



```bash
curl -O http://www.example.com/file.zip
```

------

## 章节3：使用C++进行HTTP请求

### 3.1 设置C++开发环境

确保安装了支持C++17或更高标准的编译器，并安装了curl库来处理HTTP请求。

- **安装libcurl：**

   

  **Ubuntu:**

  

  ```bash
  sudo apt-get install libcurl4-openssl-dev
  ```


### 3.2 发送GET请求

使用libcurl在C++中发送GET请求。



```cpp
#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << readBuffer << std::endl;
    }

    return 0;
}
```

### 3.3 发送POST请求

使用libcurl在C++中发送POST请求。



```cpp
#include <iostream>
#include <curl/curl.h>

int main()
{
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com/form");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "key1=value1&key2=value2");

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
```

### 3.4 添加HTTP头信息

在C++中设置HTTP请求的头信息。



```cpp
#include <iostream>
#include <curl/curl.h>

int main()
{
    CURL* curl;
    CURLcode res;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer <token>");

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com/api");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
    }

    curl_slist_free_all(headers);
    curl_global_cleanup();
    return 0;
}
```

### 3.5 处理HTTP响应

解析HTTP响应的头部和内容。



```cpp
#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            std::cout << "HTTP code: " << http_code << std::endl;

            std::cout << "Response: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
```

------

## HTTP 服务器原理讲解

实现一个简单的 HTTP 服务器仅使用 C++ 标准库，对于基本的 GET 和 POST 请求的支持，可以通过 UNIX 系统的套接字 API 来实现。在这个实现演示中，一个最小功能的 HTTP 服务器将解析简单的 HTTP 请求并提供响应。

这是一个使用 C++ 和标准 POSIX Socket API 实现简单 HTTP 服务器的完整示例：

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

const int PORT = 8080;

// Function for handling client connections
void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = read(client_socket, buffer, 1024);
    if (bytes_read < 0) {
        std::cerr << "Failed to read from socket\n";
        close(client_socket);
        return;
    }

    std::string request(buffer, bytes_read);
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

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "setsockopt failed\n";
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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
```

### 服务器说明

1. **套接字创建**：
   - 使用 `socket()` 创建一个 TCP socket。
   
2. **设置选项**：
   - 使用 `setsockopt()` 设置套接字选项，以便在服务器关闭后立即重用端口。

3. **绑定和监听**：
   - 将服务器绑定到本地的指定端口 `8080`。
   - `listen()` 方法监听传入的连接。

4. **接受连接**：
   - `accept()` 用于接受进入的连接，并为每个连接生成一个线程通过 `std::thread` 调用 `handle_client()`。

5. **请求处理**：
   - 通过 `read()` 从套接字读取客户端请求。
   - 解析 `GET` 和 `POST` 请求，返回相应的响应。
   - 使用 `send()` 发送 HTTP 响应到客户端。

### 测试

编译并运行你的服务器后，可以使用 `curl` 来测试它：

- **GET 请求**：
  ```bash
  curl -X GET http://localhost:8080/
  ```

- **POST 请求**：
  ```bash
  curl -X POST http://localhost:8080/ -d "test data"
  
  # 上传图片
  curl -X POST \
       -H "Content-Type: application/octet-stream" \
       --upload-file qmsht.jpeg \
       http://127.0.0.1:8080/upload
  ```

该服务器只是一个最小化的演示，能够处理基本的 GET 和 POST 请求，并返回有限的响应。在生产中应使用更健壮和成熟的解决方案来处理HTTP服务器需求，包括错误处理、并发管理以及HTTP协议的完整实现。



## 作业：

(1) 将客户端和服务端的代码都自己再写一遍，理解一 下。

(2) 基于 Python，Flaskapi 库实现简单 http 请求（这 个作业不提交）