from dataset import dataset
from model import SRCNN
from utils import PSNR

import torch
import os

def training(architecture, steps, batch_size, save_every):
    ckpt_dir = f"checkpoint/SRCNN-{architecture}"
    model_path = os.path.join(ckpt_dir, f"SRCNN-{architecture}.pt")
    ckpt_path = os.path.join(ckpt_dir, "ckpt.pt")


    dataset_dir = "dataset"
    lr_crop_size = 33
    hr_crop_size = 21
    if architecture == 3:
        hr_crop_size = 19
    if architecture == 5:
        hr_crop_size = 17

    train_set = dataset(dataset_dir, "train")
    train_set.generate(lr_crop_size, hr_crop_size)
    train_set.load_data()

    valid_set = dataset(dataset_dir, "validation")
    valid_set.generate(lr_crop_size, hr_crop_size)
    valid_set.load_data()

    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    srcnn = SRCNN(architecture, device)
    srcnn.setup(optimizer=torch.optim.Adam(srcnn.model.parameters(), lr=2e-5),
                loss=torch.nn.MSELoss(),
                model_path=model_path,
                ckpt_path=ckpt_path,
                metric=PSNR)

    srcnn.load_checkpoint(ckpt_path)
    srcnn.train(train_set, valid_set,
                steps=steps,
                batch_size=batch_size,
                save_every=save_every,
                ckpt_dir=ckpt_dir)