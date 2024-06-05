from architecture import SRCNN_architecture
from utils import *

import numpy as np
import os
import torch


class SRCNN:
    def __init__(self, architecture, device):
        self.device = device
        self.model = SRCNN_architecture(architecture).to(device)
        self.optimizer = None
        self.loss = None
        self.metric = None
        self.model_path = None
        self.ckpt_path = None
        self.ckpt_man = None

    def setup(self, optimizer, loss, metric, model_path, ckpt_path):
        self.optimizer = optimizer
        self.loss = loss
        self.metric = metric
        self.model_path = model_path
        self.ckpt_path = ckpt_path

    def load_checkpoint(self, ckpt_path):
        if not exists(ckpt_path):
            return
        self.ckpt_man = torch.load(ckpt_path)
        self.optimizer.load_state_dict(self.ckpt_man['optimizer'])
        self.model.load_state_dict(self.ckpt_man['model'])

    def load_weights(self, filepath):
        self.model.load_state_dict(torch.load(filepath, map_location=torch.device(self.device)))

    def predict(self, lr1, lr2):
        self.model.train(False)
        sr = self.model(lr1, lr2)
        return sr

    def evaluate(self, dataset, batch_size=64):
        losses, metrics = [], []
        isEnd = False
        while isEnd == False:
            lr1, lr2, hr, isEnd = dataset.get_batch(batch_size, shuffle_each_epoch=False)
            lr1, lr2, hr = lr1.to(self.device), lr2.to(self.device), hr.to(self.device)
            sr = self.predict(lr1, lr2)
            loss = self.loss(hr, sr)
            metric = self.metric(hr, sr)
            losses.append(tensor2numpy(loss))
            metrics.append(tensor2numpy(metric))

        metric = np.mean(metrics)
        loss = np.mean(losses)
        return loss, metric

    def train(self, train_set, valid_set, batch_size, steps, save_every, ckpt_dir):
        os.makedirs(ckpt_dir, exist_ok=True)

        cur_step = 0
        if self.ckpt_man is not None:
            cur_step = self.ckpt_man['step']
        max_steps = cur_step + steps

        loss_buffer = []
        metric_buffer = []
        while cur_step < max_steps:
            cur_step += 1
            lr1, lr2, hr, _ = train_set.get_batch(batch_size)
            loss, metric = self.train_step(lr1, lr2, hr)
            loss_buffer.append(tensor2numpy(loss))
            metric_buffer.append(tensor2numpy(metric))

            if (cur_step % save_every == 0) or (cur_step >= max_steps):
                loss = np.mean(loss_buffer)
                metric = np.mean(metric_buffer)
                val_loss, val_metric = self.evaluate(valid_set)
                print(f"Step {cur_step}/{max_steps}",
                      f"- loss: {loss:.7f}",
                      f"- {self.metric.__name__}: {metric:.3f}",
                      f"- val_loss: {val_loss:.7f}",
                      f"- val_{self.metric.__name__}: {val_metric:.3f}")

                loss_buffer = []
                metric_buffer = []
                torch.save({'step': cur_step,
                            'model': self.model.state_dict(),
                            'optimizer': self.optimizer.state_dict()
                            }, self.ckpt_path)

                torch.save(self.model.state_dict(), self.model_path)
                print(f"Save model to {self.model_path}\n")

    def train_step(self, lr1, lr2, hr):
        self.model.train(True)
        self.optimizer.zero_grad()

        lr1, lr2, hr = lr1.to(self.device), lr2.to(self.device), hr.to(self.device)
        sr = self.model(lr1, lr2)

        loss = self.loss(hr, sr)
        metric = self.metric(hr, sr)
        loss.backward()
        self.optimizer.step()

        return loss, metric