#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 加载灰度图像
    cv::Mat image = cv::imread("example.jpg", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "无法加载图像!" << std::endl;
        return -1;
    }

    // 访问灰度图像的像素
    int x = 50, y = 50; // 假设你访问(50, 50)的像素
    uchar pixel = image.at<uchar>(y, x);
    std::cout << "灰度图像像素值: " << static_cast<int>(pixel) << std::endl;

    // 修改像素值
    image.at<uchar>(y, x) = 255;

    // 保存修改后的灰度图像
    cv::imwrite("modified_gray.jpg", image);

    // 加载彩色图像 -> 
    cv::Mat color_image = cv::imread("example.jpg", cv::IMREAD_COLOR);
    if (color_image.empty()) {
        std::cerr << "无法加载彩色图像!" << std::endl;
        return -1;
    }

    // 访问彩色图像的像素 (BGR 顺序)
    cv::Vec3b pixel_color = color_image.at<cv::Vec3b>(y, x);
    uchar blue = pixel_color[0];
    uchar green = pixel_color[1];
    uchar red = pixel_color[2];
    std::cout << "彩色图像像素值 - 蓝: " << static_cast<int>(blue)
              << ", 绿: " << static_cast<int>(green)
              << ", 红: " << static_cast<int>(red) << std::endl;

    // 修改彩色图像的像素为蓝色
    color_image.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 0, 0);

    // 保存修改后的彩色图像
    cv::imwrite("modified_color.jpg", color_image);

    return 0;
}