## C++ OpenCV 视频处理应用场景 (第34节)

### 一、课程目标

* 了解 OpenCV 在视频处理领域的常见应用场景
* 掌握视频读取、显示、保存等基本操作
* 学习目标检测、目标跟踪等核心算法的实现
* 能够运用 OpenCV 解决实际的视频处理问题

### 二、视频基础操作

#### 2.1 视频读取

OpenCV 提供了 `VideoCapture` 类用于读取视频文件或摄像头数据。

**代码示例:**

```cpp
#include <opencv2/opencv.hpp>

int main() {
  // 读取视频文件
  cv::VideoCapture cap("video.mp4");

  // 检查是否成功打开
  if (!cap.isOpened()) {
    std::cerr << "Error opening video stream or file" << std::endl;
    return -1;
  }

  cv::Mat frame;
  while (true) {
    // 从视频捕获下一帧
    cap >> frame;

    // 检查是否到达视频末尾
    if (frame.empty()) {
      break;
    }

    // 在窗口中显示帧
    cv::imshow("Video Frame", frame);

    // 等待按键输入
    if (cv::waitKey(30) >= 0) {
      break;  // 按键退出
    }
  }

  // 释放资源
  cap.release();
  cv::destroyAllWindows();
  return 0;
}

```

#### 2.2 视频保存

可以使用 `VideoWriter` 类将处理后的视频帧保存为新的视频文件。

**代码示例:**

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  // 读取视频文件
  cv::VideoCapture cap("input.mp4");

  // 检查是否成功打开视频文件
  if (!cap.isOpened()) {
    std::cerr << "Error opening video stream or file" << std::endl;
    return -1;
  }

  // 定义输出视频的编码器、帧率、尺寸等参数
  int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // MJPG 编码器
  double fps = cap.get(cv::CAP_PROP_FPS); // 使用输入视频的帧率
  cv::Size size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT)); // 视频尺寸

  // 创建 VideoWriter 对象
  cv::VideoWriter writer("output.avi", codec, fps, size);

  // 检查 VideoWriter 是否成功打开
  if (!writer.isOpened()) {
    std::cerr << "Could not open the output video file for write" << std::endl;
    return -1;
  }

  cv::Mat frame;
  while (true) {
    // 读取下一帧
    cap >> frame;

    // 检查是否到达视频末尾
    if (frame.empty()) {
      break;
    }

    // 处理视频帧（可以添加图像处理代码，比如灰度转换等）
    // cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY); // 示例：将帧转换为灰度图像

    // 写入处理后的帧到输出文件
    writer.write(frame);

    // 显示帧
    cv::imshow("Processed Frame", frame);

    // 按下任意键退出
    if (cv::waitKey(30) >= 0) {
      break;
    }
  }

  // 释放资源
  cap.release();
  writer.release();
  cv::destroyAllWindows();

  return 0;
}

```

#### 2.3 读取摄像头并录制视频

```
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  // 打开默认摄像头 (设备ID为0)
  cv::VideoCapture cap(0);

  // 检查摄像头是否成功打开
  if (!cap.isOpened()) {
    std::cerr << "Error opening camera" << std::endl;
    return -1;
  }

  // 定义输出视频的编码器、帧率、尺寸等参数
  int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');  // MJPG 编码器
  double fps = 25.0;  // 帧率
  cv::Size size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT));  // 视频尺寸

  // 创建 VideoWriter 对象用于写入视频文件
  cv::VideoWriter writer("output.avi", codec, fps, size);

  // 检查 VideoWriter 是否成功打开
  if (!writer.isOpened()) {
    std::cerr << "Could not open the output video file for write" << std::endl;
    return -1;
  }

  cv::Mat frame;
  while (true) {
    // 从摄像头读取一帧
    cap >> frame;

    // 检查是否成功读取
    if (frame.empty()) {
      std::cerr << "Failed to capture an image" << std::endl;
      break;
    }

    // 将帧写入输出视频文件
    writer.write(frame);

    // 显示当前帧
    cv::imshow("Camera Frame", frame);

    // 按下 'q' 键退出
    if (cv::waitKey(1) == 'q') {
      break;
    }
  }

  // 释放资源
  cap.release();
  writer.release();
  cv::destroyAllWindows();

  return 0;
}
```

g++ -o camera_capture camera_capture.cpp `pkg-config --cflags --libs opencv4`

### 三、目标检测

#### 3.1 基于 Haar 特征的目标检测

OpenCV 提供了预训练的 Haar 级联分类器，可以用于检测人脸、眼睛等物体。

**代码示例:**

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 加载人脸检测器
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading haarcascade_frontalface_default.xml" << std::endl;
        return -1;
    }

    // 打开摄像头 (0 表示默认摄像头)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        // 读取视频帧
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "No captured frame -- Break!" << std::endl;
            break;
        }

        // 转换为灰度图像
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        // 检测人脸
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

        // 绘制矩形框
        for (size_t i = 0; i < faces.size(); i++) {
            cv::rectangle(frame, faces[i], cv::Scalar(255, 0, 0), 2);
        }

        // 显示结果帧
        cv::imshow("Face Detection", frame);

        // 按下 'q' 键退出
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // 释放摄像头
    cap.release();
    cv::destroyAllWindows();
    return 0;
}

```

#### 3.2 基于深度学习的目标检测 (YOLO)

YOLO 是一种快速准确的深度学习目标检测算法，OpenCV 提供了 DNN 模块可以加载 YOLO 模型进行目标检测.

**代码示例:**

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>

// 函数：获取检测框的中心坐标、宽高、置信度等信息
void postprocess(cv::Mat& frame, const std::vector<cv::Mat>& outs, float confThreshold, float nmsThreshold, std::vector<std::string>& classes) {
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (size_t i = 0; i < outs.size(); ++i) {
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            double confidence;
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold) {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    // 非极大值抑制，删除重叠的检测框
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);

    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 3); // 绘制检测框
        std::string label = cv::format("%.2f", confidences[idx]);
        if (!classes.empty()) {
            label = classes[classIds[idx]] + ": " + label;
        }
        cv::putText(frame, label, cv::Point(box.x, box.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
    }
}

int main() {
    // 加载 YOLO 模型和配置文件
    cv::dnn::Net net = cv::dnn::readNetFromDarknet("yolov3.cfg", "yolov3.weights");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    // 读取类名
    std::vector<std::string> classes;
    std::ifstream ifs("coco.names");
    std::string line;
    while (getline(ifs, line)) {
        classes.push_back(line);
    }

    // 读取视频文件或者摄像头
    cv::VideoCapture cap("input.mp4"); // 可以将 "input.mp4" 替换为 0 打开摄像头
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // 定义阈值
    float confThreshold = 0.5; // 置信度阈值
    float nmsThreshold = 0.4;  // 非极大值抑制阈值

    cv::Mat frame;
    while (true) {
        // 从视频读取下一帧
        cap >> frame;

        // 检查是否到达视频末尾
        if (frame.empty()) {
            break;
        }

        // 预处理输入图像
        cv::Mat blob;
        cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
        net.setInput(blob);

        // 进行推理
        std::vector<cv::Mat> outs;
        net.forward(outs, net.getUnconnectedOutLayersNames());

        // 处理输出结果
        postprocess(frame, outs, confThreshold, nmsThreshold, classes);

        // 显示处理后的帧
        cv::imshow("YOLO Object Detection", frame);

        // 按下 'q' 键退出
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // 释放资源
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

```

**模型加载**：

- `yolov3.cfg` 和 `yolov3.weights` 是 YOLOv3 的配置文件和预训练权重文件。请确保这些文件位于可访问的路径。
- `coco.names` 文件包含了 YOLOv3 预训练模型所识别的 80 个类的名称。

**预处理**：

- 使用 `cv::dnn::blobFromImage` 将每一帧转换为网络输入格式（尺寸 416x416，像素值归一化到 [0, 1]）。

**推理**：

- 使用 `net.forward` 对输入帧进行推理，获取多个输出层的结果。

**结果处理**：

- `postprocess` 函数处理 YOLO 输出，解析每个检测框的中心点、宽高和类别置信度，绘制检测框和标签。

**显示结果**：

- 每一帧通过 `cv::imshow` 显示检测结果。

**退出**：

- 按下 `'q'` 键退出循环并停止检测。

### 四、目标跟踪

#### 4.1 Meanshift 跟踪算法

Meanshift 是一种基于颜色直方图的跟踪算法.

**代码示例:**

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

// 全局变量，用于存储用户选择的目标区域
cv::Rect2d bbox;
bool selectObject = false;

// 鼠标回调函数，选择跟踪目标区域
void onMouse(int event, int x, int y, int, void* param) {
    static cv::Point origin;
    cv::Mat* image = (cv::Mat*)param;

    if (selectObject) {
        bbox.x = std::min(x, origin.x);
        bbox.y = std::min(y, origin.y);
        bbox.width = std::abs(x - origin.x);
        bbox.height = std::abs(y - origin.y);

        // 绘制当前选择的区域
        cv::Mat temp;
        image->copyTo(temp);
        cv::rectangle(temp, bbox, cv::Scalar(255, 0, 0), 2);
        cv::imshow("Select Object", temp);
    }

    if (event == cv::EVENT_LBUTTONDOWN) {
        origin = cv::Point(x, y);
        bbox = cv::Rect2d(x, y, 0, 0);
        selectObject = true;
    } else if (event == cv::EVENT_LBUTTONUP) {
        selectObject = false;
    }
}

int main() {
    // 读取视频文件或者摄像头
    cv::VideoCapture cap("input.mp4");  // 或者用 cap(0) 打开摄像头
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame;  // 读取第一帧

    // 显示第一帧，并等待用户选择要跟踪的对象区域
    cv::imshow("Select Object", frame);
    cv::setMouseCallback("Select Object", onMouse, &frame);
    while (selectObject) {
        cv::waitKey(1);
    }

    // 选择完目标区域后，计算目标区域的 HSV 直方图
    cv::Mat roi = frame(bbox);
    cv::cvtColor(roi, roi, cv::COLOR_BGR2HSV);

    float hranges[] = {0, 180};  // 色调范围
    const float* phranges = hranges;
    int channels[] = {0};  // 只使用色调通道
    cv::Mat hist;
    int histSize = 64;  // 直方图的大小
    cv::calcHist(&roi, 1, channels, cv::Mat(), hist, 1, &histSize, &phranges);  // 计算直方图
    cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX);  // 归一化直方图

    // 设置 CamShift 的终止条件
    cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10, 1);

    while (true) {
        cap >> frame;  // 读取下一帧
        if (frame.empty()) {
            break;
        }

        // 转换当前帧为 HSV
        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 计算当前帧的后向投影
        cv::Mat backproj;
        cv::calcBackProject(&hsv, 1, channels, hist, backproj, &phranges);

        // 使用 CamShift 进行目标跟踪
        cv::RotatedRect trackBox = cv::CamShift(backproj, bbox, criteria);

        // 在当前帧上绘制跟踪框
        cv::ellipse(frame, trackBox, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);

        // 显示当前帧
        cv::imshow("Tracking", frame);

        // 按下 'q' 键退出
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // 释放资源
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

```

### 代码说明：

1. **鼠标回调**：
   - 通过 `onMouse` 函数，用户可以通过鼠标点击并拖动选择要跟踪的目标区域。
   - 使用 OpenCV 提供的 `setMouseCallback` 函数设置鼠标事件监听。
2. **目标区域直方图**：
   - 一旦选择了目标区域，程序将该区域转换为 HSV 颜色空间，并计算色调通道的直方图。
   - 直方图被归一化，用作后向投影的参考。
3. **目标跟踪**：
   - 每帧中，计算后向投影，使用 CamShift 算法更新目标位置。
   - `cv::CamShift` 返回旋转矩形 `cv::RotatedRect`，用于绘制跟踪框。
4. **帧显示和退出**：
   - 每帧显示处理后的图像，按下 `'q'` 键退出循环。

#### 4.2 KCF 跟踪算法

KCF 是一种基于循环矩阵和核函数的跟踪算法，具有较高的效率和鲁棒性.

**代码示例:**

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

// 全局变量，用于存储用户选择的目标区域
cv::Rect2d bbox;
bool selectObject = false;

// 鼠标回调函数，选择跟踪目标区域
void onMouse(int event, int x, int y, int, void* param) {
    static cv::Point origin;
    cv::Mat* image = (cv::Mat*)param;

    if (selectObject) {
        bbox.x = std::min(x, origin.x);
        bbox.y = std::min(y, origin.y);
        bbox.width = std::abs(x - origin.x);
        bbox.height = std::abs(y - origin.y);

        // 绘制当前选择的区域
        cv::Mat temp;
        image->copyTo(temp);
        cv::rectangle(temp, bbox, cv::Scalar(255, 0, 0), 2);
        cv::imshow("Select Object", temp);
    }

    if (event == cv::EVENT_LBUTTONDOWN) {
        origin = cv::Point(x, y);
        bbox = cv::Rect2d(x, y, 0, 0);
        selectObject = true;
    } else if (event == cv::EVENT_LBUTTONUP) {
        selectObject = false;
    }
}

int main() {
    // 打开视频文件或摄像头
    cv::VideoCapture cap(0); // 使用摄像头，可以替换为视频文件名
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame;  // 读取第一帧

    // 显示第一帧，并等待用户通过鼠标选择跟踪区域
    cv::imshow("Select Object", frame);
    cv::setMouseCallback("Select Object", onMouse, &frame);
    while (selectObject) {
        cv::waitKey(1); // 等待用户选择完目标区域
    }

    // 创建 KCF 跟踪器
    cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
    tracker->init(frame, bbox);  // 初始化跟踪器

    while (true) {
        cap >> frame;  // 读取下一帧
        if (frame.empty()) {
            break;
        }

        // 更新跟踪结果
        bool ok = tracker->update(frame, bbox);

        // 绘制跟踪框
        if (ok) {
            cv::rectangle(frame, bbox, cv::Scalar(255, 0, 0), 2, 1);
        } else {
            cv::putText(frame, "Tracking failure detected", cv::Point(100, 80),
                        cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 255), 2);
        }

        // 显示当前帧
        cv::imshow("Tracking", frame);

        // 按下 'q' 键退出
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // 释放资源
    cap.release();
    cv::destroyAllWindows();

    return 0;
}

```


### 五、 总结

本节课介绍了 OpenCV 在视频处理领域的常见应用场景，包括视频读取、显示、保存、目标检测和目标跟踪等。我们学习了如何使用 OpenCV 实现这些功能，并提供了完整的代码示例. 

### 六、 作业

1. 使用 OpenCV 读取一段视频，并将其转换为灰度视频保存.

   