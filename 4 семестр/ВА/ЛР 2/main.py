SUCCESS = 0
ERROR = -1

EPS = 1e-6


def print_table(table):
    symbol = '-'
    print(symbol.center(10 * len(table) + 1, '-'))
    for i in range(len(table)):
        print("|", end='')
        for j in range(len(table[i])):
            print("{:^9.2f}|".format(table[i][j]), end='')
        print()
        print(symbol.center(10 * len(table) + 1, '-'))


def read_data(size_table):
    try:
        nx = int(input("Введите степень аппроксимирующего полинома - nx: "))

        if (nx <= 0):
            print("Степень аппроксимирующего полинома nx должна быть больше 0")
            return ERROR, 0, 0, 0, 0, 0, 0
        elif (nx >= size_table):
            print("Степень аппроксимирующего полинома nx должна быть меньше размерности таблицы")
            return ERROR, 0, 0, 0, 0, 0, 0

        ny = int(input("Введите степень аппроксимирующего полинома - ny: "))

        if (ny <= 0):
            print("Степень аппроксимирующего полинома ny должна быть больше 0")
            return ERROR, 0, 0, 0, 0, 0, 0
        elif (ny >= size_table):
            print("Степень аппроксимирующего полинома ny должна быть меньше размерности таблицы")
            return ERROR, 0, 0, 0, 0, 0, 0

        nz = int(input("Введите степень аппроксимирующего полинома - nz: "))

        if (nz <= 0):
            print("Степень аппроксимирующего полинома nz должна быть больше 0")
            return ERROR, 0, 0, 0, 0, 0, 0
        elif (nz >= size_table):
            print("Степень аппроксимирующего полинома nz должна быть меньше размерности таблицы")
            return ERROR, 0, 0, 0, 0, 0, 0

        try:
            x = float(input("\nВведите x, для которого выполняется интерполяция: "))
            y = float(input("Введите y, для которого выполняется интерполяция: "))
            z = float(input("Введите z, для которого выполняется интерполяция: "))
        except:
            print("Введенные значения должны быть числами")
            return ERROR, 0, 0, 0, 0, 0, 0

        return SUCCESS, nx, ny, nz, x, y, z

    except:
        print("Введенные значения должны быть целыми числами")
        return ERROR, 0, 0, 0, 0, 0, 0


def find_range(table, n, x):
    index = -1

    for str in table:
        if str[0] > x:
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


def divided_difference(x0, y0, x1, y1):
    if abs(x0 - x1) > EPS:
        return (y0 - y1) / (x0 - x1)


def newton_polynomial(table, n, x):
    index = find_range(table, n + 1, x)
    value_np = table[index][1]

    for i in range(n):
        for j in range(n - i):
            table[index + j][1] = divided_difference(
                table[index + j][0], table[index + j][1],
                table[index + j + i + 1][0], table[index + j + 1][1])

        mul = 1
        for j in range(i + 1):
            mul *= (x - table[index + j][0])

        mul *= table[index][1]
        value_np += mul

    return value_np


def second_interpolation(table, nx, ny, x, y):
    result = []

    for i in range(len(table)):
        array_tmp = []
        for j in range(len(table)):
            array_tmp.append([j, table[i][j]])

        result.append(newton_polynomial(array_tmp, nx, x))

    array = []
    for i in range(len(table)):
        array.append([i, result[i]])

    return newton_polynomial(array, ny, y)


def third_interpolation(table, nx, ny, nz, x, y, z):
    array = []

    for i in range(len(table)):
        array.append([i, second_interpolation(table[i], nx, ny, x, y)])

    return newton_polynomial(array, nz, z)


def main():
    table_0 = [[0, 1, 4, 9, 16],
               [1, 2, 5, 10, 17],
               [4, 5, 8, 13, 20],
               [9, 10, 13, 18, 25],
               [16, 17, 20, 25, 32]]

    table_1 = [[1, 2, 5, 10, 17],
               [2, 3, 6, 11, 18],
               [5, 6, 9, 14, 21],
               [10, 11, 14, 19, 26],
               [17, 18, 21, 26, 33]]

    table_2 = [[4, 5, 8, 13, 20],
               [5, 6, 9, 14, 21],
               [8, 9, 12, 17, 24],
               [13, 14, 17, 22, 29],
               [20, 21, 24, 29, 36]]

    table_3 = [[9, 10, 13, 18, 25],
               [10, 11, 14, 19, 26],
               [13, 14, 17, 22, 29],
               [18, 19, 22, 27, 34],
               [25, 26, 29, 34, 41]]

    table_4 = [[16, 17, 20, 25, 32],
               [17, 18, 21, 26, 33],
               [20, 21, 24, 29, 36],
               [25, 26, 29, 34, 41],
               [32, 33, 36, 41, 48]]

    table = []
    table.append(table_0)
    table.append(table_1)
    table.append(table_2)
    table.append(table_3)
    table.append(table_4)

    for i in range(len(table)):
        print("{:^50s}".format("z = %d" % (i)))
        print_table(table[i])

    rc, nx, ny, nz, x, y, z = read_data(len(table))
    if (rc < 0):
        return

    np = third_interpolation(table, nx, ny, nz, x, y, z)

    print("\nРезультат интерполяции = %.2f\n" % (np))

    print("{:^30s}".format("Таблица интерполяции"))
    for i in range(1, 4):
        table_interpolation = [[0] * 3 for i in range(3)]

        for j in range(1, 4):
            for k in range(1, 4):
                table_interpolation[j - 1][k - 1] = third_interpolation(table, k, j, i, x, y, z)

        print("{:^30s}".format("nz = %d" % (i)))
        print_table(table_interpolation)


if __name__ == "__main__":
    main()
