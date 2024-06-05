from tkinter import Tk, Radiobutton, Canvas, Label, Entry, Button, IntVar, CENTER
from draw import WINDOW_HEIGHT, WINDOW_WIDTH, CANVAS_WIDTH, CANVAS_HEIGHT, \
    clear_canvas, click_left, click_right, close_figure, add_vertex, cut_off

my_font = "Microsoft JhengHei UI Light"

my_fg_highlight = "#ffffff"

my_bg_highlight_1 = "#6EC8D9"
my_bg_1 = "#ADEBF7"
my_fg_1 = "#003741"

my_bg_highlight_2 = "#73EA7B"
my_bg_2 = "#AEFBB3"
my_fg_2 = "#004605"

my_bg_highlight_3 = "#7C8EE0"
my_bg_3 = "#B5C1F8"
my_fg_3 = "#000C43"


def main():
    window = Tk()
    window.title("Лабораторная работа №9")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)

    canvas = Canvas(window, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
    canvas.place(x=0, y=0)

    figure = []
    cutter = []

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
                anchor="w").place(width=150, height=20, x=CANVAS_WIDTH + 150, y=70)

    Label(text="", bg=my_bg_2).place(width=310, height=95, x=CANVAS_WIDTH + 4, y=95)

    Label(text="ЦВЕТ ФИГУРЫ", font=(my_font, 16, "bold"), bg=my_bg_highlight_2,
          fg=my_fg_highlight).place(width=308, height=25, x=CANVAS_WIDTH + 4, y=95)

    color_fig_var = IntVar()
    color_fig_var.set(3)

    Radiobutton(text="Чёрный", variable=color_fig_var, value=0, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=125)

    Radiobutton(text="Красный", variable=color_fig_var, value=1, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=145)

    Radiobutton(text="Синий", variable=color_fig_var, value=2, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 20, y=165)

    Radiobutton(text="Зелёный", variable=color_fig_var, value=3, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=125)

    Radiobutton(text="Жёлтый", variable=color_fig_var, value=4, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=140, height=20, x=CANVAS_WIDTH + 150, y=145)

    Radiobutton(text="Фиолетовый", variable=color_fig_var, value=5, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=150, height=20, x=CANVAS_WIDTH + 150, y=165)

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
                anchor="w").place(width=150, height=20, x=CANVAS_WIDTH + 150, y=260)

    Label(text="", bg=my_bg_2).place(width=310, height=175, x=CANVAS_WIDTH + 4, y=285)

    Label(text="ПОСТРОЕНИЕ ФИГУРЫ", font=(my_font, 16, "bold"), bg=my_bg_highlight_2,
          fg=my_fg_highlight).place(width=305, height=25, x=CANVAS_WIDTH + 5, y=285)
    Label(text="X                     Y", font=(my_font, 16), bg=my_bg_2,
          fg=my_fg_2).place(width=268, height=20, x=CANVAS_WIDTH + 25, y=320)

    x_fig_entry = Entry(font=(my_font, 16), fg=my_fg_2, justify=CENTER)
    x_fig_entry.place(width=134, height=30, x=CANVAS_WIDTH + 25, y=345)

    y_fig_entry = Entry(font=(my_font, 16), fg=my_fg_2, justify=CENTER)
    y_fig_entry.place(width=134, height=30, x=CANVAS_WIDTH + 159, y=345)

    Button(text="Построить вершину", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_2,
           activeforeground=my_fg_2, fg=my_fg_2,
           command=lambda:
           add_vertex(cutter, figure, canvas, color_fig_var, color_cut_var, x_fig_entry, y_fig_entry)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=387)

    Button(text="Замкнуть фигуру", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_2,
           activeforeground=my_fg_2, fg=my_fg_2,
           command=lambda: close_figure(figure, canvas, color_fig_var, fig_str="Фигура должна")). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=422)

    Label(text="", bg=my_bg_1).place(width=310, height=235, x=CANVAS_WIDTH + 4, y=460)

    Label(text="ПОСТРОЕНИЕ ОТСЕКАТЕЛЯ", font=(my_font, 16, "bold"), bg=my_bg_highlight_1,
          fg=my_fg_highlight).place(width=305, height=25, x=CANVAS_WIDTH + 5, y=460)

    Label(text="X                     Y", font=(my_font, 16), bg=my_bg_1,
          fg=my_fg_1).place(width=268, height=20, x=CANVAS_WIDTH + 25, y=495)

    x_cut_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    x_cut_entry.place(width=134, height=30, x=CANVAS_WIDTH + 25, y=520)

    y_cut_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    y_cut_entry.place(width=134, height=30, x=CANVAS_WIDTH + 159, y=520)

    Button(text="Построить вершину", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_1,
           activeforeground=my_fg_1, fg=my_fg_1,
           command=lambda:
           add_vertex(figure, cutter, canvas, color_cut_var, color_fig_var, x_cut_entry, y_cut_entry)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=562)

    Button(text="Замкнуть отсекатель", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_1,
           activeforeground=my_fg_1, fg=my_fg_1,
           command=lambda: close_figure(cutter, canvas, color_cut_var, fig_str="Отсекатель должен")). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=597)

    Button(text="Отсечь", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_2,
           activeforeground=my_fg_2, fg=my_fg_2,
           command=lambda: cut_off(cutter, figure, canvas, color_res_var)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=632)

    Button(text="Очистить экран", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_3,
           activeforeground=my_fg_3, fg=my_fg_3,
           command=lambda: clear_canvas(canvas, figure, cutter)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=667)

    canvas.bind('<1>',
                lambda event: click_left(event, cutter, figure, canvas, color_fig_var, color_cut_var))
    canvas.bind('<3>',
                lambda event: click_right(event, figure, cutter, canvas, color_cut_var, color_fig_var))

    x_fig_entry.insert(0, "100")
    y_fig_entry.insert(0, "200")

    x_cut_entry.insert(0, "200")
    y_cut_entry.insert(0, "100")

    window.mainloop()


if __name__ == "__main__":
    main()
