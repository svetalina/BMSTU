import copy

from newton_polynom import newton_polynomial


def calc_A(y_arr):
    return y_arr[:-1]


def calc_C(x_arr, y_arr, table, flag):
    size = len(x_arr)

    C = [0] * (size - 1)

    if (flag == 2 or flag == 3):
        np, np_derivative = newton_polynomial(copy.deepcopy(table), 3, 0)
        C[0] = np_derivative
        # ksi_arr = [0, 1]
        # teta_arr = [0, 0]

    ksi_arr = [0, 0]
    teta_arr = [0, 0]

    for i in range(2, size):
        h1 = x_arr[i] - x_arr[i - 1]
        h2 = x_arr[i - 1] - x_arr[i - 2]

        fi = 3 * ((y_arr[i] - y_arr[i - 1]) / h1 -
                  (y_arr[i - 1] - y_arr[i - 2]) / h2)

        ksi_cur = - h1 / (h2 * ksi_arr[i - 1] + 2 * (h2 + h1))
        teta_cur = (fi - h1 * teta_arr[i - 1]) / (h1 * ksi_arr[i - 1] + 2 * (h2 + h1))



        ksi_arr.append(ksi_cur)
        teta_arr.append(teta_cur)

    C[-1] = teta_arr[-1]

    for i in range(size - 2, 0, -1):
        C[i - 1] = ksi_arr[i] * C[i] + teta_arr[i]

    return C


def calc_B_and_D(x_arr, y_arr, C, table, flag):
    B = []
    D = []

    for i in range(1, len(x_arr) - 1):
        h = x_arr[i] - x_arr[i - 1]

        B.append((y_arr[i] - y_arr[i - 1]) / h - (h * (C[i] + 2 * C[i - 1])) / 3)
        D.append((C[i] - C[i - 1]) / (3 * h))

    h = x_arr[-1] - x_arr[-2]

    B.append((y_arr[-1] - y_arr[-2]) / h - (h * 2 * C[-1]) / 3)

    if flag == 3:
        np, np_derivative = newton_polynomial(copy.deepcopy(table), 3, y_arr[-1])
        D.append(np_derivative - C[-1] / (3 * h))
    else:
        D.append(- C[-1] / (3 * h))

    return B, D


def calculate_koefs_spline(x_arr, y_arr, table, flag):
    A = calc_A(y_arr)
    C = calc_C(x_arr, y_arr, table, flag)
    B, D = calc_B_and_D(x_arr, y_arr, C, table, flag)

    return A, B, C, D


def fined_index(x_arr, x):
    size = len(x_arr)
    index = 1

    while (index < size and x_arr[index] < x):
        index += 1

    return index - 1


def count_polynom(x, x_arr, index, koefs):
    h = x - x_arr[index]
    y = 0

    for i in range(4):
        y += koefs[i][index] * (h ** i)

    return y


def spline(table, x, flag):
    x_arr = [i[0] for i in table]
    y_arr = [i[1] for i in table]

    koefs = calculate_koefs_spline(x_arr, y_arr, table, flag)

    index = fined_index(x_arr, x)

    y = count_polynom(x, x_arr, index, koefs)

    return y
