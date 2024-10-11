# ONNX教学课件

## 1. ONNX简介

ONNX (Open Neural Network Exchange) 是一种用于表示机器学习模型的开放格式。它定义了一组通用的运算符和标准数据类型,使不同框架之间的模型交换成为可能。

**主要特点:**

- 跨平台兼容性
- 框架无关性
- 广泛的工具和运行时支持

**主要优势:**

*   **互操作性:** ONNX 能够打破不同深度学习框架之间的壁垒，方便模型在不同框架之间转换和使用。
*   **硬件优化:** ONNX Runtime 可以针对不同的硬件平台进行优化，提升模型推理性能。
*   **可移植性:** ONNX 模型可以在不同的操作系统和硬件平台上运行，提高模型部署的灵活性。
*   **生态系统:** ONNX 拥有一个活跃的社区和丰富的工具支持，方便开发者使用和学习。

## 2. ONNX的工作原理

在ONNX（Open Neural Network Exchange）中，模型的结构使用计算图（computation graph）来表示。计算图是由节点（operators）和边（tensors）组成的有向图，节点表示具体的操作（如加法、卷积、激活函数等），边则表示从一个节点到下一个节点的数据流，通常是张量（tensors）。每个张量都有其形状（如`Float(2, 3, 4)`），并且可以携带数据。

下面我们将详细讲解你给出的示例，并扩展说明ONNX的计算图是如何工作的。

### 示例解读
```onnx
graph torch_graph(...) {
    %0 : Float(2, 3, 4) = onnx::Constant[value=...]()
    %1 : Float(2, 3, 4) = onnx::Constant[value=...]()
    %2 : Float(2, 3, 4) = onnx::Add(%0, %1)
    return (%2);
}
```

- **图名称**: `torch_graph` - 这是计算图的名字，可能表明该图是从PyTorch模型导出的。
- **节点和操作**:
  - `%0` 和 `%1` 是两个常量（通过 `onnx::Constant` 操作生成），每个常量都是一个 `Float` 类型的张量，形状为 `(2, 3, 4)`。常量的值通常是预定义的，但在此示例中，具体值被省略为 `...`。
  - `%2` 是通过 `onnx::Add` 操作生成的，它将两个输入张量 `%0` 和 `%1` 相加，生成的张量也是一个 `Float(2, 3, 4)` 类型的张量。
  - `return (%2)` 表示这个图的输出是 `%2`，即加法操作的结果。

### 计算图中的主要元素

1. **节点（Operators）**:
   - 节点是计算图中的操作符，通常对应于深度学习框架中的操作，如矩阵相乘、激活函数、卷积等。在这个例子中，我们有两个 `onnx::Constant` 节点（用于定义常量）和一个 `onnx::Add` 节点（用于执行张量相加操作）。
   
2. **边（Tensors）**:
   - 边表示节点之间的输入输出关系，通常是张量。在这个例子中，`%0` 和 `%1` 是两个常量张量，它们作为 `onnx::Add` 节点的输入，`%2` 是该节点的输出。
   - 张量的形状非常重要，例如，`Float(2, 3, 4)` 表示一个3维张量，其形状为 `(2, 3, 4)`，数据类型为 `Float`。

### 补充示例

我们可以进一步扩展此示例，包含更多的操作以展示一个更复杂的ONNX计算图。例如，我们可以在加法操作后增加一个矩阵乘法操作：

```onnx
graph torch_graph(...) {
    %0 : Float(2, 3, 4) = onnx::Constant[value=...]()
    %1 : Float(2, 3, 4) = onnx::Constant[value=...]()
    %2 : Float(2, 3, 4) = onnx::Add(%0, %1)
    
    %3 : Float(4, 5) = onnx::Constant[value=...]()  // 矩阵常量
    %4 : Float(2, 3, 5) = onnx::MatMul(%2, %3)      // 矩阵乘法
    return (%4);
}
```

在这个扩展示例中，除了原有的加法操作，我们还添加了一个新的矩阵乘法操作：
- `%3` 是一个 `Float(4, 5)` 形状的常量张量。
- `onnx::MatMul` 是一个矩阵乘法操作，它将 `%2`（形状为 `Float(2, 3, 4)`）与 `%3`（形状为 `Float(4, 5)`）相乘，输出结果为 `%4`，形状为 `Float(2, 3, 5)`。

### 计算图的实际作用

ONNX的计算图定义了数据从输入流向输出的完整路径，每个节点对应的操作是深度学习网络的不同层。例如，卷积层、批量归一化、ReLU激活等都可以表示为节点，而它们之间的张量边则表示不同层之间的数据流。在ONNX模型中，所有这些节点和张量的关系被序列化存储，便于跨平台使用。

### 总结

这个简单的ONNX计算图示例展示了基本的张量操作如何用图的形式表示。ONNX通过这种计算图抽象模型的结构和计算过程，使得模型可以在不同的深度学习框架和平台之间自由转换。

## 3. 安装ONNX

使用pip安装ONNX:

```bash
pip install onnx
```

对于C++开发,你可能需要从源代码编译ONNX:

```bash
git clone https://github.com/onnx/onnx.git
cd onnx
mkdir build && cd build
cmake ..
make
make install
```

## 4. 导出模型到ONNX

以PyTorch为例:

```python
import torch
import torch.nn as nn

class SimpleModel(nn.Module):
    def __init__(self):
        super(SimpleModel, self).__init__()
        self.fc = nn.Linear(10, 5)

    def forward(self, x):
        return self.fc(x)

model = SimpleModel()
dummy_input = torch.randn(1, 10)
torch.onnx.export(model, dummy_input, "simple_model.onnx", input_names=["input"], output_name=["output"])
```

## 5. 加载和检查ONNX模型

使用Python API:

```python
import onnx

# 加载模型
model = onnx.load("simple_model.onnx")

# 检查模型
onnx.checker.check_model(model)

# 打印模型信息
print(onnx.helper.printable_graph(model.graph))
```

## 6. 使用ONNX Runtime进行推理

Python示例:

```python
import onnxruntime as ort
import numpy as np

# 创建推理会话
session = ort.InferenceSession("simple_model.onnx")

# 准备输入数据
input_name = session.get_inputs()[0].name
input_data = np.random.randn(1, 10).astype(np.float32)

# 运行推理
output = session.run(None, {input_name: input_data})

print(output)
```

C++示例:

```cpp
#include <onnxruntime_cxx_api.h> // 包含 ONNX Runtime C++ API 的头文件
#include <vector> // 包含 vector 容器的头文件
#include <iostream> // 包含输入输出流的头文件

int main() {
    // 创建 ONNX Runtime 环境
    // ORT_LOGGING_LEVEL_WARNING 设置日志级别为警告
    // "test" 是日志标识符
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");

    // 创建 Session 选项，这里使用默认选项
    Ort::SessionOptions session_options;

    // 创建 ONNX Runtime Session，加载名为 "simple_model.onnx" 的模型
    Ort::Session session(env, "simple_model.onnx", session_options);

    // 创建输入数据，一个包含 10 个元素的浮点数向量，所有元素初始化为 1.0
    std::vector<float> input_data(10, 1.0f);

    // 定义输入和输出节点的名称
    std::vector<const char*> input_names = {"input"};
    std::vector<const char*> output_names = {"output"};

    // 创建内存信息，指定使用 CPU 和默认内存类型
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    // 创建输入张量
    // 使用 input_data 的数据，大小为 10，形状为 {1, 10} (1 行 10 列)
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_data.size(), {1, 10});

    // 运行模型推理
    // Ort::RunOptions{nullptr} 使用默认运行选项
    // input_names.data() 输入节点名称数组的指针
    // &input_tensor 输入张量的指针
    // 1 输入张量的数量
    // output_names.data() 输出节点名称数组的指针
    // 1 输出张量的数量
    auto output_tensors = session.Run(Ort::RunOptions{nullptr}, input_names.data(), &input_tensor, 1, output_names.data(), 1);

    // 获取输出张量的数据指针
    float* output_data = output_tensors.front().GetTensorMutableData<float>();

    // 打印输出张量的前 5 个元素
    for (int i = 0; i < 5; ++i) {
        std::cout << output_data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**代码功能:**

这段代码演示了如何使用 ONNX Runtime C++ API 加载 ONNX 模型并进行推理。它首先加载一个名为 "simple_model.onnx" 的模型，然后创建一个包含 10 个浮点数的输入张量，将其送入模型进行推理，最后打印输出张量的前 5 个元素。

**注意:** 

*  你需要安装 ONNX Runtime 并在编译时链接相应的库文件。
*  "simple_model.onnx" 应该是一个有效的 ONNX 模型文件，其输入节点名称为 "input"，输出节点名称为 "output"。
*  代码假设输出张量是一个浮点数张量，并且至少包含 5 个元素。

## 7. ONNX模型优化

使用ONNX Runtime的图优化工具:

```python
import onnx
from onnxruntime.tools.graph_optimization import optimize_model

# 加载模型
model = onnx.load("simple_model.onnx")

# 优化模型
optimized_model = optimize_model(model)

# 保存优化后的模型
onnx.save(optimized_model, "optimized_model.onnx")
```

## 8. ONNX运算符和自定义运算符

ONNX提供了大量标准运算符。如果需要,也可以定义自定义运算符:

```python
from onnx import helper, TensorProto

# 定义自定义运算符
custom_op = helper.make_opsetid("CustomDomain", 1)

# 创建节点
node_def = helper.make_node(
    'CustomOp',  # 运算符名称
    ['X'],       # 输入
    ['Y'],       # 输出
    domain='CustomDomain'
)

# 在图中使用自定义运算符
graph_def = helper.make_graph(
    [node_def],
    "CustomOpGraph",
    [helper.make_tensor_value_info("X", TensorProto.FLOAT, [1, 10])],
    [helper.make_tensor_value_info("Y", TensorProto.FLOAT, [1, 5])]
)

# 创建模型
model_def = helper.make_model(graph_def, producer_name='CustomOpModel')
model_def.opset_import.append(custom_op)

onnx.save(model_def, "custom_op_model.onnx")
```

## 9. 自定义算子

### **9.1. 定义 PyTorch 自定义算子并导出 ONNX 模型:**

```python
import torch
import torch.nn as nn
import torch.onnx

# 自定义 ChannelShuffle 算子
class ChannelShuffle(torch.autograd.Function):
    @staticmethod
    def forward(ctx, x, groups):
        N, C, H, W = x.size()
        g = groups
        assert C % g == 0, "ChannelShuffle: input channels must be divisible by groups"
        x = x.view(N, g, C // g, H, W)
        x = x.permute(0, 2, 1, 3, 4).contiguous()
        x = x.view(N, C, H, W)
        return x

    @staticmethod
    def backward(ctx, grad_output):
        N, C, H, W = grad_output.size()
        g = ctx.groups
        grad_output = grad_output.view(N, g, C // g, H, W)
        grad_output = grad_output.permute(0, 2, 1, 3, 4).contiguous()
        grad_output = grad_output.view(N, C, H, W)
        return grad_output, None


# 使用自定义算子的 PyTorch 模型
class MyModel(nn.Module):
    def __init__(self, groups):
        super(MyModel, self).__init__()
        self.groups = groups

    def forward(self, x):
        return ChannelShuffle.apply(x, self.groups)

# 创建模型实例并导出 ONNX 模型
model = MyModel(groups=2)
dummy_input = torch.randn(1, 4, 224, 224)
torch.onnx.export(model, dummy_input, "my_model.onnx", verbose=True, opset_version=13)

# 注册自定义算子符号，以便导出 ONNX
def channel_shuffle_symbolic(g, input, groups):
    return g.op("mydomain::ChannelShuffle", input, groups_i=groups)

torch.onnx.register_custom_op_symbolic('::ChannelShuffle', channel_shuffle_symbolic, 13)
```

### **9.2. 实现自定义算子的 C++ Kernel:**

```cpp
#include "onnxruntime_cxx_api.h"

// ChannelShuffle Kernel 的实现
class ChannelShuffleKernel : public Ort::OpKernel {
public:
    ChannelShuffleKernel(const OrtApi& api, const OrtKernelInfo* info) : Ort::OpKernel(api, info) {
        groups_ = info->GetAttribute<int64_t>("groups_i");
    }

    void Compute(OrtKernelContext* context) override {
        // 获取输入张量
        const OrtValue* input_tensor = context->GetInput(0);
        auto input_info = input_tensor->GetTensorTypeAndShapeInfo();
        auto input_shape = input_info->GetShape();
        auto input_data = input_tensor->GetTensorMutableData<float>();

        // 创建输出张量
        OrtValue* output_tensor = context->GetOutput(0, input_shape.data(), input_shape.size());
        auto output_data = output_tensor->GetTensorMutableData<float>();

        // 计算 ChannelShuffle
        int64_t N = input_shape[0];
        int64_t C = input_shape[1];
        int64_t H = input_shape[2];
        int64_t W = input_shape[3];
        int64_t g = groups_;

        for (int64_t n = 0; n < N; ++n) {
            for (int64_t c = 0; c < C; ++c) {
                int64_t group_index = c % g;
                int64_t channel_in_group = c / g;
                int64_t new_c = channel_in_group * g + group_index;
                for (int64_t h = 0; h < H; ++h) {
                    for (int64_t w = 0; w < W; ++w) {
                        output_data[n * C * H * W + new_c * H * W + h * W + w] = 
                            input_data[n * C * H * W + c * H * W + h * W + w];
                    }
                }
            }
        }
    }

private:
    int64_t groups_;
};

// 注册自定义算子
OrtStatus* RegisterCustomOps(OrtSessionOptions* options, const OrtApiBase* api) {
    OrtCustomOpDomain* domain = OrtCreateCustomOpDomain("mydomain");
    OrtStatus* status = api->CustomOpDomain_Add(domain, "ChannelShuffle", OrtCustomOpType::ORT_CUSTOM_OP_KERNEL);

    // 创建 Kernel Creator
    OrtCustomOpKernelCreateInfo kernel_info;
    kernel_info.op_kernel_lib_name = "libchannelshuffle.so"; // 替换成你的库名
    kernel_info.op_kernel_name = "ChannelShuffleKernel";
    kernel_info.kernel_create_func = [](const OrtCustomOpApi* api, const OrtKernelInfo* info) -> OrtKernelBase* {
        return new ChannelShuffleKernel(api->GetOrtApi(), info);
    };

    status = api->CustomOpDomain_AddKernel(domain, &kernel_info);
    api->AddCustomOpDomain(options, domain);
    api->ReleaseCustomOpDomain(domain);
    return status;
}

// ... 其他代码 ...
```

### **9.3. 编译自定义算子的 Kernel:** 

将上面的 C++ 代码编译成一个动态链接库 (例如 `libchannelshuffle.so`)。

### **9.4. 在 C++ 代码中加载 ONNX 模型并使用自定义算子:**

```cpp
#include "onnxruntime_cxx_api.h"
// ... 其他头文件 ...

int main() {
    // 创建 ONNX runtime 环境和 SessionOptions
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
    Ort::SessionOptions session_options;

    // 注册自定义算子
    RegisterCustomOps(&session_options, OrtGetApiBase());

    // 创建 Session
    Ort::Session session(env, "my_model.onnx", session_options);

    // ... 其他代码 (准备输入数据, 执行推理等) ...

    return 0;
}
```

**解释:**

与之前的 `MyReLU` 例子类似，我们首先定义了 `ChannelShuffle` 算子并在 PyTorch 中导出 ONNX 模型，同时注册了自定义算子符号。然后，我们使用 C++ 实现了 `ChannelShuffle` 算子的 Kernel，包括计算逻辑和注册函数。接着，我们将 Kernel 编译成动态链接库。最后，在 C++ 代码中加载 ONNX 模型时，我们使用 `RegisterCustomOps` 函数注册自定义算子，并创建 Session。


**注意:**

* ChannelShuffle 算子的逻辑无法用 ONNX 标准算子直接表示，所以需要注册自定义算子并提供 C++ 实现。
* 你需要根据你的自定义算子的逻辑来实现对应的 C++ Kernel。
* 你需要将 Kernel 编译成动态链接库，并在 C++ 代码中加载它。
* 你需要确保 ONNX runtime 的版本与你使用的 ONNX opset 版本兼容。


通过以上步骤，你就可以在 ONNX runtime C++ 版本中增加对 ChannelShuffle 算子的支持，并在推理时使用它。

## 10. ONNX与其他框架的集成

ONNX支持多种深度学习框架,包括但不限于:
- PyTorch
- TensorFlow
- Keras
- MXNet
- Scikit-learn

每个框架都有其特定的ONNX导出方法。

## 11. ONNX的实际应用案例

1. 模型部署:
   - 在云端训练模型,导出为ONNX,然后在边缘设备上部署。
2. 模型交换:
   - 在PyTorch中训练模型,导出为ONNX,然后在TensorFlow中使用。
3. 模型优化:
   - 使用ONNX Runtime的优化功能提高模型性能。

## 12. ONNX的未来发展

- 更多框架的支持
- 更丰富的运算符集
- 更强大的优化工具
- 在边缘计算和IoT领域的应用

## 13. 总结

ONNX为深度学习模型的部署和交换提供了一个强大的解决方案。通过学习ONNX,你可以更灵活地处理不同框架的模型,并在各种平台上高效地部署它们。