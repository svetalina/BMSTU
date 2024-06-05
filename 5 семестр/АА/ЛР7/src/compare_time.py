from time import process_time, process_time_ns
import numpy as np
from random import randint

from ant_algorythm import ant_alg
from full_combinations import full_combinations_alg
from color import base_color, purple

def generate_matrix(size, rand_start, rand_end):
    matrix = np.zeros((size, size), dtype = int)

    for i in range(size):
        for j in range(size):
            if (i == j):
                num = 0
            else:
                num = randint(rand_start, rand_end)

            matrix[i][j] = num
            matrix[j][i] = num

    return matrix

def compare_time():
    time_full_combinations = []
    time_ant_algorythm = []

    sizes_arr = [5, 6, 7, 8, 9, 10]

    for size in sizes_arr:

        ##print(size)

        matrix = generate_matrix(size, 1, 2)

        start = process_time_ns()
        full_combinations_alg(matrix, size)
        end = process_time_ns()

        print("Время выполнения алгоритма полного перебора для %d:  %d" % (size, end - start))

        start = process_time_ns()
        ant_alg(matrix, size, 0.5, 0.5, 0.5, 20)
        end = process_time_ns()

        print("Время выполнения муравьиного алгоритма для %d:  %d" % (size, end - start))

        print()
