from model import SRCNN
from utils import *

import torch

def testing(architecture, scale):
    ckpt_path = f"checkpoint/SRCNN-{architecture}/SRCNN-{architecture}.pt"

    pad = architecture // 2 + 6

    device = "cuda" if torch.cuda.is_available() else "cpu"
    model = SRCNN(architecture, device)
    model.load_weights(ckpt_path)

    ls_data = sorted_list(f"dataset/test/x{scale}/data")
    ls_labels = sorted_list(f"dataset/test/x{scale}/labels")

    sum_mse_bicubic1 = sum_mse_bicubic2 = sum_mse = 0
    sum_psnr_bicubic1 = sum_psnr_bicubic2 = sum_psnr = 0
    sum_ssim_bicubic1 = sum_ssim_bicubic2 = sum_ssim = 0
    with torch.no_grad():
        for i in range(0, len(ls_data)):
            lr_image = read_image(ls_data[i])
            lr_image1 = gaussian_blur(lr_image)
            lr_image2 = gaussian_noise(lr_image)
            hr_image = read_image(ls_labels[i])
            
            bicubic_image1 = upscale(lr_image1, scale)
            bicubic_image2 = upscale(lr_image2, scale)

            bicubic_image1 = rgb2ycbcr(bicubic_image1)
            bicubic_image2 = rgb2ycbcr(bicubic_image2)
            hr_image = rgb2ycbcr(hr_image)

            bicubic_image1 = norm01(bicubic_image1)
            bicubic_image2 = norm01(bicubic_image2)
            hr_image = norm01(hr_image)

            bicubic_image1_pad = bicubic_image1[:, pad:-pad, pad:-pad]
            bicubic_image2_pad = bicubic_image2[:, pad:-pad, pad:-pad]
            hr_image = hr_image[:, pad:-pad, pad:-pad]

            bicubic_image1 = torch.unsqueeze(bicubic_image1, dim=0).to(device)
            bicubic_image2 = torch.unsqueeze(bicubic_image2, dim=0).to(device)
            sr_image = model.predict(bicubic_image1, bicubic_image2)[0].cpu()

            sum_mse_bicubic1 += MSE(hr_image, bicubic_image1_pad)
            sum_psnr_bicubic1 += PSNR(hr_image, bicubic_image1_pad)
            sum_ssim_bicubic1 += SSIM(hr_image, bicubic_image1_pad)

            sum_mse_bicubic2 += MSE(hr_image, bicubic_image2_pad)
            sum_psnr_bicubic2 += PSNR(hr_image, bicubic_image2_pad)
            sum_ssim_bicubic2 += SSIM(hr_image, bicubic_image2_pad)

            sum_mse += MSE(hr_image, sr_image)
            sum_psnr += PSNR(hr_image, sr_image)
            sum_ssim += SSIM(hr_image, sr_image)

    data = [
        ["Bicubic 1",
         "{:.5f}".format(sum_mse_bicubic1.item() / len(ls_data)),
         "{:.5f}".format(sum_psnr_bicubic1.item() / len(ls_data)),
         "{:.5f}".format(sum_ssim_bicubic1 / len(ls_data))],
        ["Bicubic 2",
         "{:.5f}".format(sum_mse_bicubic2.item() / len(ls_data)),
         "{:.5f}".format(sum_psnr_bicubic2.item() / len(ls_data)),
         "{:.5f}".format(sum_ssim_bicubic2 / len(ls_data))],
        ["MSRCNN",
         "{:.5f}".format(sum_mse.item() / len(ls_data)),
         "{:.5f}".format(sum_psnr.item() / len(ls_data)),
         "{:.5f}".format(sum_ssim / len(ls_data))]
    ]

    return data


