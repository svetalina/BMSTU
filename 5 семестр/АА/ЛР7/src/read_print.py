import numpy as np

from color import base_color, red, purple

MSG = "\n\t\tМеню:\n"\
      "1. Полный перебор \n"\
      "2. Муравьиный алгоритм \n"\
      "3. Параметризация \n"\
      "4. Замеры времени \n"\
      "0. Выход \n\n"\
      "Выбор: "\


def read_command():
    try:
        command = int(input(MSG))
    except:
        command = -1
    
    if command < 0 or command > 4:
        print("%s\nОшибка: введено не целое число от 0 до 4 %s"
            %(red, base_color))

    return command


def read_matrix():
    filename = input("Введите имя файла: ")
    try:
        file = open(filename, "r")

        size = len(file.readline().split())
        matrix = np.zeros((size, size), dtype=int)

        file.seek(0)

        i = 0
        for line in file.readlines():
            j = 0
            for num in line.split():
                matrix[i][j] = int(num)
                j += 1
            i += 1

        file.close()

        print("\n%sМатрица смежности:%s" %(purple, base_color))
        for i in range(size):
            for j in range(size):
                print("%5d" %(matrix[i][j]), end=" ")
            print("")

    except:
        size = 0
        matrix = [[]]
        print("%s\nОшибка: невозможно прочитать данные файла %s"
              % (red, base_color))

    return size, matrix


def read_koefs():
    
    try:
        alpha = float(input("\n%sВведите коэффициент alpha: %s" % (purple, base_color)))
        beta = beta = 1 - alpha
        print("%sКоэффициент beta: %.2f %s" % (purple, beta, base_color))
        evaporation = float(input("%sВведите коэффициент evaporation: %s" % (purple, base_color)))
        days = int(input("%sВведите количество дней: %s" % (purple, base_color)))
    except:
        print("\n%sОшибка: введены неверные коэффициенты %s" % (red, base_color))
        alpha = beta = evaporation = days = 0

    return alpha, beta, evaporation, days
