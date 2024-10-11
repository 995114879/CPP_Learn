## C++ 培训 - 第 29 课：Docker 和 Dockerfile

**课程目标:**

* 了解 Docker 的基本概念和优势
* 掌握 Docker 镜像和容器的操作
* 学习 Dockerfile 的语法和构建镜像

**课程内容:**

### 1. Docker 简介

**1.1 什么是 Docker?**

Docker 是一个开源的应用容器引擎，可以让开发者打包他们的应用以及依赖包到一个可移植的镜像中，然后发布到任何流行的 Linux 或 Windows 机器上，也可以实现虚拟化。

**1.2 Docker 的优势:**

* **轻量级:** Docker 容器共享操作系统内核，比虚拟机更轻量级，占用资源更少。
* **可移植性:** Docker 镜像可以在任何支持 Docker 的平台上运行，实现一次构建，随处运行。
* **隔离性:** Docker 容器之间相互隔离，不会互相影响。
* **可扩展性:** 可以轻松地创建和管理大量的 Docker 容器。

**1.3 Docker 的架构:**

Docker 使用客户端-服务器架构。Docker 客户端与 Docker 守护进程通信，后者负责构建、运行和分发 Docker 容器。

**1.4 Docker 的基本概念:**

* **镜像 (Image):** Docker 镜像是一个只读模板，包含创建 Docker 容器的说明。
* **容器 (Container):** Docker 容器是由 Docker 镜像创建的运行实例。
* **Docker Hub:** Docker Hub 是一个公共的 Docker 镜像仓库，可以存储和分享 Docker 镜像。

### 2. Docker 命令行操作

**2.1 安装 Docker:**

```bash
# Ubuntu
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io

# CentOS
sudo yum install docker-ce docker-ce-cli containerd.io
```

**2.2 运行 Hello World 容器:**

```bash
docker run hello-world
```

**2.3 搜索 Docker 镜像:**

```bash
docker search ubuntu
```

**2.4 下载 Docker 镜像:**

```bash
docker pull ubuntu:latest
```

**2.5 列出本地镜像:**

```bash
docker images
```

**2.6 创建并运行容器:**

```bash
docker run -it ubuntu:latest bash
```

**2.7 停止容器:**

```bash
docker stop <container_id>
```

**2.8 删除容器:**

```bash
docker rm <container_id>
```

### 3. Dockerfile

**3.1 什么是 Dockerfile?**

Dockerfile 是一个文本文件，包含构建 Docker 镜像的所有指令。

**3.2 Dockerfile 指令:**

* **FROM:** 指定基础镜像
* **MAINTAINER:** 指定镜像维护者
* **RUN:** 执行命令
* **COPY:** 复制文件或目录
* **ADD:** 复制文件或目录，并可以解压缩
* **EXPOSE:** 暴露端口
* **ENV:** 设置环境变量
* **CMD:** 指定容器启动时执行的命令
* **ENTRYPOINT:** 指定容器的入口点
* **WORKDIR:** 设置工作目录
* **VOLUME:** 定义匿名卷

**3.3 Dockerfile 示例:**

```dockerfile
# 使用 Ubuntu 作为基础镜像
FROM ubuntu:latest

# 设置维护者信息
MAINTAINER Your Name <your.email@example.com>

# 更新软件包列表并安装 C++ 编译器
RUN apt-get update && apt-get install -y build-essential

# 设置工作目录
WORKDIR /app

# 复制源代码到容器
COPY . /app

# 编译 C++ 代码
RUN g++ main.cpp -o main

# 暴露程序运行的端口
EXPOSE 8080

# 设置容器启动时执行的命令
CMD ["./main"]
```

**3.4 构建 Docker 镜像:**

```bash
docker build -t my-cpp-app .
```

**3.5 运行 Docker 镜像:**

```bash
docker run -p 8080:8080 my-cpp-app
```

## 作业

自己编写一个 dockerfile, 并将其运行起来