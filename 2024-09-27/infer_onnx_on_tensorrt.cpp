#include <iostream>
#include <fstream>
#include <NvInfer.h>  // TensorRT 核心头文件
#include <NvOnnxParser.h>  // 用于解析 ONNX 模型的头文件
#include <opencv2/opencv.hpp>  // OpenCV 头文件，用于图像处理
#include <cuda_runtime_api.h>  // CUDA 运行时 API，用于管理 GPU 内存
#include <vector>
#include <algorithm>  // 用于排序结果

using namespace nvinfer1;  // TensorRT 命名空间
using namespace nvonnxparser;  // ONNX 解析器命名空间

// TensorRT 日志记录器，用于记录推理过程中的日志信息
class Logger : public ILogger {
public:
    // 实现 ILogger 接口中的 log 方法
    void log(Severity severity, const char* msg) noexcept override {
        // 忽略 INFO 级别的消息，只打印 WARNING 及以上级别的消息
        if (severity != Severity::kINFO) {
            std::cout << msg << std::endl;
        }
    }
};

// 读取并预处理图像
std::vector<float> getImage(const std::string& path) {
    cv::Mat image = cv::imread(path);  // 读取图像
    cv::resize(image, image, cv::Size(224, 224));  // 调整图像大小为 224x224
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);  // 将图像从 BGR 转换为 RGB
    image.convertTo(image, CV_32F, 1.0 / 255);  // 将像素值归一化到 [0, 1]

    // 使用 ImageNet 模型的均值和标准差进行归一化
    cv::Scalar mean(0.485, 0.456, 0.406);  // ImageNet 均值
    cv::Scalar std(0.229, 0.224, 0.225);  // ImageNet 标准差

    // 减去均值并除以标准差进行归一化操作
    cv::subtract(image, mean, image);
    cv::divide(image, std, image);

    // 将图像转换为 NCHW 格式的张量，TensorRT 需要这种格式
    std::vector<float> input_tensor_values(1 * 3 * 224 * 224);  // 创建一个大小为 1x3x224x224 的数组，用于存储图像数据
    for (int c = 0; c < 3; ++c)  // 遍历每个通道（RGB）
        for (int h = 0; h < 224; ++h)  // 遍历每个像素的高度
            for (int w = 0; w < 224; ++w)  // 遍历每个像素的宽度
                input_tensor_values[c * 224 * 224 + h * 224 + w] = image.at<cv::Vec3f>(h, w)[c];  // 将图像数据填充到数组中

    return input_tensor_values;  // 返回处理后的图像数据
}

int main() {
    Logger logger;  // 创建 TensorRT 日志记录器

    // 创建 TensorRT builder，用于构建推理引擎
    IBuilder* builder = createInferBuilder(logger);
    // 创建 BuilderConfig，用于设置推理引擎的配置，例如工作空间大小等
    IBuilderConfig* config = builder->createBuilderConfig();
    // 创建网络定义，显式设置 batch 尺寸（1U << 0 表示显式批次模式）
    const auto explicitBatch = 1U << static_cast<uint32_t>(NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
    INetworkDefinition* network = builder->createNetworkV2(explicitBatch);

    // 创建 ONNX 模型解析器
    IParser* parser = createParser(*network, logger);
    // 解析 ONNX 模型文件
    if (!parser->parseFromFile("resnet50_imagenet1.onnx", static_cast<int>(ILogger::Severity::kWARNING))) {
        std::cerr << "Failed to parse ONNX model." << std::endl;  // 如果解析失败，输出错误信息
        return -1;  // 退出程序
    }

    // 设置最大工作空间的大小为 1GB，用于推理时的内存分配
    config->setMaxWorkspaceSize(1 << 30);  // 1GB
    // 如果硬件支持 FP16 精度，则启用 FP16 推理模式
    if (builder->platformHasFastFp16()) {
        config->setFlag(BuilderFlag::kFP16);
    }

    // 使用配置好的网络和配置创建推理引擎
    ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    if (!engine) {
        std::cerr << "Failed to create TensorRT engine." << std::endl;  // 如果引擎创建失败，输出错误信息
        return -1;  // 退出程序
    }

    // 使用引擎创建执行上下文（ExecutionContext），用于运行推理
    IExecutionContext* context = engine->createExecutionContext();

    // 获取输入和输出的索引（根据名称查找）
    int inputIndex = engine->getBindingIndex("input");
    int outputIndex = engine->getBindingIndex("output");

    // 获取输入和输出的维度信息
    Dims inputDims = engine->getBindingDimensions(inputIndex);  // 输入尺寸 (1, 3, 224, 224)
    Dims outputDims = engine->getBindingDimensions(outputIndex);  // 输出尺寸 (1, 1000)

    // 准备输入数据，调用之前定义的 getImage 函数读取并预处理图像
    std::vector<float> input_tensor_values = getImage("cat.jpg");

    // 分配 GPU 内存，用于存储输入和输出数据
    void* buffers[2];  // 创建输入和输出缓冲区指针
    cudaMalloc(&buffers[inputIndex], input_tensor_values.size() * sizeof(float));  // 为输入分配 GPU 内存
    cudaMalloc(&buffers[outputIndex], outputDims.d[1] * sizeof(float));  // 为输出分配 GPU 内存，outputDims.d[1] == 1000

    // 将输入数据从主机内存复制到 GPU 内存中
    cudaMemcpy(buffers[inputIndex], input_tensor_values.data(), input_tensor_values.size() * sizeof(float), cudaMemcpyHostToDevice);

    // 执行推理，将输入数据传递给 TensorRT 引擎
    context->enqueueV2(buffers, 0, nullptr);

    // 从 GPU 获取推理输出，将数据从 GPU 内存复制到主机内存
    std::vector<float> output_tensor_values(outputDims.d[1]);  // 创建一个大小为 1000 的数组用于存储输出
    cudaMemcpy(output_tensor_values.data(), buffers[outputIndex], outputDims.d[1] * sizeof(float), cudaMemcpyDeviceToHost);

    // 释放 GPU 内存
    cudaFree(buffers[inputIndex]);
    cudaFree(buffers[outputIndex]);

    // 读取 ImageNet 标签文件
    std::ifstream label_file("imagenet_class.txt");
    std::vector<std::string> labels;
    std::string line;
    while (std::getline(label_file, line)) {
        labels.push_back(line);  // 将每一行的标签存入 labels 向量中
    }

    // 将输出结果与索引配对存储
    std::vector<std::pair<float, int>> results;
    for (int i = 0; i < outputDims.d[1]; ++i) {  // 遍历输出结果
        results.emplace_back(output_tensor_values[i], i);  // 存储预测概率和对应的类别索引
    }
    // 根据预测概率进行排序，从高到低
    std::sort(results.begin(), results.end(), std::greater<>());

    // 输出 top-3 预测结果
    for (int i = 0; i < 3; ++i) {
        std::cout << "Label: " << labels[results[i].second] << ", Probability: " << results[i].first << std::endl;
    }

    // 清理资源，销毁上下文、引擎、网络、解析器和 builder
    context->destroy();
    engine->destroy();
    network->destroy();
    parser->destroy();
    builder->destroy();
    config->destroy();

    return 0;
}