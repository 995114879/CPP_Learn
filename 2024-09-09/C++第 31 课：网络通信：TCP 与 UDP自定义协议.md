## C++第 31 课：网络通信：基于TCP 与 UDP自定义协议

### 一、引言

在现代软件开发中，网络编程扮演着至关重要的角色。从简单的客户端-服务器应用到复杂的分布式系统，网络编程都是不可或缺的一部分。在本节课中，我们将学习两种最常用的网络协议：TCP 和 UDP，并使用 C++ 实现它们。

### 二、TCP 协议

#### 2.1 TCP 简介

传输控制协议（TCP）是一种面向连接的、可靠的、基于字节流的传输层通信协议。TCP 协议的主要特点包括：

* **面向连接:** 在传输数据之前，通信双方必须先建立连接。
* **可靠传输:** TCP 协议提供可靠的数据传输，确保数据包按顺序、无差错地到达接收方。
* **全双工通信:** 通信双方可以同时发送和接收数据。

#### 2.2 TCP 通信流程

1. **建立连接 (三次握手):**
   * 客户端发送 SYN 包到服务器，请求建立连接。
   * 服务器收到 SYN 包后，回复 SYN-ACK 包，确认连接请求。
   * 客户端收到 SYN-ACK 包后，回复 ACK 包，连接建立完成。

2. **数据传输:**  连接建立后，双方可以进行双向数据传输。

3. **关闭连接 (四次挥手):**
   * 任意一方可以主动发起关闭连接请求。
   * 双方协商关闭连接，最终断开连接。

#### 2.3 C++ 实现 TCP 服务器

```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

int main() {
  // 1. 创建 socket
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    std::cerr << "Socket creation failed" << std::endl;
    return -1;
  }

  // 2. 绑定地址和端口
  sockaddr_in address{};
  address.sin_family = AF_INET; 
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Bind failed" << std::endl;
    return -1;
  }

  // 3. 监听连接
  if (listen(server_fd, 3) < 0) {
    std::cerr << "Listen failed" << std::endl;
    return -1;
  }

  // 4. 接受连接
  int new_socket;
  sockaddr_in client_address{};
  socklen_t addrlen = sizeof(client_address);
  std::cout << "Waiting for connection..." << std::endl;
  new_socket = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);
  if (new_socket < 0) {
    std::cerr << "Accept failed" << std::endl;
    return -1;
  }

  // 5. 接收和发送数据
  char buffer[1024] = {0};
  int valread = read(new_socket, buffer, 1024);
  std::cout << "Client: " << buffer << std::endl;
  const char *message = "Hello from server";
  send(new_socket, message, strlen(message), 0);

  // 6. 关闭连接
  close(new_socket);
  close(server_fd);
  return 0;
}
```

#### 2.4 C++ 实现 TCP 客户端

```cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

int main() {
  // 1. 创建 socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  // 2. 设置服务器地址
  sockaddr_in serv_addr{};
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // 将 IPv4 地址从文本转换为二进制形式
  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
  {
      std::cerr << "Invalid address/ Address not supported" << std::endl;
      return -1;
  }

  // 3. 连接服务器
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection Failed" << std::endl;
    return -1;
  }

  // 4. 发送数据
  const char *message = "Hello from client";
  send(sock, message, strlen(message), 0);

  // 5. 接收数据
  char buffer[1024] = {0};
  int valread = read(sock , buffer, 1024);
  std::cout << "Server: " << buffer << std::endl;

  // 6. 关闭连接
  close(sock);
  return 0;
}
```

### 三、UDP 协议

#### 3.1 UDP 简介

用户数据报协议（UDP）是一种无连接的、不可靠的、面向数据报的传输层通信协议。UDP 协议的主要特点包括：

* **无连接:** 在传输数据之前，通信双方不需要建立连接。
* **不可靠传输:** UDP 协议不保证数据包能够按顺序、无差错地到达接收方。
* **高效率:** 由于没有连接建立和数据确认的开销，UDP 协议的传输效率比 TCP 协议高。

#### 3.2 UDP 通信流程

1. **发送数据:** 发送方将数据封装成数据报，并发送到网络中。
2. **接收数据:** 接收方从网络中接收数据报，并进行处理。

#### 3.3 C++ 实现 UDP 服务器

```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

int main() {
  // 1. 创建 socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    std::cerr << "Socket creation failed" << std::endl;
    return -1;
  }

  // 2. 绑定地址和端口
  sockaddr_in servaddr{};
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    std::cerr << "Bind failed" << std::endl;
    return -1;
  }

  // 3. 接收数据
  char buffer[1024];
  sockaddr_in cliaddr{};
  socklen_t len = sizeof(cliaddr);
  int n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
  buffer[n] = '\0';
  std::cout << "Client: " << buffer << std::endl;

  // 4. 发送数据
  const char *message = "Hello from server";
  sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);

  // 5. 关闭 socket
  close(sockfd);
  return 0;
}
```

#### 3.4 C++ 实现 UDP 客户端

```cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

int main() {
  // 1. 创建 socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    std::cerr << "Socket creation failed" << std::endl;
    return -1;
  }

  // 2. 设置服务器地址
  sockaddr_in servaddr{};
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  // 3. 发送数据
  const char *message = "Hello from client";
  sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

  // 4. 接收数据
  char buffer[1024];
  int n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&servaddr,  (socklen_t *)sizeof(servaddr));
  buffer[n] = '\0';
  std::cout << "Server: " << buffer << std::endl;

  // 5. 关闭 socket
  close(sockfd);
  return 0;
}
```

### 四、TCP 与 UDP 的比较

| 特性     | TCP                                      | UDP                                    |
| -------- | ---------------------------------------- | -------------------------------------- |
| 连接     | 面向连接                                 | 无连接                                 |
| 可靠性   | 可靠传输                                 | 不可靠传输                             |
| 数据传输 | 基于字节流，有序                         | 基于数据报，可能无序、丢失             |
| 效率     | 较低，有连接建立和数据确认的开销         | 较高，没有连接建立和数据确认的开销     |
| 应用场景 | 需要可靠传输的应用，如文件传输、网页浏览 | 需要高效传输的应用，如视频流、在线游戏 |

### 五、总结

本节课我们学习了 TCP 和 UDP 两种网络协议，并使用 C++ 实现了简单的 TCP 和 UDP 服务器和客户端程序。在实际应用中，我们需要根据具体的应用场景选择合适的网络协议。