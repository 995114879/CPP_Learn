### 1. 安装依赖项
首先，确保系统更新并安装构建 ONNX Runtime 所需的依赖项。

```bash
sudo apt update
sudo apt install -y git build-essential python3 python3-pip python3-setuptools python3-dev libprotobuf-dev protobuf-compiler libcurl4-openssl-dev libssl-dev autoconf automake libtool curl make cmake unzip pkg-config
```

### 2. 克隆 ONNX Runtime 源代码
从官方 GitHub 仓库克隆 ONNX Runtime 源代码。

```bash
git clone https://github.com/microsoft/onnxruntime
cd onnxruntime
git submodule update --init --recursive
```

### 3. 安装 Python 构建工具
ONNX Runtime 使用 Python 构建系统来生成必要的编译配置，因此需要安装 `onnxruntime` 的 Python 构建工具。

```bash
pip3 install --upgrade pip setuptools wheel
pip3 install -r requirements.txt
```

### 4. 构建 ONNX Runtime C++ 静态库/共享库

ONNX Runtime 使用 Python 脚本进行构建，而不是直接使用 `cmake`。你可以使用以下命令来编译 ONNX Runtime。

#### 编译共享库或静态库（默认共享库）

```bash
./build.sh --config Release --build_shared_lib
```

这里 `--config Release` 选项是构建优化后的 `Release` 版本，`--build_shared_lib` 选项用于构建共享库。如果不需要共享库，可以去掉这个选项，来生成静态库。

### 5. 安装 ONNX Runtime C++ 库

编译完成后，使用以下命令安装 ONNX Runtime C++ 库：

```bash
sudo cp -r build/Linux/Release/* /usr/local/lib/
sudo cp -r include/* /usr/local/include/
```

这样，ONNX Runtime 的库文件将会安装到 `/usr/local/lib`，头文件安装到 `/usr/local/include`，可以在你的 C++ 项目中使用这些库和头文件。

### 6. 使用 ONNX Runtime C++ 进行推理
你现在可以使用安装好的 ONNX Runtime 库进行 C++ 项目的开发。这里是一个简单的 C++ 示例代码来加载并运行 ONNX 模型：

```cpp
#include <onnxruntime/core/session/onnxruntime_cxx_api.h>
#include <iostream>

int main() {
    // 创建 ORT 环境
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNXRuntimeTest");

    // 设置会话选项
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

    // 加载 ONNX 模型
    const char* model_path = "your_model.onnx";
    Ort::Session session(env, model_path, session_options);

    // 打印模型输入信息
    size_t num_input_nodes = session.GetInputCount();
    std::cout << "Number of input nodes: " << num_input_nodes << std::endl;

    return 0;
}
```

### 7. 编译并运行你的 C++ 应用程序

```bash
g++ -std=c++17 simple_model_infer.cpp -I/usr/local/include -L/usr/local/lib -lonnxruntime -o simple_model_infer
```

### 8. 运行生成的可执行文件

```bash
./simple_model_infer
```