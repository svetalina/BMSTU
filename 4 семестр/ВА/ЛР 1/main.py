import sys

ERROR_NEGATIVE_POWER = 1
ERROR_BIG_POWER = 2
ERROR_NOT_NUMBER = 3

matrix = [[0.00, 1.000000, -1.000000],
          [0.15, 0.838771, -1.14944],
          [0.30, 0.655336, -1.29552],
          [0.45, 0.450447, -1.43497],
          [0.60, 0.225336, -1.56464],
          [0.75, -0.018310, -1.68164],
          [0.90, -0.278390, -1.78333],
          [1.05, -0.552430, -1.86742]]

EPS = 1e-6

def print_matrix():
    print("{:^10}{:^10}{:^10}".format("x", "y", "y'"))

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print("%-10f" % (matrix[i][j]), end=' ')
        print()
    print()


def read_data():
    try:
        n = int(input("Введите степень аппроксимирующего полинома: "))

        if (n <= 0):
            print("Ошибка: Степень полинома должна быть положительным числом")
            return ERROR_NEGATIVE_POWER, 0, 0

        if (n >= len(matrix)):
            print("Ошибка: Cтепень полинома должна быть меньше, чем количество элементов в таблице")
            return ERROR_BIG_POWER, 0, 0

        x = float(input("Введите значение аргумента, для которого выполняется интерполяция: "))
        return 0, n, x

    except:
        print("Ошибка: введенные данные не являются числами")
        return ERROR_NOT_NUMBER, 0, 0


def create_table():
    table = [[0] * len(matrix[0]) for i in range(len(matrix))]
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            table[i][j] = matrix[i][j]

    return table


def find_range(table, n, x):
    index = -1

    for str in table:
        if (str[0] > x):
            break
        index += 1

    if index <= n // 2:
        return 0
    if index >= len(table) - 1 - n // 2:
        return len(table) - n

    if x - table[index][0] < EPS:
        return index - n // 2

    if x - table[index][0] < x - table[index + 1][0]:
        return index - n // 2
    return index - n // 2 + 1


def divided_difference(x0, y0, x1, y1, y_derivative):
    if abs(x0 - x1) > EPS:
        return (y0 - y1) / (x0 - x1)
    else:
        return y_derivative


def newton_polynomial(table, n, x):
    index = find_range(table, n, x)
    value_np = table[index][1]

    for i in range(n):
        for j in range(n - i):
            table[index + j][1] = divided_difference(
                table[index + j][0], table[index + j][1],
                table[index + j + i + 1][0], table[index + j + 1][1], table[index + j][2])

        mul = 1
        for j in range(i + 1):
            mul *= (x - table[index + j][0])

        mul *= table[index][1]
        value_np += mul

    return value_np


def hermit_polynomial(table, n, x):
    for i in range(0, len(table) * 2, 2):
        table.insert(i + 1, table[i][:])

    return newton_polynomial(table, n, x)


def find_root(table, n, x):
    table.sort(key=lambda array: array[1])
    for str in table:
        str[0], str[1] = str[1], str[0]

    return newton_polynomial(table, n, x)


print_matrix()

rc, n, x = read_data()
if (rc):
    sys.exit(rc)

value_np = newton_polynomial(create_table(), n, x)
value_hp = hermit_polynomial(create_table(), n, x)

value_root = find_root(create_table(), n, 0)

print("\nЗначение полинома Ньютона для x = %.4f  = %.6f" % (x, value_np))
print("Значение полинома Эрмита для x = %.4f  = %.6f" % (x, value_hp))

print("\nЗначение корня функции = %.6f" % (value_root))
