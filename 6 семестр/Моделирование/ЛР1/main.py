from tabulate import tabulate
import math


def function_1_analytical(y):
    return 3 * math.exp(y) - y * y - 2 * y - 2


def function_1_euler(y, x):
    return y * y + x


def function_1_picard_1(y):
    return pow(y, 3) / 3 + 1


def function_1_picard_2(y):
    return pow(y, 4) / 12 + pow(y, 3) / 3 + y + 1


def function_1_picard_3(y):
    return pow(y, 5) / 60 + pow(y, 4) / 12 + pow(y, 3) / 3 + pow(y, 2) / 2 + y + 1


def function_1_picard_4(y):
    return pow(y, 6) / 360 + pow(y, 5) / 60 + pow(y, 4) / 12 + pow(y, 3) / 3 + pow(y, 2) / 2 + y + 1


def function_2_analytical(y):
    return math.exp(y * y) - y * y / 2 - 1 / 2


def function_2_euler(y, x):
    return y * y * y + 2 * x * y


def function_2_picard_1(y):
    return 0.5 + pow(y, 2) / 2 + pow(y, 4) / 4


def function_2_picard_2(y):
    return 0.5 + pow(y, 2) / 2 + pow(y, 4) / 2 + pow(y, 6) / 12


def function_2_picard_3(y):
    return 0.5 + pow(y, 2) / 2 + pow(y, 4) / 2 + pow(y, 6) / 6 + pow(y, 8) / 48


def function_2_picard_4(y):
    return 0.5 + pow(y, 2) / 2 + pow(y, 4) / 2 + pow(y, 6) / 6 + pow(y, 8) / 24 + pow(y, 10) / 240


def function_3_euler(x, y):
    return x * x + y * y


def function_3_picard_1(x):
    return pow(x, 3) / 3


def function_3_picard_2(x):
    return pow(x, 3) / 3 + pow(x, 7) / 63


def function_3_picard_3(x):
    return pow(x, 3) / 3 + pow(x, 7) / 63 + 2 * pow(x, 11) / 2079 + pow(x, 15) / 59535


def function_3_picard_4(x):
    return pow(x, 3) / 3 + \
           pow(x, 7) / 63 + \
           2 * pow(x, 11) / 2079 + \
           13 * pow(x, 15) / 218295 + \
           82 * pow(x, 19) / 37328445 + \
           2 * pow(x, 23) / 86266215 + \
           4 * pow(x, 23) / 99411543 + \
           pow(x, 31) / 109876902975 + \
           4 * pow(x, 27) / 3341878155





def euler_solve(function, arg0, val0, begin, end, step):
    answers = []
    i = begin
    argi = arg0
    vali = val0
    answers.append(vali)
    while i <= end:
        fi = function(argi, vali)
        hf = step * fi
        i += step
        argi = i
        vali = vali + hf
        answers.append(vali)

    return answers


def euler_improved_solve(function, arg0, val0, begin, end, step):
    answers = []
    i = begin
    argi = arg0
    vali = val0
    answers.append(vali)
    while i <= end:
        arg_mid = argi + step / 2
        fi = function(argi, vali)
        val_mid = vali + step / 2 * fi
        fi = function(arg_mid, val_mid)
        fi *= step
        vali = vali + fi
        answers.append(vali)

        i += step
        argi = i

    return answers


def get_limit_euler_analyt(function, analyt_function, arg0, val0, begin, accuracy, step):
    answers = []
    i = begin
    argi = arg0
    vali = val0
    value = vali
    analyt_value = analyt_function(argi)
    while abs(value - analyt_value) < accuracy:
        arg_mid = argi + step / 2
        fi = function(argi, vali)
        val_mid = vali + step / 2 * fi
        fi = function(arg_mid, val_mid)
        fi *= step
        value = vali = vali + fi

        i += step
        argi = i

        analyt_value = analyt_function(argi)

    return argi


def get_limit_euler(function, arg0, val0, begin, accuracy, step):
    answers = []
    i = begin
    argi = arg0
    vali1 = vali2 = val0

    val_e = val_ei = val0

    while abs(val_e - val_ei) < accuracy:
        fi1 = function(argi, vali1)
        hf = step * fi1
        vali1 = vali1 + hf
        val_e = vali1

        arg_mid = argi + step / 2
        fi2 = function(argi, vali2)
        val_mid = vali2 + step / 2 * fi2
        fi2 = function(arg_mid, val_mid)
        fi2 *= step
        vali2 = vali2 + fi2
        val_ei = vali2

        i += step
        argi = i

    return argi


def menu():
    selected = False
    choice = -1

    while not selected:
        try:
            choice = int(input("Выберите ОДУ:\n"
                                   "1) (u^2+x)u'=1\n"
                                   "    u(1)=0\n\n"
                                   "2) 1-2xuu'=u^3u'\n"
                                   "   u(0.5)=0\n\n"
                                   "3) u'(x)=x^2+u^2\n"
                                   "   u(0)=0\n\n"
                                   "4) Завершить программу\n\n"
                                   "Выбор: "))

            if 0 < choice < 5:
                selected = True
            else:
                print("Неверно выбрана опция")
        except ValueError:
            print("Неверный формат ввода данных")
            selected = False

    return choice


def create_table(headers, data):
    print(tabulate(data, headers=headers, tablefmt="grid"))


if __name__ == "__main__":
    finish = False
    while not finish:
        choice = menu()

        if choice == 1:
            argument = "y"
            value = "x"

            arg_begin = 0
            val_begin = 1

            function_euler = function_1_euler
            function_analytical = function_1_analytical

            print("Начальное значение аргумента " + argument + ": " + str(arg_begin))
            arg_step = float(input("Введите шаг аргумента " + argument + ": "))

            choice = int(input("Выбрать конечное значение автоматически, чтобы обеспечить точность до 2х знаков после запятой?\n"
                               "1) Да\n"
                               "2) Нет\n"))

            if choice == 2:
                arg_end = float(input("Введите конечное значение аргумента " + argument + ": "))
            else:
                arg_end = get_limit_euler_analyt(function_euler, function_1_analytical, arg_begin, val_begin, arg_begin, 0.001, arg_step)
                print("Конечное значение аргумента определено: " + str(arg_end))

            function_picard_1 = function_1_picard_1
            function_picard_2 = function_1_picard_2
            function_picard_3 = function_1_picard_3
            function_picard_4 = function_1_picard_4

            headers = ["Аргумент " + argument + ": ",
                       "Аналитическое решение",
                       "Метод Эйлера",
                       "Метод Эйлера улучшенный",
                       "1-е приближение Пикара",
                       "2-е приближение Пикара",
                       "3-е приближение Пикара",
                       "4-е приближение Пикара"]

            data = []
            euler_answers = euler_solve(function_euler, arg_begin, val_begin, arg_begin, arg_end, arg_step)
            euler_improved_answers = euler_improved_solve(function_euler, arg_begin, val_begin, arg_begin, arg_end, arg_step)
            i = arg_begin
            counter = 0
            while i <= arg_end:
                data.append([i,
                             function_analytical(i),
                             euler_answers[counter],
                             euler_improved_answers[counter],
                             function_picard_1(i),
                             function_picard_2(i),
                             function_picard_3(i),
                             function_picard_4(i)])
                i += arg_step
                counter += 1
        elif choice == 2:
            argument = "y"
            value = "x"

            arg_begin = 0
            val_begin = 0.5

            function_euler = function_2_euler
            function_analytical = function_2_analytical

            print("Начальное значение аргумента " + argument + ": " + str(arg_begin))
            arg_step = float(input("Введите шаг аргумента " + argument + ": "))

            choice = int(input("Выбрать конечное значение автоматически, чтобы обеспечить точность до 2х знаков после запятой?\n"
                               "1) Да\n"
                               "2) Нет\n"))

            if choice == 2:
                arg_end = float(input("Введите конечное значение аргумента " + argument + ": "))
            else:
                arg_end = get_limit_euler_analyt(function_euler, function_2_analytical, arg_begin, val_begin, arg_begin, 0.001, arg_step)
                print("Конечное значение аргумента определено: " + str(arg_end))

            function_picard_1 = function_2_picard_1
            function_picard_2 = function_2_picard_2
            function_picard_3 = function_2_picard_3
            function_picard_4 = function_2_picard_4

            headers = ["Аргумент " + argument + ": ",
                       "Аналитическое решение",
                       "Метод Эйлера",
                       "Метод Эйлера улучшенный",
                       "1-е приближение Пикара",
                       "2-е приближение Пикара",
                       "3-е приближение Пикара",
                       "4-е приближение Пикара"]

            data = []
            euler_answers = euler_solve(function_euler, arg_begin, val_begin, arg_begin, arg_end, arg_step)
            euler_improved_answers = euler_improved_solve(function_euler, arg_begin, val_begin, arg_begin, arg_end, arg_step)
            i = arg_begin
            counter = 0
            while i <= arg_end:
                data.append([i,
                             function_analytical(i),
                             euler_answers[counter],
                             euler_improved_answers[counter],
                             function_picard_1(i),
                             function_picard_2(i),
                             function_picard_3(i),
                             function_picard_4(i)])
                i += arg_step
                counter += 1
        elif choice == 3:
            argument = "x"
            value = "y"

            arg_begin = 0
            val_begin = 0

            function_euler = function_3_euler

            print("Начальное значение аргумента " + argument + ": " + str(arg_begin))
            arg_step = float(input("Введите шаг аргумента " + argument + ": "))
            choice = int(input("Выбрать конечное значение автоматически, чтобы обеспечить точность до 2х знаков после запятой?\n"
                               "1) Да\n"
                               "2) Нет\n"))

            if choice == 2:
                arg_end = float(input("Введите конечное значение аргумента " + argument + ": "))
            else:
                arg_end = get_limit_euler(function_euler, arg_begin, val_begin, arg_begin, 0.001, arg_step)
                print("Конечное значение аргумента определено: " + str(arg_end))

            function_picard_1 = function_3_picard_1
            function_picard_2 = function_3_picard_2
            function_picard_3 = function_3_picard_3
            function_picard_4 = function_3_picard_4

            headers = ["Аргумент " + argument + ": ",
                       "Метод Эйлера",
                       "Метод Эйлера улучшенный",
                       "1-е приближение Пикара",
                       "2-е приближение Пикара",
                       "3-е приближение Пикара",
                       "4-е приближение Пикара"]

            data = []
            euler_answers = euler_solve(function_euler, arg_begin, val_begin, arg_begin, arg_end, arg_step)
            euler_improved_answers = euler_improved_solve(function_euler, arg_begin, val_begin, arg_begin, arg_end, arg_step)
            i = arg_begin
            counter = 0
            while i <= arg_end:
                data.append([i,
                             euler_answers[counter],
                             euler_improved_answers[counter],
                             function_picard_1(i),
                             function_picard_2(i),
                             function_picard_3(i),
                             function_picard_4(i)])
                i += arg_step
                counter += 1
        elif choice == 4:
            finish = True
            break
        else:
            print("Операция выбрана неверно")
            choice = menu()

        create_table(headers, data)