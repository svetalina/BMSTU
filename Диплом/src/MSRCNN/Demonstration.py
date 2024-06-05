from model import SRCNN
from utils import *

def demonstration(architecture, image_path1, image_path2, scale):
    ckpt_path = f"checkpoint/SRCNN-{architecture}/SRCNN-{architecture}.pt"

    device = "cuda" if torch.cuda.is_available() else "cpu"

    lr_image1 = read_image(image_path1)
    show_image(image_path1)
    lr_image2 = read_image(image_path2)
    show_image(image_path2)

    bicubic_image1 = upscale(lr_image1, scale)
    write_image("img/bicubic1.png", bicubic_image1)
    show_image("img/bicubic1.png")

    bicubic_image2 = upscale(lr_image2, scale)
    write_image("img/bicubic2.png", bicubic_image2)
    show_image("img/bicubic2.png")

    bicubic_image1 = rgb2ycbcr(bicubic_image1)
    bicubic_image1 = norm01(bicubic_image1)
    bicubic_image1 = torch.unsqueeze(bicubic_image1, dim=0)

    bicubic_image2 = rgb2ycbcr(bicubic_image2)
    bicubic_image2 = norm01(bicubic_image2)
    bicubic_image2 = torch.unsqueeze(bicubic_image2, dim=0)

    model = SRCNN(architecture, device)
    model.load_weights(ckpt_path)
    with torch.no_grad():
        bicubic_image1, bicubic_image2 = bicubic_image1.to(device), bicubic_image2.to(device),
        hr_image = model.predict(bicubic_image1, bicubic_image2)[0]

    hr_image = denorm01(hr_image)
    hr_image = ycbcr2rgb(hr_image.type(torch.uint8))

    write_image("img/hr.png", hr_image)
    show_image("img/hr.png")
