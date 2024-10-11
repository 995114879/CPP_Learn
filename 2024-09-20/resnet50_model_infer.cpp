#include <iostream>
#include <fstream>
#include <onnxruntime/core/session/onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

// 读取并处理图片
std::vector<float> getImage(const std::string& path) {
    cv::Mat image = cv::imread(path);
    cv::resize(image, image, cv::Size(224, 224));
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    image.convertTo(image, CV_32F, 1.0 / 255);

    // 均值和标准差 (使用 cv::Scalar)
    cv::Scalar mean(0.485, 0.456, 0.406);
    cv::Scalar std(0.229, 0.224, 0.225);

    // 减去均值并除以标准差
    cv::subtract(image, mean, image);
    cv::divide(image, std, image);

    // 转换为 NCHW 格式 (1, 3, 224, 224)
    std::vector<float> input_tensor_values(1 * 3 * 224 * 224);  // 包含 batch size 维度
    for (int c = 0; c < 3; ++c)
        for (int h = 0; h < 224; ++h)
            for (int w = 0; w < 224; ++w)
                input_tensor_values[c * 224 * 224 + h * 224 + w] = image.at<cv::Vec3f>(h, w)[c];

    return input_tensor_values;
}

int main() {
    // 初始化 ONNX Runtime
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNXResNet");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);

    // 加载 ONNX 模型
    Ort::Session session(env, "resnet50_imagenet1.onnx", session_options);

    // 手动指定输入和输出名称
    const char* input_name = "input";
    const char* output_name = "output";

    // 获取输入输出信息
    auto input_info = session.GetInputTypeInfo(0);
    auto input_tensor_info = input_info.GetTensorTypeAndShapeInfo();
    auto output_info = session.GetOutputTypeInfo(0);
    auto output_tensor_info = output_info.GetTensorTypeAndShapeInfo();
    std::vector<int64_t> input_shape = input_tensor_info.GetShape();
    std::vector<int64_t> output_shape = output_tensor_info.GetShape();

    // 打印输入和输出形状，调试用
    std::cout << "Input shape: ";
    for (auto dim : input_shape) {
        std::cout << dim << " ";
    }
    std::cout << std::endl;

    std::cout << "Output shape: ";
    for (auto dim : output_shape) {
        std::cout << dim << " ";
    }
    std::cout << std::endl;

    // 检查输入形状是否为 (1, 3, 224, 224)
    if (input_shape.size() != 4 || input_shape[0] != 1 || input_shape[1] != 3 || input_shape[2] != 224 || input_shape[3] != 224) {
        std::cerr << "Unexpected input shape. Expected (1, 3, 224, 224), but got ";
        for (auto dim : input_shape) std::cerr << dim << " ";
        std::cerr << std::endl;
        return -1;
    }

    // 准备输入数据
    std::vector<float> input_tensor_values = getImage("cat.jpg");
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_tensor_values.data(), input_tensor_values.size(), input_shape.data(), input_shape.size());

    // 检查输出形状是否为 (1, 1000)
    if (output_shape.size() != 2 || output_shape[0] != 1 || output_shape[1] != 1000) {
        std::cerr << "Unexpected output shape. Expected (1, 1000), but got ";
        for (auto dim : output_shape) std::cerr << dim << " ";
        std::cerr << std::endl;
        return -1;
    }

    // 输出张量的占位符
    std::vector<float> output_tensor_values(output_shape[1]);
    // 推理，直接使用模型中的输入输出名称
    auto output_tensors = session.Run(Ort::RunOptions{nullptr}, &input_name, &input_tensor, 1, &output_name, 1);

    // 处理输出
    float* raw_output = output_tensors[0].GetTensorMutableData<float>();

    // 打印 top-3 结果
    std::ifstream label_file("imagenet_class.txt");
    std::vector<std::string> labels;
    std::string line;
    while (std::getline(label_file, line)) {
        labels.push_back(line);
    }

    std::vector<std::pair<float, int>> results;
    for (int i = 0; i < output_shape[1]; ++i) {
        results.emplace_back(raw_output[i], i);
    }
    std::sort(results.begin(), results.end(), std::greater<>());

    // 输出 top-3
    for (int i = 0; i < 3; ++i) {
        std::cout << "Label: " << labels[results[i].second] << ", Probability: " << results[i].first << std::endl;
    }


    return 0;
}
