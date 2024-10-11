# CUDA 编程入门课件

## 1. CUDA 简介

CUDA (Compute Unified Device Architecture) 是一种由 NVIDIA 提供的并行计算架构，允许开发者使用 GPU 来加速计算密集型任务。

### 1.1 CPU 和 GPU 的区别
- **CPU**：通用处理器，擅长处理复杂的、顺序执行的任务。
- **GPU**：专为数据并行任务设计，擅长处理大量的并行计算。

### 1.2 GPU 编程模型
CUDA 让我们能够使用 C++ 语言扩展编写代码，调用 GPU 来执行并行计算。CUDA 中的代码可以分为两部分：
- **Host 代码**：在 CPU 上执行的代码。(CPU)
- **Device 代码**：在 GPU 上执行的代码。(GPU)

---

## 2. CUDA 编程基础

### 2.1 编写第一个 CUDA 程序

我们从一个简单的向量加法程序开始。在这个例子中，我们将两个向量加在一起，并使用 GPU 进行计算。

### 代码示例：向量加法

```cpp
#include <iostream>
#include <cuda_runtime.h>

const int N = 512;  // 定义数组大小为 512 

// CUDA 内核函数：用于在 GPU 上执行的代码
__global__ void vectorAdd(int* a, int* b, int* c) {
    int index = threadIdx.x;  // 获取每个线程的索引
    c[index] = a[index] + b[index];  // 执行向量加法
}

int main() {
    int a[N], b[N], c[N];  // 在 Host (CPU) 上定义三个数组
    int *d_a, *d_b, *d_c;  // 定义指向 Device (GPU) 上数据的指针

    // 在 GPU 上分配内存
    cudaMalloc((void**)&d_a, N * sizeof(int));  // 分配 a 数组的内存
    cudaMalloc((void**)&d_b, N * sizeof(int));  // 分配 b 数组的内存
    cudaMalloc((void**)&d_c, N * sizeof(int));  // 分配 c 数组的内存

    // 初始化 Host 上的数组
    for (int i = 0; i < N; i++) {
        a[i] = i;  // 初始化 a 数组
        b[i] = i * 2;  // 初始化 b 数组
    }

    // 将数据从 Host 复制到 Device
    cudaMemcpy(d_a, a, N * sizeof(int), cudaMemcpyHostToDevice);  // 复制 a 数组到 GPU
    cudaMemcpy(d_b, b, N * sizeof(int), cudaMemcpyHostToDevice);  // 复制 b 数组到 GPU

    // 启动 CUDA 内核，每个线程处理一个数组元素
    vectorAdd<<<1, N>>>(d_a, d_b, d_c);

    // 将结果从 Device 复制回 Host
    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);

    // 输出结果
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << " + " << b[i] << " = " << c[i] << std::endl;
    }

    // 释放 GPU 上的内存
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
```

### 代码讲解：
- `__global__` 是一个 CUDA 关键字，用于声明在 GPU 上运行的函数。
- `threadIdx.x` 是 CUDA 提供的内置变量，用于标识当前线程的索引。
- `cudaMalloc` 用于在 GPU 上分配内存。
- `cudaMemcpy` 用于在 Host 和 Device 之间复制数据。
- `<<<1, N>>>` 是 CUDA 内核启动的语法，其中 `1` 是 block 的数量，`N` 是每个 block 中的线程数量。

---

## 3. CUDA 并行编程模型

CUDA 编程模型基于线程的并行执行。CUDA 将线程组织成 **网格 (Grid)** 和 **块 (Block)** 的层次结构。

### 3.1 线程和块
- **线程 (Thread)**：CUDA 中的最小执行单元。
- **块 (Block)**：线程的集合，通常由 1D、2D 或 3D 组织。
- **网格 (Grid)**：块的集合。

### 3.2 线程索引

每个线程可以通过 `blockIdx` 和 `threadIdx` 来获取其在网格中的位置。以下是一个使用 2D 索引的示例。

### 代码示例：2D 索引的矩阵加法

```cpp
#include <iostream>
#include <cuda_runtime.h>

const int N = 16;  // 定义矩阵大小为 16x16

// CUDA 内核函数：用于在 GPU 上执行的代码
__global__ void matrixAdd(int* a, int* b, int* c, int width) {
    int col = threadIdx.x + blockIdx.x * blockDim.x;  // 计算当前线程对应的列索引
    int row = threadIdx.y + blockIdx.y * blockDim.y;  // 计算当前线程对应的行索引

    int idx = row * width + col;  // 将 2D 索引转换为 1D 索引
    if (col < width && row < width) {  // 确保索引在矩阵范围内
        c[idx] = a[idx] + b[idx];  // 执行矩阵加法
    }
}

int main() {
    int a[N * N], b[N * N], c[N * N];  // 在 Host (CPU) 上定义三个矩阵
    int *d_a, *d_b, *d_c;  // 定义指向 Device (GPU) 上数据的指针

    // 在 GPU 上分配内存
    cudaMalloc((void**)&d_a, N * N * sizeof(int));  // 分配 a 矩阵的内存
    cudaMalloc((void**)&d_b, N * N * sizeof(int));  // 分配 b 矩阵的内存
    cudaMalloc((void**)&d_c, N * N * sizeof(int));  // 分配 c 矩阵的内存

    // 初始化 Host 上的矩阵
    for (int i = 0; i < N * N; i++) {
        a[i] = i;  // 初始化 a 矩阵
        b[i] = i * 2;  // 初始化 b 矩阵
    }

    // 将数据从 Host 复制到 Device
    cudaMemcpy(d_a, a, N * N * sizeof(int), cudaMemcpyHostToDevice);  // 复制 a 矩阵到 GPU
    cudaMemcpy(d_b, b, N * N * sizeof(int), cudaMemcpyHostToDevice);  // 复制 b 矩阵到 GPU

    // 定义线程块和网格的维度
    dim3 threadsPerBlock(4, 4);  // 每个块有 4x4 = 16 个线程
    dim3 numBlocks(N / threadsPerBlock.x, N / threadsPerBlock.y);  // 总共 4x4 = 16 个块

    // 启动 CUDA 内核
    matrixAdd<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, N);

    // 将结果从 Device 复制回 Host
    cudaMemcpy(c, d_c, N * N * sizeof(int), cudaMemcpyDeviceToHost);

    // 输出结果
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << c[i * N + j] << " ";
        }
        std::cout << std::endl;
    }

    // 释放 GPU 上的内存
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
```

### 代码讲解：
- `dim3` 是 CUDA 用来定义 3D 维度的结构体。
- `blockIdx` 和 `threadIdx` 分别表示当前块和线程的索引。
- 通过 `blockIdx` 和 `threadIdx` 的组合，可以在 2D 网格中找到每个线程的唯一索引。

---

## 4. CUDA 内存模型

CUDA 中有多种不同的内存类型，每种内存的性能和作用不同。

### 4.1 内存类型
- **全局内存**：所有线程都可以访问，但是访问速度较慢。
- **共享内存**：同一个块中的线程可以共享，访问速度较快。
- **寄存器**：每个线程私有的存储，访问速度最快。

### 代码示例：使用共享内存进行向量加法

```cpp
#include <iostream>
#include <cuda_runtime.h>

const int N = 512;  // 定义数组大小为 512

// CUDA 内核函数：用于在 GPU 上执行的代码
__global__ void vectorAddShared(int* a, int* b, int* c) {
    __shared__ int shared_a[N];  // 在共享内存中声明 a 数组
    __shared__ int shared_b[N];  // 在共享内存中声明 b 数组

    int index = threadIdx.x;  // 获取每个线程的索引

    // 将全局内存中的数据复制到共享内存
    shared_a[index] = a[index];
    shared_b[index] = b[index];

    __syncthreads();  // 保证所有线程都完成了数据复制

    // 执行向量加法
    c[index] = shared_a[index] + shared_b[index];
}

int main() {
    int a[N], b[N], c[N];  // 在 Host (CPU) 上定义三个数组
    int *d_a, *d_b, *d_c;  // 定义指向 Device (GPU) 上数据的指针

    // 在 GPU 上分配内存
    cudaMalloc((void**)&d_a, N * sizeof(int));  // 分配 a 数组的内存
    cudaMalloc((void**)&d_b, N * sizeof(int));  // 分配 b 数组的内存
    cudaMalloc((void**)&d_c, N * sizeof(int));  // 分配 c 数组的内存

    // 初始化 Host 上的数组
    for (int i = 0; i < N; i++) {
        a[i] = i;  // 初始化 a 数组
        b[i] = i * 2;  // 初始化 b 数组
    }

    // 将数据从 Host 复制到 Device
    cudaMemcpy(d_a, a, N * sizeof(int), cudaMemcpyHostToDevice);  // 复制 a 数组到 GPU
    cudaMemcpy(d_b, b, N * sizeof(int), cudaMemcpyHostToDevice);  // 复制 b 数组到 GPU

    // 启动 CUDA 内核
    vectorAddShared<<<1, N>>>(d_a, d_b, d_c);

    // 将结果从 Device 复制回 Host
    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);

    // 输出结果
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << " + " << b[i] << " = " << c[i] << std::endl;
    }

    // 释放 GPU 上的内存
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
```

### 代码讲解：
- `__shared__` 关键字用于声明共享内存。
- `__syncthreads()` 用于同步块中的所有线程，确保所有线程都完成共享内存的加载。

---

## 5. CUDA 编译器和工具

### 5.1 NVCC 编译器

NVCC 是 NVIDIA CUDA Compiler 的缩写，是 CUDA 程序的编译器。它将 CUDA 代码 (包含 Host 代码和 Device 代码) 编译成可在 GPU 上运行的可执行文件。

**使用方法：**



```bash
nvcc [options] source_file.cu -o executable_file
```

**常用选项：**

- `-o`: 指定输出文件名。
- `-arch`: 指定目标 GPU 架构。
- `-I`: 指定头文件路径。
- `-g`: 生成调试信息。
- `-ptx`: 生成 PTX 代码 (一种中间代码)。

### 5.2 CUDA Toolkit

CUDA Toolkit 是 NVIDIA 提供的 CUDA 开发工具包，包含 NVCC 编译器、CUDA 运行时库、CUDA 调试工具等。

**下载地址：** https://developer.nvidia.com/cuda-toolkit

**安装完成后，需要设置环境变量：**

- `PATH`: 添加 NVCC 编译器的路径。
- `LD_LIBRARY_PATH`: 添加 CUDA 运行时库的路径。

### 5.3 CUDA Profiler

CUDA Profiler 是 NVIDIA 提供的性能分析工具，可以帮助开发者分析 CUDA 程序的性能瓶颈。

**使用方法：**



```bash
nvprof ./executable_file
```

CUDA Profiler 会收集程序运行时的各种信息，例如内核执行时间、内存访问次数等，并生成可视化的报告。

### 5.4 CUDA Debugger (cuda-gdb)

cuda-gdb 是 NVIDIA 提供的 CUDA 调试工具，可以帮助开发者调试 CUDA 程序。

**使用方法：**



```bash
cuda-gdb ./executable_file
```

**cuda-gdb 支持常用的调试命令，例如：**

- `break`: 设置断点。
- `run`: 运行程序。
- `step`: 单步执行。
- `print`: 打印变量值。

## 真实案例
普通的 C++代码
```c++
   // 转换为 NCHW 格式 (1, 3, 224, 224)
    std::vector<float> input_tensor_values(1 * 3 * 224 * 224);  // 包含 batch size 维度
    for (int c = 0; c < 3; ++c)
        for (int h = 0; h < 224; ++h)
            for (int w = 0; w < 224; ++w)
                input_tensor_values[c * 224 * 224 + h * 224 + w] = image.at<cv::Vec3f>(h, w)[c];
```
相应的 cuda 实现
```c++
6. #include <iostream>
   #include <vector>
   #include <opencv2/opencv.hpp>
   #include <cuda_runtime.h>

   __global__ void convert_image_to_tensor(const cv::Vec3f* image, float* tensor, int width, int height) {
       int c = blockIdx.x;
       int h = threadIdx.y;
       int w = threadIdx.x;

       if (c < 3 && h < height && w < width) {
           tensor[c * width * height + h * width + w] = image[h * width + w][c];
       }
   }

   int main() {
       // 读取图像
       cv::Mat image = cv::imread("image.jpg", cv::IMREAD_COLOR);
       image.convertTo(image, CV_32FC3); // 转换为 float 格式

       // 检查图像是否为空
       if (image.empty()) {
           std::cerr << "无法读取图像！" << std::endl;
           return -1;
       }
       
       // 获取图像尺寸
       int width = image.cols;
       int height = image.rows;
       
       // 在 Host 上分配内存
       std::vector<float> input_tensor_values(1 * 3 * height * width);
       cv::Vec3f* h_image = (cv::Vec3f*)image.data;
       float* h_tensor = input_tensor_values.data();
       
       // 在 Device 上分配内存
       cv::Vec3f* d_image;
       float* d_tensor;
       cudaMalloc((void**)&d_image, height * width * sizeof(cv::Vec3f));
       cudaMalloc((void**)&d_tensor, 1 * 3 * height * width * sizeof(float));
       
       // 将数据从 Host 复制到 Device
       cudaMemcpy(d_image, h_image, height * width * sizeof(cv::Vec3f), cudaMemcpyHostToDevice);
       
       // 定义线程块和网格的维度
       dim3 threadsPerBlock(width, height);
       dim3 numBlocks(3);
       
       // 启动 CUDA 内核
       convert_image_to_tensor<<<numBlocks, threadsPerBlock>>>(d_image, d_tensor, width, height);
       
       // 将结果从 Device 复制回 Host
       cudaMemcpy(h_tensor, d_tensor, 1 * 3 * height * width * sizeof(float), cudaMemcpyDeviceToHost);
       
       // 释放 GPU 上的内存
       cudaFree(d_image);
       cudaFree(d_tensor);
       
       // 打印转换后的张量 (可选)
       // for (int i = 0; i < 1 * 3 * height * width; ++i) {
       //     std::cout << input_tensor_values[i] << " ";
       // }
       // std::cout << std::endl;
       
       return 0;
   }
```
## 7. 总结

- CUDA 编程模型让我们可以轻松实现并行计算。
- 关键的 CUDA 概念包括：线程、块和网格，以及不同类型的内存 (全局内存、共享内存、寄存器)。
- 通过理解内核函数的执行方式和内存模型，可以写出高效的 CUDA 程序。
- NVCC 编译器和 CUDA Toolkit 是 CUDA 开发的必备工具。
- CUDA Profiler 和 cuda-gdb 可以帮助开发者分析和调试 CUDA 程序。

------

**参考文献**：

- NVIDIA官方文档: https://docs.nvidia.com/cuda/

---

**课后作业**：
1. 阅读课件上的这两份代码，理解其中并行编程的思想, 再去cuda 官网上面看看相关资料。

