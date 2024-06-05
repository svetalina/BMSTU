import copy

from newton_polynom import newton_polynomial
from spline import spline

def read_data():
    try:
        x = float(input("Введите значение аргумента, для которого выполняется интерполяция: "))
        return 0, x

    except:
        print("Ошибка ввода данных!\n")
        return 1, 0

def read_flag():
    try:
        flag = int(input("Введите вариант задания условий на границах таблицы от 1 до 3: "))

        if flag < 1 or flag > 3:
            print("Введенный варинт не удовлетворяет промежутку!\n")
            return 1, 0

        return 0, flag

    except:
        print("Ошибка ввода данных!\n")
        return 1, 0

def print_table(table):
    print("\n{:^10}{:^10}\n".format("x", "y"))

    for i in range(len(table)):
        for j in range(len(table[i])):
            print("{:^10.3f}".format(table[i][j]), end = '')
        print()
    print()

def main():
    table = [[0, 0],
              [1, 0.496],
              [2, 0.986],
              [3, 1.102],
              [4, 0.972],
              [5, 0.754],
              [6, 0.539],
              [7, 0.364],
              [8, 0.236],
              [9, 0.148],
              [10, 0.091]]

    # table.sort(key=lambda array: array[0])
    print_table(table)

    rc, x = read_data()
    if (rc):
        return

    rc, flag = read_flag()
    if (rc):
        return

    np, np_derivative = newton_polynomial(copy.deepcopy(table), 3, x)
    spl = spline(table, x, flag)

    print("\nИнтерполяция сплайнами = %.6f" %(spl))
    print("\nИнтреполяция полиномом Ньютона = %.6f\n" %(np))

if __name__ == "__main__":
    main()
