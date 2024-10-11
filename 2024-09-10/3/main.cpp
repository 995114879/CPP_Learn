#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 加载灰度图像
    cv::Mat image = cv::imread("example.jpg", cv::IMREAD_GRAYSCALE);

    // 检查图像是否加载成功
    if (image.empty()) {
        std::cerr << "无法加载图像!" << std::endl;
        return -1;
    }

    // 反转每个像素的灰度值
    for (int y = 0; y < image.rows; y++) {
        uchar* row_ptr = image.ptr<uchar>(y);
        for (int x = 0; x < image.cols; x++) {
            row_ptr[x] = 255 - row_ptr[x];  // 反转像素值
        }
    }

    // 保存反转后的图像
    cv::imwrite("inverted_image.jpg", image);

    std::cout << "已完成图像反转并保存为 inverted_image.jpg" << std::endl;

    return 0;
}