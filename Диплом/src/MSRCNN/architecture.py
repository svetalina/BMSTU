import torch
import torch.nn as nn
import torch.nn.functional as F

class SRCNN_architecture(nn.Module):
    def __init__(self, architecture) -> None:
        super(SRCNN_architecture, self).__init__()

        self.patch_extraction = nn.Conv2d(in_channels=6, out_channels=64, kernel_size=9)
        nn.init.normal_(self.patch_extraction.weight, mean=0.0, std=0.001)
        nn.init.zeros_(self.patch_extraction.bias)

        self.nonlinear_map = nn.Conv2d(in_channels=64, out_channels=32, kernel_size=architecture)
        nn.init.normal_(self.nonlinear_map.weight, mean=0.0, std=0.001)
        nn.init.zeros_(self.nonlinear_map.bias)

        self.recon = nn.Conv2d(in_channels=32, out_channels=3, kernel_size=5)
        nn.init.normal_(self.recon.weight, mean=0.0, std=0.001)
        nn.init.zeros_(self.recon.bias)

    def forward(self, X1_in, X2_in):
        X_concat = torch.cat((X1_in, X2_in), dim=1)
        X = F.relu(self.patch_extraction(X_concat))
        X = F.relu(self.nonlinear_map(X))
        X = self.recon(X)
        X_out = torch.clip(X, 0.0, 1.0)
        return X_out
