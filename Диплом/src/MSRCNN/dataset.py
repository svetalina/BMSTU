from utils import *

import numpy as np
import torch
import os

class dataset:
    def __init__(self, dataset_dir, subset):
        self.dataset_dir = dataset_dir
        self.subset = subset
        self.data1 = torch.Tensor([])
        self.data2 = torch.Tensor([])
        self.labels = torch.Tensor([])
        self.data1_file = os.path.join(self.dataset_dir, f"data1_{self.subset}.npy")
        self.data2_file = os.path.join(self.dataset_dir, f"data2_{self.subset}.npy")
        self.labels_file = os.path.join(self.dataset_dir, f"labels_{self.subset}.npy")
        self.cur_idx = 0
    
    def generate(self, lr_crop_size, hr_crop_size):
        if exists(self.data1_file) and exists(self.data2_file) and exists(self.labels_file):
            print(f"{self.data1_file}, {self.data2_file}  и {self.labels_file} уже существуют\n")
            return
        data1 = []
        data2 = []
        labels = []
        padding = np.absolute(hr_crop_size - lr_crop_size) // 2
        step = 14

        subset_dir = os.path.join(self.dataset_dir, self.subset)
        ls_images = sorted_list(subset_dir)
        for image_path in ls_images:
            hr_image = read_image(image_path)

            lr_image1 = gaussian_blur(hr_image)
            lr_image1 = make_lr(lr_image1)

            lr_image2 = gaussian_noise(hr_image)
            lr_image2 = make_lr(lr_image2)

            hr_image = rgb2ycbcr(hr_image)
            lr_image1 = rgb2ycbcr(lr_image1)
            lr_image2 = rgb2ycbcr(lr_image2)

            hr_image = norm01(hr_image)
            lr_image1 = norm01(lr_image1)
            lr_image2 = norm01(lr_image2)

            h = hr_image.shape[1]
            w = hr_image.shape[2]
            for x in np.arange(start=0, stop=h-lr_crop_size, step=step):
                for y in np.arange(start=0, stop=w-lr_crop_size, step=step):
                    data1_tmp  = lr_image1[:, x : x + lr_crop_size, y : y + lr_crop_size]
                    data2_tmp = lr_image2[:, x: x + lr_crop_size, y: y + lr_crop_size]
                    label_tmp = hr_image[:, x + padding : x + padding + hr_crop_size,
                                              y + padding : y + padding + hr_crop_size]

                    data1.append(data1_tmp.numpy())
                    data2.append(data2_tmp.numpy())
                    labels.append(label_tmp.numpy())

        data1 = np.array(data1)
        data2 = np.array(data2)
        labels = np.array(labels)
        
        np.save(self.data1_file, data1)
        np.save(self.data2_file, data2)
        np.save(self.labels_file, labels)

    def load_data(self):
        if not exists(self.data1_file):
            raise ValueError(f"\n{self.data1_file}, {self.data2_file}, и {self.labels_file} не существуют\n")
        self.data1 = np.load(self.data1_file)
        self.data1 = torch.as_tensor(self.data1)

        self.data2 = np.load(self.data2_file)
        self.data2 = torch.as_tensor(self.data2)

        self.labels = np.load(self.labels_file)
        self.labels = torch.as_tensor(self.labels)
    
    def get_batch(self, batch_size, shuffle_each_epoch=True):
        isEnd = False
        if self.cur_idx + batch_size > self.data1.shape[0]:
            isEnd = True
            self.cur_idx = 0
            if shuffle_each_epoch:
                self.data1, self.data2, self.labels = shuffle(self.data1, self.data2, self.labels)
        
        data1 = self.data1[self.cur_idx : self.cur_idx + batch_size]
        data2 = self.data2[self.cur_idx: self.cur_idx + batch_size]
        labels = self.labels[self.cur_idx : self.cur_idx + batch_size]
        self.cur_idx += batch_size
        
        return data1, data2, labels, isEnd
