import torch
import torchvision.io as io
from skimage.metrics import structural_similarity
import torchvision.transforms as transforms
import numpy as np
import os

def read_image(filepath):
    image = io.read_image(filepath, io.ImageReadMode.RGB)
    return image

def write_image(filepath, src):
    io.write_png(src, filepath)

def show_image(filepath):
    os.system(f"start {filepath}")

# https://www.researchgate.net/publication/284923134
def rgb2ycbcr(src):
    R = src[0]
    G = src[1]
    B = src[2]
    
    ycbcr = torch.zeros(size=src.shape)
    ycbcr[0] =  0.299 * R + 0.587 * G + 0.114 * B
    ycbcr[1] =  -0.16874 * R - 0.33126 * G + 0.5 * B + 128
    ycbcr[2] =  0.5 * R - 0.41869 * G - 0.08131 * B + 128

    ycbcr[0] = torch.clip(ycbcr[0], 16, 235)
    ycbcr[[1, 2]] = torch.clip(ycbcr[[1, 2]], 16, 240)
    ycbcr = ycbcr.type(torch.uint8)
    return ycbcr

# https://www.researchgate.net/publication/284923134
def ycbcr2rgb(src):
    Y = src[0]
    Cb = src[1]
    Cr = src[2]

    rgb = torch.zeros(size=src.shape)
    rgb[0] = Y + 1.402 * Cr - 179.456
    rgb[1] = Y - 0.34414 * Cb - 0.71414 * Cr + 135.45984
    rgb[2] = Y + 1.772 * Cb - 226.816

    rgb = torch.clip(rgb, 0, 255)
    rgb = rgb.type(torch.uint8)
    return rgb

def sorted_list(dir):
    ls = os.listdir(dir)
    ls.sort()
    for i in range(0, len(ls)):
        ls[i] = os.path.join(dir, ls[i])
    return ls

def resize_bicubic(src, h, w):
    image = transforms.Resize((h, w), transforms.InterpolationMode.BICUBIC)(src)
    return image

def gaussian_blur(src, ksize=3, sigma=0.7):
    blur_image = transforms.GaussianBlur(kernel_size=ksize, sigma=sigma)(src)
    return blur_image

def gaussian_noise(image, mean=0, sigma=5):
    noise = np.random.normal(mean, sigma, size=image.shape).astype(np.uint8)
    noisy_image = image + noise
    return noisy_image
    
def upscale(src, scale):
    h = int(src.shape[1] * scale)
    w = int(src.shape[2] * scale)
    image = resize_bicubic(src, h, w)
    return image

def downscale(src, scale):
    h = int(src.shape[1] / scale)
    w = int(src.shape[2] / scale)
    image = resize_bicubic(src, h, w)
    return image

def make_lr(src, scale=3):
    h = src.shape[1]
    w = src.shape[2]
    lr_image = downscale(src, scale)
    lr_image = resize_bicubic(lr_image, h, w)
    return lr_image

def norm01(src):
    return src / 255

def denorm01(src):
    return src * 255

def exists(path):
    return os.path.exists(path)

def MSE(y_true, y_pred):
    return torch.mean(torch.square(y_true - y_pred))

def PSNR(y_true, y_pred, max_val=1):
    mse = MSE(y_true, y_pred)
    return 10 * torch.log10(max_val * max_val / mse)

def SSIM(y_true, y_pred):
    y_true = y_true.numpy().astype(np.float32)
    y_pred = y_pred.numpy().astype(np.float32)

    y_true = np.transpose(y_true, (1, 2, 0))
    y_pred = np.transpose(y_pred, (1, 2, 0))

    ssim_value = structural_similarity(y_true, y_pred,
                                          data_range=y_true.max() - y_true.min(),
                                          channel_axis=2)
    return ssim_value

def random_crop(src, h, w):
    crop = transforms.RandomCrop([h, w])(src)
    return crop

def random_transform(src):
    _90_left, _90_right, _180 = 1, 3, 2
    operations = {
        0 : (lambda x : x                                       ),
        1 : (lambda x : torch.rot90(x, k=_90_left,  dims=(1, 2))),
        2 : (lambda x : torch.rot90(x, k=_90_right, dims=(1, 2))),
        3 : (lambda x : torch.rot90(x, k=_180,      dims=(1, 2))),
        4 : (lambda x : torch.fliplr(x)                         ),
        5 : (lambda x : torch.flipud(x)                         ),
    }
    idx = np.random.choice([0, 1, 2, 3, 4, 5])
    image_transform = operations[idx](src)
    return image_transform

def shuffle(X, Y, Z):
    if X.shape[0] != Z.shape[0]:
        raise ValueError("X, Y and Z must have the same number of elements")
    indices = np.arange(0, X.shape[0])
    np.random.shuffle(indices)
    X = torch.index_select(X, dim=0, index=torch.as_tensor(indices))
    Y = torch.index_select(Y, dim=0, index=torch.as_tensor(indices))
    Z = torch.index_select(Z, dim=0, index=torch.as_tensor(indices))
    return X, Y, Z

def tensor2numpy(tensor):
    return tensor.detach().cpu().numpy()

def to_cpu(tensor):
    return tensor.detach().cpu()