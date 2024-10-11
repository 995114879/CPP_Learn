#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 创建一个 100x100 的白色图像
    cv::Mat white_image(100, 100, CV_8UC3, cv::Scalar(0, 0, 0));

    // 保存为 example.jpg
    cv::imwrite("example.jpg", white_image);

    std::cout << "已生成 example.jpg" << std::endl;
    return 0;
}

