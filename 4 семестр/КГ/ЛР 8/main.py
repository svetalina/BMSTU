from tkinter import Tk, Radiobutton, Canvas, Label, Entry, Button, IntVar, CENTER
from draw import WINDOW_HEIGHT, WINDOW_WIDTH, CANVAS_WIDTH, CANVAS_HEIGHT, \
    clear_canvas, click_left, click_right, click_centre, \
    add_line, add_vertex_figure, cut_off

my_font = "Microsoft JhengHei UI Light"

my_fg_highlight = "#ffffff"

my_bg_highlight_1 = "#CA6BFF"
my_bg_1 = "#E0A8FF"
my_fg_1 = "#440666"

my_bg_highlight_2 = "#FF62BB"
my_bg_2 = "#FFA3D7"
my_fg_2 = "#66063C"

my_bg_highlight_3 = "#9574FF"
my_bg_3 = "#C1ADFF"
my_fg_3 = "#1D0766"

my_bg_highlight_4 = "#FF62BB"
my_bg_4 = "#FFA3D7"
my_fg_4 = "#66063C"


def main():
    window = Tk()
    window.title("Лабораторная работа №8")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)
    window["bg"] = "#e0e0eb"

    canvas = Canvas(window, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
    canvas.place(x=0, y=0)

    lines = [[]]
    cutter_figure = []

    Label(text="", bg=my_bg_1).place(width=310, height=95, x=CANVAS_WIDTH + 4, y=0)

    Label(text="ЦВЕТ ОТСЕКАТЕЛЯ", font=(my_font, 16, "bold"), bg=my_bg_highlight_1, fg=my_fg_highlight). \
        place(width=308, height=25, x=CANVAS_WIDTH + 4, y=0)

    color_cut_var = IntVar()
    color_cut_var.set(2)

    Radiobutton(text="Чёрный", variable=color_cut_var, value=0, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=30)

    Radiobutton(text="Красный", variable=color_cut_var, value=1, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=50)

    Radiobutton(text="Синий", variable=color_cut_var, value=2, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=70)

    Radiobutton(text="Зелёный", variable=color_cut_var, value=3, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=30)

    Radiobutton(text="Жёлтый", variable=color_cut_var, value=4, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=50)

    Radiobutton(text="Фиолетовый", variable=color_cut_var, value=5, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=160, height=20, x=CANVAS_WIDTH + 150, y=70)

    Label(text="", bg=my_bg_2).place(width=310, height=95, x=CANVAS_WIDTH + 4, y=95)

    Label(text="ЦВЕТ ОТРЕЗКА", font=(my_font, 16, "bold"), bg=my_bg_highlight_2,
          fg=my_fg_highlight).place(width=308, height=25, x=CANVAS_WIDTH + 4, y=95)

    color_line_var = IntVar()
    color_line_var.set(3)

    Radiobutton(text="Чёрный", variable=color_line_var, value=0, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=125)

    Radiobutton(text="Красный", variable=color_line_var, value=1, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=145)

    Radiobutton(text="Синий", variable=color_line_var, value=2, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=165)

    Radiobutton(text="Зелёный", variable=color_line_var, value=3, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=125)

    Radiobutton(text="Жёлтый", variable=color_line_var, value=4, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=145)

    Radiobutton(text="Фиолетовый", variable=color_line_var, value=5, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=160, height=20, x=CANVAS_WIDTH + 150, y=165)

    Label(text="", bg=my_bg_3).place(width=310, height=95, x=CANVAS_WIDTH + 4, y=190)

    Label(text="ЦВЕТ РЕЗУЛЬТАТА", font=(my_font, 16, "bold"), bg=my_bg_highlight_3,
          fg=my_fg_highlight).place(width=308, height=25, x=CANVAS_WIDTH + 4, y=190)

    color_res_var = IntVar()
    color_res_var.set(1)

    Radiobutton(text="Чёрный", variable=color_res_var, value=0, font=(my_font, 16),
                activebackground=my_bg_highlight_3, bg=my_bg_3, activeforeground=my_fg_highlight, fg=my_fg_3,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=220)

    Radiobutton(text="Красный", variable=color_res_var, value=1, font=(my_font, 16),
                activebackground=my_bg_highlight_3, bg=my_bg_3, activeforeground=my_fg_highlight, fg=my_fg_3,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=240)

    Radiobutton(text="Синий", variable=color_res_var, value=2, font=(my_font, 16),
                activebackground=my_bg_highlight_3, bg=my_bg_3, activeforeground=my_fg_highlight, fg=my_fg_3,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=260)

    Radiobutton(text="Зелёный", variable=color_res_var, value=3, font=(my_font, 16),
                activebackground=my_bg_highlight_3, bg=my_bg_3, activeforeground=my_fg_highlight, fg=my_fg_3,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=220)

    Radiobutton(text="Жёлтый", variable=color_res_var, value=4, font=(my_font, 16),
                activebackground=my_bg_highlight_3, bg=my_bg_3, activeforeground=my_fg_highlight, fg=my_fg_3,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=240)

    Radiobutton(text="Фиолетовый", variable=color_res_var, value=5, font=(my_font, 16),
                activebackground=my_bg_highlight_3, bg=my_bg_3, activeforeground=my_fg_highlight, fg=my_fg_3,
                anchor="w").place(width=160, height=20, x=CANVAS_WIDTH + 150, y=260)

    Label(text="", bg=my_bg_4).place(width=310, height=140, x=CANVAS_WIDTH + 4, y=285)

    Label(text="ПОСТРОЕНИЕ ОТРЕЗКА", font=(my_font, 16, "bold"), bg=my_bg_highlight_4,
          fg=my_fg_highlight).place(width=308, height=25, x=CANVAS_WIDTH + 4, y=285)

    Label(text="Xн       Yн        Xк       Yк", font=(my_font, 16), bg=my_bg_4,
          fg=my_fg_4).place(width=268, height=20, x=CANVAS_WIDTH + 25, y=320)

    xb_entry = Entry(font=(my_font, 16), fg=my_fg_4, justify=CENTER)
    xb_entry.place(width=67, height=30, x=CANVAS_WIDTH + 25, y=345)

    yb_entry = Entry(font=(my_font, 16), fg=my_fg_4, justify=CENTER)
    yb_entry.place(width=67, height=30, x=CANVAS_WIDTH + 92, y=345)

    xe_entry = Entry(font=(my_font, 16), fg=my_fg_4, justify=CENTER)
    xe_entry.place(width=67, height=30, x=CANVAS_WIDTH + 159, y=345)

    ye_entry = Entry(font=(my_font, 16), fg=my_fg_4, justify=CENTER)
    ye_entry.place(width=67, height=30, x=CANVAS_WIDTH + 226, y=345)

    Button(text="Построить отрезок", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_4,
           activeforeground=my_bg_highlight_4, fg=my_fg_highlight,
           command=lambda: add_line(lines, canvas, color_line_var, xb_entry, yb_entry, xe_entry, ye_entry)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=387)

    Label(text="", bg=my_bg_1).place(width=310, height=315, x=CANVAS_WIDTH + 4, y=425)

    Label(text="ПОСТРОЕНИЕ ОТСЕКАТЕЛЯ", font=(my_font, 16, "bold"), bg=my_bg_highlight_1,
          fg=my_fg_highlight).place(width=305, height=25, x=CANVAS_WIDTH + 5, y=425)

    Label(text="X                    Y", font=(my_font, 16), bg=my_bg_1,
          fg=my_fg_1).place(width=268, height=20, x=CANVAS_WIDTH + 25, y=460)

    x_cut_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    x_cut_entry.place(width=134, height=30, x=CANVAS_WIDTH + 25, y=485)

    y_cut_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    y_cut_entry.place(width=134, height=30, x=CANVAS_WIDTH + 159, y=485)

    Button(text="Построение отсекателя", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_1,
           activeforeground=my_bg_highlight_1, fg=my_fg_highlight,
           command=lambda:
           add_vertex_figure(lines, cutter_figure, canvas, color_cut_var, x_cut_entry, y_cut_entry)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=527)

    Button(text="Замкнуть отсекатель", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_2,
           activeforeground=my_bg_highlight_2, fg=my_fg_highlight,
           command=lambda event='<3>':
           click_centre(event, cutter_figure, canvas, color_cut_var)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=575)

    Button(text="Отсечь", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_3,
           activeforeground=my_bg_highlight_3, fg=my_fg_highlight,
           command=lambda: cut_off(cutter_figure, lines, canvas, color_cut_var, color_res_var)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=612)

    Button(text="Очистить экран", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_4,
           activeforeground=my_bg_highlight_4, fg=my_fg_highlight,
           command=lambda: clear_canvas(canvas, lines, cutter_figure)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=649)

    canvas.bind('<1>',
                lambda event: click_left(event, lines, canvas, color_line_var))
    canvas.bind('<2>',
                lambda event: click_centre(event, cutter_figure, canvas, color_cut_var))
    canvas.bind('<3>',
                lambda event: click_right(event, lines, cutter_figure, canvas, color_cut_var))

    xb_entry.insert(0, "100")
    yb_entry.insert(0, "200")

    xe_entry.insert(0, "800")
    ye_entry.insert(0, "500")

    x_cut_entry.insert(0, "200")
    y_cut_entry.insert(0, "100")

    window.mainloop()


if __name__ == "__main__":
    main()
