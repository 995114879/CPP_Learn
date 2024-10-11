## C++ OpenCV 开发环境搭建 (Ubuntu Linux) - 第 31 节

### 课程目标

* 了解 OpenCV 库及其功能
* 掌握在 Ubuntu Linux 系统下搭建 OpenCV C++ 开发环境的方法
* 能够编写简单的 OpenCV C++ 程序并运行

### OpenCV 简介

OpenCV (Open Source Computer Vision Library) 是一个开源的计算机视觉库，它提供了丰富的图像处理和计算机视觉算法，广泛应用于图像识别、目标检测、视频分析等领域。

**OpenCV 的主要功能:**

* 图像读取、显示和保存
* 图像处理 (滤波、边缘检测、形态学操作等)
* 特征提取和匹配
* 目标检测和跟踪
* 机器学习 (分类、回归等)

### 开发环境搭建

**0. 为什么要从源码安装 opencv**
1. 获得最新版本和功能:

​		OpenCV 的官方发布周期相对较长，而源码库通常包含最新的 bug 修复、性能改进和新功能。如果您需要使用最		新特性或修复特定 bug，从源码安装是最佳选择。
​		您可以选择安装特定版本的 OpenCV，甚至可以安装特定的 git commit，这在包管理器中通常无法实现。

2. 自定义编译选项:

​		从源码安装允许您根据自己的需求定制编译选项，例如：
​		启用/禁用特定模块: 您可以选择只编译您需要的模块，从而减小库的大小和依赖项。
​		优化性能: 您可以针对您的特定硬件平台和编译器进行性能优化，例如启用 SIMD 指令集（SSE, AVX 等）或使用		特定的优化级别。
​		使用第三方库: 您可以选择启用对其他第三方库的支持，例如 CUDA、OpenCL、TBB 等，从而提高 OpenCV 的性		能和功能。
​		通过自定义编译选项，您可以获得更小、更快、更适合您需求的 OpenCV 库。

3. 更好的控制和理解:

​		从源码安装可以让您深入了解 OpenCV 的构建过程和依赖关系，这有助于您更好地理解库的运作方式，并更容易		进行调试和故障排除。
​		您可以更好地控制安装位置和库的配置，这在某些情况下非常重要，例如在嵌入式系统或需要多个 OpenCV 版本		共存的环境中。

4. 避免兼容性问题:

​		包管理器提供的 OpenCV 版本可能与您的操作系统或其他软件库不兼容。从源码安装可以让您根据自己的环境选		择合适的依赖项和编译选项，从而避免潜在的兼容性问题。
5. 许可和合规性：
** LICENSE符合**：确保符合特定项目或组织的许可政策。
确保法规合规：在包含专有组件时，自行确保合规性。
6. 可重复性和可靠性：
确定的构建过程：确保一致的构建环境和产出。
可重现性：在问题出现时，轻松重建以有效复现和排查。

**1. 安装依赖库:**

在终端中执行以下命令安装 OpenCV 需要的依赖库:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
```

**2. 下载 OpenCV 源码:**

可以选择从 OpenCV 官网下载源码压缩包，或者使用 Git 克隆仓库:

```bash
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```

**3. 编译安装 OpenCV:**

```bash
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D WITH_CUDA=ON \
      -D WITH_CUDNN=ON \
      -D WITH_TBB=ON \
      -D WITH_OPENMP=ON \
      -D WITH_IPP=ON \
      -D WITH_EIGEN=ON \
      -D WITH_GTK=ON \
      -D WITH_V4L=ON \
      -D BUILD_opencv_python3=ON \
      -D BUILD_opencv_python2=OFF \
      -D BUILD_opencv_java=ON \
      -D ENABLE_FAST_MATH=ON \
      -D CUDA_FAST_MATH=ON \
      -D WITH_QT=ON \
      -D WITH_OPENCL=ON \
      -D BUILD_EXAMPLES=ON \
      -D BUILD_TESTS=ON \
      -D BUILD_PERF_TESTS=ON \
      -D INSTALL_C_EXAMPLES=ON \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
      ..
make -j$(nproc)
sudo make install
```

**参数说明:**

* `CMAKE_BUILD_TYPE=RELEASE`:  编译 Release 版本
* `CMAKE_INSTALL_PREFIX=/usr/local`:  安装路径
* `OPENCV_EXTRA_MODULES_PATH`:  opencv_contrib 模块路径
* `WITH_CUDA=OFF`:  禁用 CUDA 支持 (根据需要开启)
* `-j$(nproc)`:  使用多线程编译，加快速度

**4. 配置环境变量:**

将 OpenCV 库路径添加到 `LD_LIBRARY_PATH` 环境变量中:

```bash
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib" >> ~/.bashrc
source ~/.bashrc
```

**5. 验证安装:**

可以使用 `pkg-config` 命令查看 OpenCV 的版本信息:

```bash
pkg-config --modversion opencv4
```

### 编写第一个 OpenCV 程序

**1. 创建 C++ 文件:**

创建一个名为 `hello_opencv.cpp` 的文件，并输入以下代码:

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  // 读取图像
  cv::Mat image = cv::imread("lena.jpg");

  // 检查图像是否加载成功
  if (image.empty()) {
    std::cerr << "无法打开图像文件!" << std::endl;
    return -1;
  }

  // 显示图像
  cv::imshow("Lena", image);
  cv::waitKey(0);

  return 0;
}
```

**2. 编译程序:**

```bash
g++ hello_opencv.cpp -o hello_opencv `pkg-config --cflags --libs opencv4`
```

**3. 运行程序:**

将 `lena.jpg` 图片放到程序所在目录，然后运行程序:

```bash
./hello_opencv
```

程序将显示名为 "Lena" 的窗口，其中显示了 Lena 的图像。

### 总结

本节课我们学习了如何在 Ubuntu Linux 系统下搭建 OpenCV C++ 开发环境，并编写了一个简单的程序来读取和显示图像。在接下来的课程中，我们将学习更多 OpenCV 的功能和应用。


### 课后作业

* 完成本地开发环境的配置
* 编译通过课堂的示例代码


### 参考资料

* OpenCV 官方网站: https://opencv.org/
* OpenCV 官方文档: https://docs.opencv.org/