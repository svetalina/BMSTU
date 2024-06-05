from tkinter import *
from tkinter import messagebox
from math import pi, sqrt
import matplotlib.pyplot as plt

FAIL = -1
SUCCESS = 0

WINDOW_WIDTH = 700
WINDOW_HEIGHT = 600

numb_points = 0


def task():
    messagebox.showinfo("Условие задачи", "На плоскости дано множество точек. "
                                          "Найти такой треугольник с вершинами в этих точках, "
                                          "у которого разность площадей описанного круга и треугольника максимальна.")


def read_numb_points():
    global numb_points
    try:
        numb_points = int(point_txt.get())

        if numb_points < 3 or numb_points > 10:
            messagebox.showerror("Ошибка",
                                 "Количество точек должно быть число от 3 до 10")
            return
    except:
        messagebox.showerror("Ошибка",
                             "Количество точек должно быть целое положительное число")
        return

    enter_points()
    # point_list[0][1].focus()


def enter_points():
    global numb_points
    clear_table()

    for i in range(numb_points):
        point_list[i][0] = Label(window, text=str(i + 1) + ") ", font=("Courier New", 13))
        point_list[i][0].place(width=40, height=30, x=15, y=140 + i * 40)

        point_list[i][1] = Entry(window, font=("Courier New", 13))
        point_list[i][1].place(width=90, height=30, x=65, y=140 + i * 40)

        point_list[i][2] = Entry(window, font=("Courier New", 13))
        point_list[i][2].place(width=90, height=30, x=185, y=140 + i * 40)


def add_point():
    global numb_points

    if numb_points < 10:
        i = numb_points
        numb_points += 1

        point_list[i][0] = Label(window, text=str(i + 1) + ") ", font=("Courier New", 13))
        point_list[i][0].place(width=40, height=30, x=15, y=140 + i * 40)

        point_list[i][1] = Entry(window, font=("Courier New", 13))
        point_list[i][1].place(width=90, height=30, x=65, y=140 + i * 40)

        point_list[i][2] = Entry(window, font=("Courier New", 16))
        point_list[i][2].place(width=90, height=30, x=185, y=140 + i * 40)

        point_list[i][1].focus()

        point_txt.delete(0, END)
        point_txt.insert(0, str(numb_points))

    else:
        messagebox.showwarning("Предупреждение",
                               "Количество точек должно быть меньше или равно 10")


def del_point():
    global numb_points

    if numb_points == 0:
        messagebox.showwarning("Предупреждение", "Для удаления необходимо иметь хотя бы одну точку")
        return

    if numb_points == 3:
        messagebox.showwarning("Предупреждение", "Количество точек не может быть меньше 3")
        return

    try:
        number = int(del_point_txt.get())

        if number < 1 or number > numb_points:
            messagebox.showerror("Ошибка",
                                 "Номер удаляемой точки должен быть числом от 1 до %d." % (numb_points))
            return
    except:
        messagebox.showerror("Ошибка",
                             "Номер удаляемой точки должен быть целым положительным числом")
        return

    points_str_array = []

    for i in range(numb_points):
        if i + 1 != number:
            points_str_array.append([point_list[i][1].get(), point_list[i][2].get()])

    numb_points -= 1

    clear_table()
    enter_points()

    for i in range(numb_points):
        point_list[i][1].insert(0, points_str_array[i][0])
        point_list[i][2].insert(0, points_str_array[i][1])

    point_txt.delete(0, END)
    point_txt.insert(0, str(numb_points))


def clear_table():
    numb_points = 0
    for i in range(10):
        point_list[i][0].place_forget()
        point_list[i][1].place_forget()
        point_list[i][2].place_forget()


def clear_canvas():
    clear_table()
    point_txt.delete(0, END)
    del_point_txt.delete(0, END)


def get_coord():
    global coord_points

    coord_points = [[0 for i in range(2)] for j in range(numb_points)]
    for i in range(numb_points):
        try:
            coord_points[i][0] = float(point_list[i][1].get())
            coord_points[i][1] = float(point_list[i][2].get())
        except:
            messagebox.showerror("Ошибка",
                                 "Координаты точек должны быть рационалными числами")
            return FAIL

    return SUCCESS


def count_side_lengths(x1, y1, x2, y2, x3, y3):
    len_12 = sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    len_23 = sqrt((x2 - x3) ** 2 + (y2 - y3) ** 2)
    len_31 = sqrt((x3 - x1) ** 2 + (y3 - y1) ** 2)

    return len_12, len_23, len_31


def count_square(len_12, len_23, len_31):
    p = (len_12 + len_23 + len_31) / 2
    S = sqrt(p * (p - len_12) * (p - len_23) * (p - len_31))

    return S


def count_radius(len_12, len_23, len_31, S):
    R = (len_12 * len_23 * len_31) / (4 * S)
    return R


def max_defference():
    global coord_points

    max = -1e10
    max_S_circle = 0
    max_S_triangle = 0
    max_ind = [0, 0, 0]
    for i in range(numb_points):
        for j in range(i + 1, numb_points):
            for k in range(j + 1, numb_points):
                x1 = coord_points[i][0]; y1 = coord_points[i][1]
                x2 = coord_points[j][0]; y2 = coord_points[j][1]
                x3 = coord_points[k][0]; y3 = coord_points[k][1]

                len_12, len_23, len_31 = count_side_lengths(x1, y1, x2, y2, x3, y3)
                S_triangle = count_square(len_12, len_23, len_31)

                if S_triangle < 1e-3:
                    continue

                R = count_radius(len_12, len_23, len_31, S_triangle)
                S_circle = pi * R ** 2

                if S_circle - S_triangle > max:
                    max = S_circle - S_triangle
                    max_S_circle = S_circle
                    max_S_triangle = S_triangle
                    max_ind = [i, j, k]

    if max == -1e10:
        messagebox.showwarning("Ошибка",
                             "Среди заданных точек нет треугольник, то есть все вырождены")
        return FAIL, FAIL, FAIL

    return max_S_circle, max_S_triangle, max_ind


def process_max_defference():
    if numb_points == 0:
        messagebox.showerror("Ошибка",
                             "Количество точек должно быть больше 0")
        return

    S_circle, S_triangle, ind = max_defference()

    return S_circle, S_triangle, ind


def build_triangle_circle():
    if get_coord() == FAIL:
        return

    S_circle, S_triangle, ind = process_max_defference()
    if S_circle < 0:
        return

    # Треугольник
    x1 = coord_points[ind[0]][0]; x2 = coord_points[ind[1]][0]; x3 = coord_points[ind[2]][0]
    y1 = coord_points[ind[0]][1]; y2 = coord_points[ind[1]][1]; y3 = coord_points[ind[2]][1]

    line_x_123 = []; line_y_123 = []
    line_x_123.append(x1)
    line_x_123.append(x2)
    line_x_123.append(x3)
    line_y_123.append(y1)
    line_y_123.append(y2)
    line_y_123.append(y3)

    line_x_13 = []; line_y_13 = []
    line_x_13.append(x1)
    line_x_13.append(x3)
    line_y_13.append(y1)
    line_y_13.append(y3)

    # Круг
    len_12, len_23, len_31 = count_side_lengths(x1, y1, x2, y2, x3, y3)
    R = count_radius(len_12, len_23, len_31, S_triangle)

    K = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2))
    x_center = ((x1 ** 2 + y1 ** 2) * (y2 - y3) + (x2 ** 2 + y2 ** 2) * (y3 - y1) + (x3 ** 2 + y3 ** 2) * (y1 - y2)) / K
    y_center = ((x1 ** 2 + y1 ** 2) * (x3 - x2) + (x2 ** 2 + y2 ** 2) * (x1 - x3) + (x3 ** 2 + y3 ** 2) * (x2 - x1)) / K

    ax = plt.gca()
    ax.clear()
    ax.set_aspect("equal")
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.spines['bottom'].set_position(('data', 0))
    ax.spines['left'].set_position(('data', 0))

    circle1 = plt.Circle((0, 0), radius=0.01, color="black", fill=True)
    ax.add_patch(circle1)

    plt.grid()

    plt.plot(line_x_123, line_y_123, color="blue")
    plt.plot(line_x_13, line_y_13, color="blue")

    plt.annotate("%d (%.2f, %.2f)" % (ind[0] + 1, x1, y1), xy=(x1, y1))
    plt.annotate("%d (%.2f, %.2f)" % (ind[1] + 1, x2, y2), xy=(x2, y2))
    plt.annotate("%d (%.2f, %.2f)" % (ind[2] + 1, x3, y3), xy=(x3, y3))

    circle = plt.Circle((x_center, y_center), radius=R, color="red", fill=False)
    ax.add_patch(circle)

    plt.show()


def print_results():
    if get_coord() == FAIL:
        return

    S_circle, S_triangle, ind = process_max_defference()
    if S_circle < 0:
        return

    messagebox.showinfo("Результаты работы программы",
                        "Треугольник с максимальной разностью данных площадей образуется точками %d, %d, %d \n"
                        "Кординаты точек (%.3f,  %.3f) (%.3f,  %.3f) (%.3f,  %.3f) \n"
                        "Площадь описанного круга = %.3f\n"
                        "Площадь треугольника = %.3f"
                        % (ind[0] + 1, ind[1] + 1, ind[2] + 1, coord_points[ind[0]][0], coord_points[ind[0]][1],
                           coord_points[ind[1]][0], coord_points[ind[1]][1], coord_points[ind[2]][0],
                           coord_points[ind[2]][1], S_circle, S_triangle))


window = Tk()
window.title('Лабораторная работа №1')
window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
window.resizable(False, False)

# Количество точек
Label(window, height=2, text="Количество точек:",
      font=("Courier New", 13)).place(x=10, y=10)
point_txt = Entry(window, font=("Courier New", 16))
point_txt.place(width=180, height=40, x=205, y=10)
point_txt.focus()
Button(text="Применить", font=("Courier New", 13), command=read_numb_points). \
    place(width=180, height=40, x=400, y=10)

# Поле для ввода точек
Entry(window, font=("Courier New", 15), bd=3, state=DISABLED). \
    place(width=285, height=50, x=10, y=70)

Label(window, text=" №     X        Y    ", font=("Courier New", 18)). \
    place(width=270, height=40, x=20, y=75)

Entry(window, font=("Courier New", 16), bd=3, state=DISABLED). \
    place(width=285, height=420, x=10, y=120)

point_1_lbl = Label(); point_1x_txt = Entry(); point_1y_txt = Entry()
point_2_lbl = Label(); point_2x_txt = Entry(); point_2y_txt = Entry()
point_3_lbl = Label(); point_3x_txt = Entry(); point_3y_txt = Entry()
point_4_lbl = Label(); point_4x_txt = Entry(); point_4y_txt = Entry()
point_5_lbl = Label(); point_5x_txt = Entry(); point_5y_txt = Entry()
point_6_lbl = Label(); point_6x_txt = Entry(); point_6y_txt = Entry()
point_7_lbl = Label(); point_7x_txt = Entry(); point_7y_txt = Entry()
point_8_lbl = Label(); point_8x_txt = Entry(); point_8y_txt = Entry()
point_9_lbl = Label(); point_9x_txt = Entry(); point_9y_txt = Entry()
point_10_lbl = Label(); point_10x_txt = Entry(); point_10y_txt = Entry()

point_list = [[point_1_lbl, point_1x_txt, point_1y_txt], [point_2_lbl, point_2x_txt, point_2y_txt],
              [point_3_lbl, point_3x_txt, point_3y_txt], [point_4_lbl, point_4x_txt, point_4y_txt],
              [point_5_lbl, point_5x_txt, point_5y_txt], [point_6_lbl, point_6x_txt, point_6y_txt],
              [point_7_lbl, point_7x_txt, point_7y_txt], [point_8_lbl, point_8x_txt, point_8y_txt],
              [point_9_lbl, point_9x_txt, point_9y_txt], [point_10_lbl, point_10x_txt, point_10y_txt]]

# Добавить точку
Button(text="Добавить\nточку", font=("Courier New", 13), command=add_point). \
    place(width=120, height=50, x=295, y=405)

# Удалить точку
Button(text="Удалить\nточку", font=("Courier New", 13), command=del_point). \
    place(width=120, height=50, x=425, y=405)
Label(window, text="Номер удаляемой точки:", font=("Courier New", 13)). \
    place(height=50, x=305, y=460)
del_point_txt = Entry(window, font=("Courier New", 13))
del_point_txt.place(width=250, height=40, x=295, y=500)

Button(text="Условие задачи", font=("Courier New", 13), command=task). \
    place(width=230, height=40, x=305, y=75)

Button(text="Вывести изображение", font=("Courier New", 13), command=build_triangle_circle). \
    place(width=230, height=40, x=305, y=125)

Button(text="Вывести результаты", font=("Courier New", 13), command=print_results). \
    place(width=230, height=40, x=305, y=175)

Button(text="Очистить все поля", font=("Courier New", 13), command=clear_canvas). \
    place(width=230, height=40, x=305, y=225)

window.mainloop()
