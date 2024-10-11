#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 加载彩色图像
    cv::Mat image = cv::imread("Lena.jpg");

    // 检查图像是否加载成功
    if (image.empty()) {
        std::cerr << "无法加载图像!" << std::endl;
        return -1;
    }

    // 定义ROI区域 (从图像的(100, 100)位置开始，大小为200x200)
    cv::Rect roi(100, 100, 200, 200);

    // 确保ROI区域不超出图像边界
    if (roi.x + roi.width > image.cols || roi.y + roi.height > image.rows) {
        std::cerr << "ROI区域超出图像边界!" << std::endl;
        return -1;
    }

    // 获取ROI
    cv::Mat image_roi = image(roi);

    // 对ROI进行高斯模糊操作
    cv::GaussianBlur(image_roi, image_roi, cv::Size(5, 5), -1);

    // 保存处理后的图像
    cv::imwrite("blurred_image.jpg", image);

    std::cout << "已对ROI区域进行高斯模糊，并保存为 blurred_image.jpg" << std::endl;

    return 0;
}