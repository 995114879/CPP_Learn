# TensorRT 课件大纲

## 主题：**TensorRT 简介及其与 CUDA 的关系**

### 1. 课程目标
- 了解 TensorRT 的基本概念和使用场景。
- 掌握 TensorRT 与 CUDA 的关系及其优势。
- 初步掌握基于 TensorRT 的深度学习模型推理流程。

---

### 2. TensorRT 是什么？
TensorRT 是 NVIDIA 推出的一个高性能深度学习推理库，专为优化神经网络的推理速度和效率设计。它支持从 ONNX、TensorFlow、PyTorch 等框架导出的模型，并在 GPU 上运行高效的推理。

**核心特点：**
- **高效推理**：针对 NVIDIA GPU 优化，能大幅提升推理速度。
- **支持多种精度**：支持 FP32、FP16、INT8 等多种精度推理。
- **跨平台支持**：支持 NVIDIA Jetson、数据中心 GPU 等多个平台。

---

### 3. TensorRT 的使用场景
- **深度学习模型优化**：将训练好的模型导入 TensorRT，进行推理加速。
- **实时推理**：适用于需要快速响应的应用，如自驾车、实时图像处理等。
- **边缘计算**：在资源受限的设备上（如 Jetson）进行高效推理。

---

### 4. TensorRT 主要组件
1. **Builder**：构建推理引擎。负责解析模型（如 ONNX 模型）、配置优化策略（如选择 FP16 或 INT8 精度）等。
2. **Engine**：推理引擎，是经过优化和编译后的模型，能直接加载在 GPU 上执行推理。
3. **ExecutionContext**：执行推理时的上下文环境，负责管理输入输出缓冲区，并调度推理过程。

---

### 5. TensorRT 与 CUDA 的关系

#### 5.1 CUDA 简介
**CUDA** 是 NVIDIA 推出的并行计算平台和编程模型，它允许开发者利用 GPU 的计算能力进行高效的并行计算。

**CUDA 核心功能：**
- **并行计算**：通过大量线程在 GPU 上同时运行任务，显著提高计算效率。
- **内存管理**：提供主机和设备（GPU）之间的数据传输机制。
- **高效计算库**：CUDA 提供了丰富的数学库（如 cuBLAS、cuDNN 等），帮助开发者轻松使用 GPU 进行计算。

#### 5.2 TensorRT 如何利用 CUDA
TensorRT 是基于 CUDA 构建的，主要通过 CUDA 提供的底层计算能力进行高效推理。以下是 TensorRT 与 CUDA 的关键联系：

1. **CUDA 核函数**：TensorRT 使用 CUDA 核函数来加速张量操作，如矩阵乘法、卷积等。通过大量的并行线程来提升推理速度。
   
2. **cuDNN 集成**：TensorRT 深度集成了 NVIDIA 的 cuDNN 库。cuDNN 是 CUDA 的一个深度学习加速库，它为卷积、池化、激活等操作提供了高度优化的实现。

3. **内存管理**：TensorRT 使用 CUDA 的内存管理 API（如 `cudaMalloc`、`cudaMemcpy`）在 GPU 上分配和传输数据。它高效管理输入输出张量的分配和释放。

4. **多精度支持**：TensorRT 支持 CUDA 的多种计算精度，包括 FP32、FP16 和 INT8。通过 CUDA 的计算能力，TensorRT 可以在不同精度之间进行权衡，提升推理速度的同时保持准确性。

5. **异步执行**：TensorRT 支持 CUDA 的流（Stream）机制，允许异步执行推理任务。这使得推理过程不阻塞 CPU，可以高效处理多个推理请求。

#### 5.3 TensorRT 和 CUDA 的协同工作

- **TensorRT 管理性能优化**：TensorRT 通过分析模型的计算图，选择最优的 CUDA 内核以加速推理任务。它会根据硬件支持情况选择合适的精度（如 FP16 或 INT8），并使用 CUDA 的并行能力来执行优化后的计算。
  
- **CUDA 提供底层计算支持**：TensorRT 所有的计算操作都会映射到 CUDA 核函数中执行。这种映射使得 TensorRT 的每个操作都能充分发挥 GPU 的并行计算能力。

---

### 6. TensorRT 工作流程

1. **加载模型**：从 ONNX 文件中加载训练好的模型，或从 TensorFlow、PyTorch 等框架导出的模型。
2. **创建推理引擎**：使用 TensorRT Builder 解析模型，进行优化（如精度选择、层融合等），并生成推理引擎。
3. **分配 GPU 内存**：通过 CUDA API 分配 GPU 内存，准备好输入和输出缓冲区。
4. **执行推理**：将输入数据传输到 GPU 上，使用 TensorRT 的 ExecutionContext 调用推理引擎，执行推理任务。
5. **获取结果**：将推理结果从 GPU 复制回主机内存，进行后续处理。

---

### 7. TensorRT 优化策略

1. **精度选择**：
   - **FP32**：默认的单精度浮点数，精度高，但速度较慢。
   - **FP16**：半精度浮点数，速度更快，但可能会有一定的精度损失。
   - **INT8**：整数精度，推理速度最快，但需要使用校准数据进行量化。

2. **层融合**：TensorRT 可以自动将多个层（如卷积+激活）融合为一个 CUDA 核函数，减少内存访问开销。

3. **动态张量**：TensorRT 支持动态批次大小和输入尺寸，可以根据实际推理需求动态调整推理过程。

4. **缓存机制**：TensorRT 会缓存优化后的内核和内存布局，在后续推理时加速执行。

---

### 8. TensorRT 示例代码

#### 示例：使用 TensorRT 加载 ONNX 模型并进行推理

```cpp
#include <NvInfer.h>
#include <NvOnnxParser.h>
#include <cuda_runtime_api.h>
#include <iostream>

int main() {
    // 创建 TensorRT builder
    nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(logger);
    nvinfer1::INetworkDefinition* network = builder->createNetworkV2(0U);
    
    // 解析 ONNX 模型
    nvonnxparser::IParser* parser = nvonnxparser::createParser(*network, logger);
    parser->parseFromFile("model.onnx", static_cast<int>(ILogger::Severity::kWARNING));

    // 构建推理引擎
    nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();
    nvinfer1::ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);

    // 创建执行上下文
    nvinfer1::IExecutionContext* context = engine->createExecutionContext();

    // 准备输入输出缓冲区，执行推理
    void* buffers[2];
    cudaMalloc(&buffers[0], input_size * sizeof(float));
    cudaMalloc(&buffers[1], output_size * sizeof(float));

    // 推理
    context->enqueueV2(buffers, 0, nullptr);

    // 清理资源
    cudaFree(buffers[0]);
    cudaFree(buffers[1]);
    context->destroy();
    engine->destroy();
    network->destroy();
    builder->destroy();
    parser->destroy();

    return 0;
}
```

---

### 9. 总结
- TensorRT 是针对 NVIDIA GPU 优化的深度学习推理库，基于 CUDA 构建，能够大幅提升推理速度和效率。
- CUDA 提供了 TensorRT 所需的底层并行计算、内存管理和硬件优化支持。
- TensorRT 通过精度优化、层融合和内存管理来最大化利用 GPU 资源，是高效的推理解决方案。

---

### 10. 课后作业
1. 下载并安装 TensorRT 和 CUDA，尝试运行一个简单的 ONNX 模型推理。
2. 探索 TensorRT 支持的不同精度模式（FP32、FP16、INT8），并比较它们的推理速度和准确性。

---

**附录：参考资料**
- [NVIDIA CUDA 官方文档](https://docs.nvidia.com/cuda/)
- [NVIDIA TensorRT 官方文档

