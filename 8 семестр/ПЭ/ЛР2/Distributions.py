
from numpy.random import rayleigh, exponential
import random
import numpy as np
import math

class RayleighDistribution:
    def __init__(self, sigma: float):
        self.sigma = sigma

    def generate(self):
        return rayleigh(self.sigma)