from torchvision import transforms as T
from PIL import Image
import cv2

def prepare_image(image_file_path, target_size=(224, 224)):
    with open(image_path, 'rb') as image_file:
        image = image_file.read()
    image = Image.open(io.BytesIO(image))
    image = prepare_image(image, target_size=(224, 224))

    """对输入图像进行预处理"""
    if image.mode != 'RGB':
        image = image.convert("RGB")

    # 调整图像尺寸并转换为张量
    preprocess = T.Compose([
        T.Resize(target_size),
        T.ToTensor(),
        T.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
    ])

    image = preprocess(image).unsqueeze(0)

    if use_gpu:
        image = image.cuda()
    return image


def prepare_image2(image_file_path, target_size=(224, 224)):
    pass # return a tensor


def main():
    # prepare_image -> Tensor1
    # prepare_image2 -> Tensor2

    # Tensor1 == Tensor2
