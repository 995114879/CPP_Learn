import onnx

# 加载模型
model = onnx.load("simple_model.onnx")

# 检查模型
onnx.checker.check_model(model)

# 打印模型信息
print(onnx.helper.printable_graph(model.graph))