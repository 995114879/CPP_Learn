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

#torch.onnx.export(model, dummy_input, "simple_model.onnx", verbose=True)
torch.onnx.export(model, dummy_input, "simple_model.onnx", input_names=["input"], output_names=["output"])