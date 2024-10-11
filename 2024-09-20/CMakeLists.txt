cmake_minimum_required(VERSION 3.10)
project(ONNXResNetInference)

# 查找 OpenCV 包
# find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OpenCV4 REQUIRED opencv4)

# 添加 include 目录（OpenCV 和 Libtorch）
include_directories(${OpenCV4_INCLUDE_DIRS})

# 设置可执行文件的源代码
add_executable(onnx_resnet_inference resnet50_model_infer.cpp)

target_link_libraries(onnx_resnet_inference  ${OpenCV4_LIBRARIES} onnxruntime)
