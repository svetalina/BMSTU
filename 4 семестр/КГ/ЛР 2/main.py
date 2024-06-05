from tkinter import Tk, Label, Entry, Button, messagebox, END
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import numpy as np
from math import pi, sin, cos, sqrt

WINDOW_WIDTH = 1200
WINDOW_HEIGHT = 680

PLOT_WIDTH = WINDOW_WIDTH - 300
PLOT_HEIGHT = WINDOW_HEIGHT

ORIGINAL_VALUE_X = 450
ORIGINAL_VALUE_Y = 300

HOME_WIDTH = 300
HOME_HEIGHT = 200

ROOF_HEIGHT = HOME_HEIGHT / 2

WINDOW_RADIUS = HOME_WIDTH / 10

DOOR_WIDTH = HOME_WIDTH / 10
DOOR_HEIGHT = HOME_HEIGHT / 3

ATTIC_SIDE = ROOF_HEIGHT / 2

NUMB_POINTS = 100


def side(x1, y1, x2, y2):
    # Вычисление длины отрезка по координатам
    return sqrt((y2 - y1) ** 2 + (x2 - x1) ** 2)


def rotation():
    global picture, vers_picture

    try:
        angle_rot = float(angle_rotation.get()) * pi / 180
    except:
        messagebox.showwarning("Ошибка",
                               "Неверно задан угол поворота!\n"
                               "Ожидался ввод действительного числа (угол задаётся в градусах).")
        return

    try:
        xc = float(x_center.get())
        yc = float(y_center.get())
    except:
        messagebox.showwarning("Ошибка",
                               "Неверно заданы координаты точки, относительно которой будет производиться "
                               "поворот изображения!\n"
                               "Ожидался ввод действительных чисел.")
        return

    vers_picture.append(copy_picture(picture))
    M_rot = np.array([[cos(angle_rot), -sin(angle_rot)], [sin(angle_rot), cos(angle_rot)]])

    for i in range(len(picture)):
        for j in range(len(picture[i])):
            picture[i][j][0] -= xc
            picture[i][j][1] -= yc

            picture[i][j] = np.dot(M_rot, picture[i][j])

            picture[i][j][0] += xc
            picture[i][j][1] += yc

    draw_picture()


def movement():
    # Перемещение изображения на dx по Ox и dy по Oy
    global picture, vers_picture

    try:
        dx = float(dx_movement.get())
    except:
        messagebox.showwarning("Ошибка",
                               "Неверно задан dx!\n"
                               "Ожидался ввод действительного числа.")
        return

    try:
        dy = float(dy_movement.get())
    except:
        messagebox.showwarning("Ошибка",
                               "Неверно задан dy!\n"
                               "Ожидался ввод действительного числа.")
        return

    vers_picture.append(copy_picture(picture))

    for i in range(len(picture)):
        for j in range(len(picture[i])):
            picture[i][j][0] += dx
            picture[i][j][1] += dy

    draw_picture()


def scaling():
    # Масштабирование изображения относительно заданной точки
    global picture, vers_picture

    try:
        xm = float(x_center.get())
        ym = float(y_center.get())
    except:
        messagebox.showwarning("Ошибка",
                               "Неверно заданы координаты точки, относительно которой будет производиться "
                               "масштабирование изображения!\n"
                               "Ожидался ввод действительных чисел.")
        return

    try:
        kx = float(kx_scal.get())
        ky = float(ky_scal.get())
    except:
        messagebox.showwarning("Ошибка",
                               "Неверно заданы коэффициенты масштабирования изображения!\n"
                               "Ожидался ввод действительных положительных чисел.")
        return

    if kx == 0 or ky == 0:
        messagebox.showwarning("Ошибка",
                               "Коэфициенты масштабирования изображения не может равняться 0!")
        return

    vers_picture.append(copy_picture(picture))

    for i in range(len(picture)):
        for j in range(len(picture[i])):
            picture[i][j][0] = kx * (picture[i][j][0] - xm) + xm 
            picture[i][j][1] = ky * (picture[i][j][1] - ym) + ym

    draw_picture()


def draw_picture():
    clear_picture()

    for i in range(len(picture)):
        if i < 2:
            plt.plot([picture[i][j][0] for j in range(len(picture[i]))],
                     [picture[i][j][1] for j in range(len(picture[i]))], color='#000740')
        elif i < 6:
            plt.plot([picture[i][j][0] for j in range(len(picture[i]))],
                     [picture[i][j][1] for j in range(len(picture[i]))], color='#0084ff')
        else:
            plt.plot([picture[i][0][0], picture[i][2][0]],
                     [picture[i][0][1], picture[i][2][1]], color='#150070')
            plt.plot([picture[i][1][0], picture[i][3][0]],
                     [picture[i][1][1], picture[i][3][1]], color='#1f00ab')

    plt.text(ORIGINAL_VALUE_X - 35, ORIGINAL_VALUE_Y + 10,
             "(%d; %d)" % (ORIGINAL_VALUE_X, ORIGINAL_VALUE_Y), color='#0000ff')
    circal = plt.Circle((ORIGINAL_VALUE_X, ORIGINAL_VALUE_Y), 2.5, color='#0000ff', fill=True)
    ax.add_patch(circal)

    canvas.draw()


def step_back():
    # Откат на 1 шаг назад
    global picture, vers_picture

    if len(vers_picture) > 1:
        picture = copy_picture(vers_picture[-1])
        vers_picture.pop(-1)

        draw_picture()
    else:
        messagebox.showwarning("Ошибка",
                               "Нельзя откатиться дальше начального состояния!")


def starting_position():
    # Откат до исходного положения
    global picture, vers_picture

    if len(vers_picture) > 1:
        vers_picture = [vers_picture[0]]
        picture = copy_picture(vers_picture[0])

        set_initial_values()
        draw_picture()


def clear_picture():
    global ax

    fig.clear()

    ax = fig.add_subplot(111)
    ax.set(facecolor="#ffffff")

    ax.set_xlim([0, PLOT_WIDTH])
    ax.set_ylim([0, PLOT_HEIGHT])

    ax.grid(color="#6972b8", linestyle=':')

    canvas.draw()


def clear_fields():
    x_center.delete(0, END)
    y_center.delete(0, END)
    angle_rotation.delete(0, END)
    dx_movement.delete(0, END)
    dy_movement.delete(0, END)
    kx_scal.delete(0, END)
    ky_scal.delete(0, END)


def set_initial_values():
    clear_fields()

    x_center.insert(0, str(ORIGINAL_VALUE_X))
    y_center.insert(0, str(ORIGINAL_VALUE_Y))

    angle_rotation.insert(0, "0")

    dx_movement.insert(0, "0")
    dy_movement.insert(0, "0")

    kx_scal.insert(0, "1")
    ky_scal.insert(0, "1")

    angle_rotation.focus()


def copy_picture(picture):
    copy_picture = []

    for i in range(len(picture)):
        i_list = []

        for j in range(len(picture[i])):
            j_list = []

            for k in range(len(picture[i][j])):
                j_list.append(picture[i][j][k])

            i_list.append(j_list)

        copy_picture.append(i_list)

    return copy_picture


def create_picture():
    angle_rot = np.linspace(0, 2 * pi, NUMB_POINTS)

    home = []
    x1_home = ORIGINAL_VALUE_X - HOME_WIDTH / 2
    y1_home = ORIGINAL_VALUE_Y - HOME_HEIGHT / 2
    x2_home = ORIGINAL_VALUE_X - HOME_WIDTH / 2
    y2_home = ORIGINAL_VALUE_Y + HOME_HEIGHT / 2
    x3_home = ORIGINAL_VALUE_X + HOME_WIDTH / 2
    y3_home = ORIGINAL_VALUE_Y + HOME_HEIGHT / 2
    x4_home = ORIGINAL_VALUE_X + HOME_WIDTH / 2
    y4_home = ORIGINAL_VALUE_Y - HOME_HEIGHT / 2
    home.append([x1_home, y1_home])
    home.append([x2_home, y2_home])
    home.append([x3_home, y3_home])
    home.append([x4_home, y4_home])
    home.append([x1_home, y1_home])

    roof = []
    x1_roof = x2_home
    y1_roof = y2_home
    x2_roof = ORIGINAL_VALUE_X
    y2_roof = ORIGINAL_VALUE_Y + HOME_HEIGHT / 2 + ROOF_HEIGHT
    x3_roof = x3_home
    y3_roof = y3_home
    roof.append([x1_roof, y1_roof])
    roof.append([x2_roof, y2_roof])
    roof.append([x3_roof, y3_roof])

    attic = []
    attic_center_y = ORIGINAL_VALUE_Y + HOME_HEIGHT / 2 + 2 * ROOF_HEIGHT / 5
    x1_attic = ORIGINAL_VALUE_X - ATTIC_SIDE / 2
    y1_attic = attic_center_y - ATTIC_SIDE / 2
    x2_attic = ORIGINAL_VALUE_X - ATTIC_SIDE / 2
    y2_attic = attic_center_y + ATTIC_SIDE / 2
    x3_attic = ORIGINAL_VALUE_X + ATTIC_SIDE / 2
    y3_attic = attic_center_y + ATTIC_SIDE / 2
    x4_attic = ORIGINAL_VALUE_X + ATTIC_SIDE / 2
    y4_attic = attic_center_y - ATTIC_SIDE / 2
    attic.append([x1_attic, y1_attic])
    attic.append([x2_attic, y2_attic])
    attic.append([x3_attic, y3_attic])
    attic.append([x4_attic, y4_attic])
    attic.append([x1_attic, y1_attic])

    attic_shutters = []
    x1_attic_shutters = ORIGINAL_VALUE_X - ATTIC_SIDE / 2
    y1_attic_shutters = attic_center_y
    x2_attic_shutters = ORIGINAL_VALUE_X
    y2_attic_shutters = attic_center_y + ATTIC_SIDE / 2
    x3_attic_shutters = ORIGINAL_VALUE_X + ATTIC_SIDE / 2
    y3_attic_shutters = attic_center_y
    x4_attic_shutters = ORIGINAL_VALUE_X
    y4_attic_shutters = attic_center_y - ATTIC_SIDE / 2
    attic_shutters.append([x1_attic_shutters, y1_attic_shutters])
    attic_shutters.append([x2_attic_shutters, y2_attic_shutters])
    attic_shutters.append([x3_attic_shutters, y3_attic_shutters])
    attic_shutters.append([x4_attic_shutters, y4_attic_shutters])

    x0_window = ORIGINAL_VALUE_X - HOME_WIDTH / 4
    y0_window = ORIGINAL_VALUE_Y + HOME_HEIGHT / 4
    window_array = np.array([x0_window + WINDOW_RADIUS * np.cos(angle_rot),
                             y0_window + WINDOW_RADIUS * np.sin(angle_rot)])
    window = []
    for i in range(len(window_array[0])):
        window.append([window_array[0][i], window_array[1][i]])

    window_shutters = []
    x1_window_shutters = x0_window - WINDOW_RADIUS
    y1_window_shutters = y0_window
    x2_window_shutters = x0_window
    y2_window_shutters = y0_window + WINDOW_RADIUS
    x3_window_shutters = x0_window + WINDOW_RADIUS
    y3_window_shutters = y0_window
    x4_window_shutters = x0_window
    y4_window_shutters = y0_window - WINDOW_RADIUS
    window_shutters.append([x1_window_shutters, y1_window_shutters])
    window_shutters.append([x2_window_shutters, y2_window_shutters])
    window_shutters.append([x3_window_shutters, y3_window_shutters])
    window_shutters.append([x4_window_shutters, y4_window_shutters])

    x0_door = ORIGINAL_VALUE_X + HOME_WIDTH / 3
    y0_door = ORIGINAL_VALUE_Y
    door_array = np.array([x0_door + DOOR_WIDTH * np.cos(angle_rot),
                           y0_door + DOOR_HEIGHT * np.sin(angle_rot)])
    door = []
    for i in range(len(door_array[0])):
        door.append([door_array[0][i], door_array[1][i]])

    door_rhombus = []
    x1_rhombus = ORIGINAL_VALUE_X + HOME_WIDTH / 3 - DOOR_WIDTH
    y1_rhombus = ORIGINAL_VALUE_Y
    x2_rhombus = ORIGINAL_VALUE_X + HOME_WIDTH / 3
    y2_rhombus = ORIGINAL_VALUE_Y + DOOR_HEIGHT
    x3_rhombus = ORIGINAL_VALUE_X + HOME_WIDTH / 3 + DOOR_WIDTH
    y3_rhombus = ORIGINAL_VALUE_Y
    x4_rhombus = ORIGINAL_VALUE_X + HOME_WIDTH / 3
    y4_rhombus = ORIGINAL_VALUE_Y - + DOOR_HEIGHT
    door_rhombus.append([x1_rhombus, y1_rhombus])
    door_rhombus.append([x2_rhombus, y2_rhombus])
    door_rhombus.append([x3_rhombus, y3_rhombus])
    door_rhombus.append([x4_rhombus, y4_rhombus])
    door_rhombus.append([x1_rhombus, y1_rhombus])

    door_shutters = []
    door_shutters.append([x1_rhombus, y1_rhombus])
    door_shutters.append([x2_rhombus, y2_rhombus])
    door_shutters.append([x3_rhombus, y3_rhombus])
    door_shutters.append([x4_rhombus, y4_rhombus])

    picture = []
    picture.append(home)
    picture.append(roof)
    picture.append(attic)
    picture.append(window)
    picture.append(door)
    picture.append(door_rhombus)
    picture.append(window_shutters)
    picture.append(door_shutters)
    picture.append(attic_shutters)

    return picture


if __name__ == "__main__":
    window = Tk()
    window.title("Лабораторная работа №2")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)
    window["bg"] = "#c5e5fc"

    fig = plt.figure()
    fig.set(facecolor="#69a5ff")
    fig.subplots_adjust(right=0.97, left=0.06, bottom=0.06, top=0.97)

    canvas = FigureCanvasTkAgg(fig, master=window)
    plot = canvas.get_tk_widget()

    plot.place(x=0, y=0, width=PLOT_WIDTH, height=PLOT_HEIGHT)

    Label(text="Центр", font=("Courier New", 20, "bold"), bg="#c5e5fc",
          fg="#000f7d").place(width=240, height=30, x=PLOT_WIDTH + 30, y=10)

    Label(text="масштабирования и поворота", font=("Courier New", 14, "bold"), bg="#c5e5fc",
          fg="#000f7d").place(width=300, height=20, x=PLOT_WIDTH + 5, y=40)

    Label(text="  X \t   Y  ", font=("Courier New", 19), bg="#c5e5fc",
          fg="#000f7d").place(width=240, height=20, x=PLOT_WIDTH + 30, y=60)

    x_center = Entry(font=("Courier New", 19))
    x_center.place(width=120, height=35, x=PLOT_WIDTH + 30, y=85)

    y_center = Entry(font=("Courier New", 19))
    y_center.place(width=120, height=35, x=PLOT_WIDTH + 150, y=85)

    Label(text="Масштабирование", font=("Courier New", 20, "bold"), bg="#c5e5fc",
          fg="#000f7d").place(width=240, height=30, x=PLOT_WIDTH + 30, y=140)

    Label(text="  kx \t   ky  ", font=("Courier New", 19), bg="#c5e5fc",
          fg="#000f7d").place(width=260, height=35, x=PLOT_WIDTH + 20, y=170)

    kx_scal = Entry(font=("Courier New", 19))
    kx_scal.place(width=120, height=35, x=PLOT_WIDTH + 30, y=205)

    ky_scal = Entry(font=("Courier New", 19))
    ky_scal.place(width=120, height=35, x=PLOT_WIDTH + 150, y=205)

    Button(text="Масштабировать", font=("Courier New", 18),
           highlightbackground="#b3b3cc", highlightthickness=30, fg="#000f7d",
           command=scaling). \
        place(width=236, height=26, x=PLOT_WIDTH + 32, y=252)

    Label(text="Поворот", font=("Courier New", 20, "bold"), bg="#c5e5fc",
          fg="#000f7d").place(width=240, height=30, x=PLOT_WIDTH + 30, y=298)

    Label(text="Угол°", font=("Courier New", 19), bg="#c5e5fc",
          fg="#000f7d").place(width=90, height=35, x=PLOT_WIDTH + 65, y=330)

    angle_rotation = Entry(font=("Courier New", 19))
    angle_rotation.place(width=120, height=35, x=PLOT_WIDTH + 150, y=330)

    Button(text="Повернуть", font=("Courier New", 18),
           highlightbackground="#b3b3cc", highlightthickness=30, fg="#000f7d",
           command=rotation). \
        place(width=236, height=26, x=PLOT_WIDTH + 32, y=377)

    Label(text="Перемещение", font=("Courier New", 20, "bold"), bg="#c5e5fc",
          fg="#000f7d").place(width=240, height=30, x=PLOT_WIDTH + 30, y=423)

    Label(text="  dx \t   dy  ", font=("Courier New", 19), bg="#c5e5fc",
          fg="#000f7d").place(width=240, height=35, x=PLOT_WIDTH + 30, y=453)

    dx_movement = Entry(font=("Courier New", 19))
    dx_movement.place(width=120, height=35, x=PLOT_WIDTH + 30, y=488)

    dy_movement = Entry(font=("Courier New", 19))
    dy_movement.place(width=120, height=35, x=PLOT_WIDTH + 150, y=488)

    Button(text="Переместить", font=("Courier New", 18),
           highlightbackground="#b3b3cc", highlightthickness=30, fg="#000f7d",
           command=movement). \
        place(width=236, height=26, x=PLOT_WIDTH + 32, y=535)

    Button(text="Шаг назад", font=("Courier New", 16),
           highlightbackground="#d1d1e0", highlightthickness=30, fg="#000f7d",
           command=step_back). \
        place(width=236, height=41, x=PLOT_WIDTH + 32, y=572)

    Button(text="Исходное положение", font=("Courier New", 16),
           highlightbackground="#d1d1e0", highlightthickness=30, fg="#000f7d",
           command=starting_position). \
        place(width=236, height=41, x=PLOT_WIDTH + 32, y=617)

    picture = create_picture()
    vers_picture = [copy_picture(picture)]

    set_initial_values()
    draw_picture()

    window.mainloop()
