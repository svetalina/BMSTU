from tkinter import Tk, Radiobutton, Canvas, Label, Entry, Button, IntVar, RIDGE
from draw import WINDOW_HEIGHT, WINDOW_WIDTH, CANVAS_WIDTH, CANVAS_HEIGHT
from draw import draw_line, clear_canvas, draw_spectrum
from comparisons import time_comparison, step_comparison


def main():
    window = Tk()
    window.title("Лабораторная работа №3")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)
    window["bg"] = "#ffc7e9"

    canvas = Canvas(window, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
    canvas.place(x=0, y=0)

    Label(text="Цвет линий", font=("Courier New", 20, "bold"), bg="#ffc7e9",
          fg="#69003f").place(width=305, height=30, x=CANVAS_WIDTH + 5, y=10)

    color_fg = IntVar()
    color_fg.set(1)

    Radiobutton(text="Белый", variable=color_fg, value=0,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=130, height=20, x=CANVAS_WIDTH + 20, y=50)

    Radiobutton(text="Чёрный", variable=color_fg, value=1,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=130, height=20, x=CANVAS_WIDTH + 20, y=70)

    Radiobutton(text="Красный", variable=color_fg, value=2,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=130, height=20, x=CANVAS_WIDTH + 20, y=90)

    Radiobutton(text="Синий", variable=color_fg, value=3,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=130, height=20, x=CANVAS_WIDTH + 170, y=50)

    Radiobutton(text="Зелёный", variable=color_fg, value=4,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=130, height=20, x=CANVAS_WIDTH + 170, y=70)

    Radiobutton(text="Жёлтый", variable=color_fg, value=5,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=130, height=20, x=CANVAS_WIDTH + 170, y=90)

    Label(text="Алгоритм построения", font=("Courier New", 20, "bold"), bg="#ffc7e9",
          fg="#69003f").place(width=305, height=30, x=CANVAS_WIDTH + 5, y=120)

    algorithm = IntVar()
    algorithm.set(0)

    Radiobutton(text="ЦДА", variable=algorithm, value=0,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=250, height=20, x=CANVAS_WIDTH + 20, y=160)

    Radiobutton(text="Брезенхем (float)", variable=algorithm, value=1,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=250, height=20, x=CANVAS_WIDTH + 20, y=180)

    Radiobutton(text="Брезенхем (int)", variable=algorithm, value=2,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=250, height=20, x=CANVAS_WIDTH + 20, y=200)

    Radiobutton(text="Брезенхем (steps)", variable=algorithm, value=3,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=280, height=20, x=CANVAS_WIDTH + 20, y=220)

    Radiobutton(text="Ву", variable=algorithm, value=4,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=250, height=20, x=CANVAS_WIDTH + 20, y=240)

    Radiobutton(text="Библиотечный", variable=algorithm, value=5,
                font=("Courier New", 17), bg="#ffc7e9", fg="#69003f", anchor="w"). \
        place(width=250, height=20, x=CANVAS_WIDTH + 20, y=260)

    Label(text="Построение отрезка", font=("Courier New", 20, "bold"), bg="#ffc7e9",
          fg="#69003f").place(width=305, height=30, x=CANVAS_WIDTH + 5, y=290)

    Label(text="Xн   Yн   Xк   Yк", font=("Courier New", 17), bg="#ffc7e9",
          fg="#69003f").place(width=260, height=20, x=CANVAS_WIDTH + 30, y=330)

    x_beg_entry = Entry(font=("Courier New", 17), fg="#ff0084")
    x_beg_entry.place(width=65, height=30, x=CANVAS_WIDTH + 30, y=360)

    y_beg_entry = Entry(font=("Courier New", 17), fg="#ff0084")
    y_beg_entry.place(width=65, height=30, x=CANVAS_WIDTH + 95, y=360)

    x_end_entry = Entry(font=("Courier New", 17), fg="#ff0084")
    x_end_entry.place(width=65, height=30, x=CANVAS_WIDTH + 160, y=360)

    y_end_entry = Entry(font=("Courier New", 17), fg="#ff0084")
    y_end_entry.place(width=65, height=30, x=CANVAS_WIDTH + 225, y=360)

    Button(text="Построить отрезок", font=("Courier New", 16), bg="#ff0084", fg="white",
           relief=RIDGE, activebackground="white", activeforeground="#ff0084",
           command=lambda: draw_line(canvas, color_fg, algorithm, x_beg_entry, y_beg_entry, x_end_entry, y_end_entry)). \
        place(width=306, height=26, x=CANVAS_WIDTH + 4, y=402)

    Label(text="Построение спектра", font=("Courier New", 20, "bold"), bg="#ffc7e9",
          fg="#69003f").place(width=305, height=30, x=CANVAS_WIDTH + 5, y=440)

    Label(text="Угол поворота", font=("Courier New", 17), bg="#ffc7e9",
          fg="#69003f").place(width=197, height=30, x=CANVAS_WIDTH + 8, y=480)

    angle_entry = Entry(font=("Courier New", 17), fg="#ff0084")
    angle_entry.place(width=95, height=30, x=CANVAS_WIDTH + 205, y=480)

    Label(text="Длина отрезка", font=("Courier New", 16), bg="#ffc7e9",
          fg="#69003f").place(width=190, height=30, x=CANVAS_WIDTH + 10, y=510)

    radius_entry = Entry(font=("Courier New", 17), fg="#ff0084")
    radius_entry.place(width=95, height=30, x=CANVAS_WIDTH + 205, y=510)

    Button(text="Построить cпектр", font=("Courier New", 16), bg="#ff0084", fg="white",
           relief=RIDGE, activebackground="white", activeforeground="#ff0084",
           command=lambda: draw_spectrum(canvas, color_fg, algorithm, angle_entry, radius_entry)). \
        place(width=306, height=26, x=CANVAS_WIDTH + 4, y=552)

    Button(text="Сравнение времени", font=("Courier New", 16), bg="#ab0058", fg="white",
           relief=RIDGE, activebackground="white", activeforeground="#ab0058",
           command=lambda: time_comparison(canvas, color_fg, algorithm, angle_entry, radius_entry)). \
        place(width=306, height=31, x=CANVAS_WIDTH + 4, y=587)

    Button(text="Сравнение ступенчатости", font=("Courier New", 16), bg="#ab0058", fg="white",
           relief=RIDGE, activebackground="white", activeforeground="#ab0058",
           command=lambda: step_comparison(canvas, angle_entry, radius_entry)). \
        place(width=306, height=31, x=CANVAS_WIDTH + 4, y=622)

    Button(text="Очистить экран", font=("Courier New", 16), bg="#69003f", fg="white",
           relief=RIDGE, activebackground="white", activeforeground="#69003f",
           command=lambda: clear_canvas(canvas)). \
        place(width=306, height=36, x=CANVAS_WIDTH + 4, y=657)

    angle_entry.insert(0, str(10))
    radius_entry.insert(0, str(350))

    x_beg_entry.insert(0, str(200))
    y_beg_entry.insert(0, str(200))

    x_end_entry.insert(0, str(700))
    y_end_entry.insert(0, str(300))

    window.mainloop()


if __name__ == "__main__":
    main()
