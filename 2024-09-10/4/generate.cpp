#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 创建一个 500x500 的白色图像
    cv::Mat white_image(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));

    // 在中心绘制一个红色矩形作为标记
    cv::rectangle(white_image, cv::Point(100, 100), cv::Point(300, 300), cv::Scalar(0, 0, 255), -1);

    // 保存为 example.jpg
    cv::imwrite("example.jpg", white_image);

    std::cout << "已生成 example.jpg" << std::endl;
    return 0;
}