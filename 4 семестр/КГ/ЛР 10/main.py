from tkinter import Tk, Radiobutton, Canvas, Label, Entry, Button, IntVar, CENTER
from draw import WINDOW_HEIGHT, WINDOW_WIDTH, CANVAS_WIDTH, CANVAS_HEIGHT, \
    clear_canvas, build_graph, spin_x, spin_y, spin_z, scale_graph

my_font = "Microsoft JhengHei UI Light"

my_fg_highlight = "#ffffff"

my_bg_highlight_1 = "#668AFF"
my_bg_1 = "#B2C4FF"
my_fg_1 = "#021657"

my_bg_highlight_2 = "#D059FF"
my_bg_2 = "#E8ACFF"
my_fg_2 = "#3F0257"

my_bg_highlight_3 = "#FF6252"
my_bg_3 = "#FFB1A8"
my_fg_3 = "#570A02"


def main():
    window = Tk()
    window.title("Лабораторная работа №10")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)
    window["bg"] = "#e0e0eb"

    canvas = Canvas(window, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
    canvas.place(x=0, y=0)

    Label(text="", bg=my_bg_1).place(width=310, height=95, x=CANVAS_WIDTH + 3, y=0)

    Label(text="ЦВЕТ", font=(my_font, 16, "bold"), bg=my_bg_highlight_1,
          fg=my_fg_highlight).place(width=310, height=25, x=CANVAS_WIDTH + 3, y=0)

    color_var = IntVar()
    color_var.set(2)

    Radiobutton(text="Чёрный", variable=color_var, value=0, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=120, height=20, x=CANVAS_WIDTH + 20, y=30)

    Radiobutton(text="Красный", variable=color_var, value=1, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=120, height=20, x=CANVAS_WIDTH + 20, y=50)

    Radiobutton(text="Синий", variable=color_var, value=2, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=120, height=20, x=CANVAS_WIDTH + 20, y=70)

    Radiobutton(text="Зелёный", variable=color_var, value=3, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=150, height=20, x=CANVAS_WIDTH + 150, y=30)

    Radiobutton(text="Жёлтый", variable=color_var, value=4, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=150, height=20, x=CANVAS_WIDTH + 150, y=50)

    Radiobutton(text="Фиолетовый", variable=color_var, value=5, font=(my_font, 16),
                activebackground=my_bg_highlight_1, bg=my_bg_1, activeforeground=my_fg_highlight, fg=my_fg_1,
                anchor="w").place(width=150, height=20, x=CANVAS_WIDTH + 150, y=70)

    Label(text="", bg=my_bg_2).place(width=310, height=140, x=CANVAS_WIDTH + 3, y=95)

    Label(text="ФУНКЦИЯ", font=(my_font, 16, "bold"), bg=my_bg_highlight_2,
          fg=my_fg_highlight).place(width=310, height=25, x=CANVAS_WIDTH + 3, y=95)

    func_var = IntVar()
    func_var.set(0)

    Radiobutton(text="sin(x) * cos(z)", variable=func_var, value=0, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=200, height=25, x=CANVAS_WIDTH + 80, y=125)

    Radiobutton(text="sin(cos(x)) * sin(z)", variable=func_var, value=1, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=200, height=25, x=CANVAS_WIDTH + 80, y=150)

    Radiobutton(text="cos(x) * z / 4", variable=func_var, value=2, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=200, height=25, x=CANVAS_WIDTH + 80, y=175)

    Radiobutton(text="cos(x) * cos(sin(z))", variable=func_var, value=3, font=(my_font, 16),
                activebackground=my_bg_highlight_2, bg=my_bg_2, activeforeground=my_fg_highlight, fg=my_fg_2,
                anchor="w").place(width=200, height=25, x=CANVAS_WIDTH + 80, y=200)

    Label(text="", bg=my_bg_3).place(width=310, height=150, x=CANVAS_WIDTH + 3, y=235)

    Label(text="ПРЕДЕЛЫ", font=(my_font, 16, "bold"), bg=my_bg_highlight_3,
          fg=my_fg_highlight).place(width=310, height=25, x=CANVAS_WIDTH + 3, y=235)

    Label(text="Ox:", font=(my_font, 16), bg=my_bg_3,
          fg=my_fg_3).place(width=40, height=25, x=CANVAS_WIDTH + 10, y=300)

    Label(text="от         до         шаг", font=(my_font, 16), bg=my_bg_3,
          fg=my_fg_3).place(width=210, height=20, x=CANVAS_WIDTH + 70, y=270)

    x_from_entry = Entry(font=(my_font, 16), fg=my_fg_3, justify=CENTER)
    x_from_entry.place(width=80, height=30, x=CANVAS_WIDTH + 50, y=300)

    x_to_entry = Entry(font=(my_font, 16), fg=my_fg_3, justify=CENTER)
    x_to_entry.place(width=80, height=30, x=CANVAS_WIDTH + 130, y=300)

    x_step_entry = Entry(font=(my_font, 16), fg=my_fg_3, justify=CENTER)
    x_step_entry.place(width=80, height=30, x=CANVAS_WIDTH + 210, y=300)

    Label(text="Oz:", font=(my_font, 16), bg=my_bg_3,
          fg=my_fg_3).place(width=40, height=25, x=CANVAS_WIDTH + 10, y=340)

    z_from_entry = Entry(font=(my_font, 16), fg=my_fg_3, justify=CENTER)
    z_from_entry.place(width=80, height=30, x=CANVAS_WIDTH + 50, y=340)

    z_to_entry = Entry(font=(my_font, 16), fg=my_fg_3, justify=CENTER)
    z_to_entry.place(width=80, height=30, x=CANVAS_WIDTH + 130, y=340)

    z_step_entry = Entry(font=(my_font, 16), fg=my_fg_3, justify=CENTER)
    z_step_entry.place(width=80, height=30, x=CANVAS_WIDTH + 210, y=340)

    Label(text="", bg=my_bg_2).place(width=310, height=120, x=CANVAS_WIDTH + 3, y=380)

    Label(text="МАСШТАБИРОВАНИЕ", font=(my_font, 16, "bold"), bg=my_bg_highlight_2,
          fg=my_fg_highlight).place(width=310, height=25, x=CANVAS_WIDTH + 3, y=380)

    Label(text="Коэффициент:", font=(my_font, 16), bg=my_bg_2,
          fg=my_fg_2).place(width=150, height=20, x=CANVAS_WIDTH + 40, y=420)

    scale_entry = Entry(font=(my_font, 16), fg=my_fg_2, justify=CENTER)
    scale_entry.place(width=80, height=30, x=CANVAS_WIDTH + 190, y=415)

    Button(text="Масштабировать", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_2,
           activeforeground=my_fg_2, fg=my_fg_highlight,
           command=lambda: scale_graph(
               scale_entry, canvas, color_var, func_var,
               x_from_entry, x_to_entry, x_step_entry,
               z_from_entry, z_to_entry, z_step_entry)). \
        place(width=264, height=26, x=CANVAS_WIDTH + 27, y=452)

    Label(text="", bg=my_bg_1).place(width=310, height=220, x=CANVAS_WIDTH + 3, y=490)

    Label(text="ВРАЩЕНИЕ", font=(my_font, 16, "bold"), bg=my_bg_highlight_1,
          fg=my_fg_highlight).place(width=310, height=25, x=CANVAS_WIDTH + 3, y=490)

    Label(text="Ox:", font=(my_font, 16), bg=my_bg_1,
          fg=my_fg_1).place(width=40, height=30, x=CANVAS_WIDTH + 27, y=525)

    Label(text="Oy:", font=(my_font, 16), bg=my_bg_1,
          fg=my_fg_1).place(width=40, height=30, x=CANVAS_WIDTH + 27, y=560)

    Label(text="Oz:", font=(my_font, 16), bg=my_bg_1,
          fg=my_fg_1).place(width=40, height=30, x=CANVAS_WIDTH + 27, y=595)

    x_spin_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    x_spin_entry.place(width=80, height=30, x=CANVAS_WIDTH + 70, y=525)

    y_spin_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    y_spin_entry.place(width=80, height=30, x=CANVAS_WIDTH + 70, y=560)

    z_spin_entry = Entry(font=(my_font, 16), fg=my_fg_1, justify=CENTER)
    z_spin_entry.place(width=80, height=30, x=CANVAS_WIDTH + 70, y=595)

    Button(text="Повернуть", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_1,
           activeforeground=my_fg_1, fg=my_fg_highlight,
           command=lambda: spin_x(
               x_spin_entry, canvas, color_var, func_var,
               x_from_entry, x_to_entry, x_step_entry,
               z_from_entry, z_to_entry, z_step_entry)). \
        place(width=116, height=26, x=CANVAS_WIDTH + 172, y=527)

    Button(text="Повернуть", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_1,
           activeforeground=my_fg_1, fg=my_fg_highlight,
           command=lambda: spin_y(
               y_spin_entry, canvas, color_var, func_var,
               x_from_entry, x_to_entry, x_step_entry,
               z_from_entry, z_to_entry, z_step_entry)). \
        place(width=116, height=26, x=CANVAS_WIDTH + 172, y=562)

    Button(text="Повернуть", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_1,
           activeforeground=my_fg_1, fg=my_fg_highlight,
           command=lambda: spin_z(
               z_spin_entry, canvas, color_var, func_var,
               x_from_entry, x_to_entry, x_step_entry,
               z_from_entry, z_to_entry, z_step_entry)). \
        place(width=116, height=26, x=CANVAS_WIDTH + 172, y=597)

    Button(text="Построить", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_2,
           activeforeground=my_fg_2, fg=my_fg_highlight,
           command=lambda: build_graph(
               canvas, color_var, func_var,
               x_from_entry, x_to_entry, x_step_entry,
               z_from_entry, z_to_entry, z_step_entry, new_graph=True)). \
        place(width=264, height=25, x=CANVAS_WIDTH + 27, y=637)

    Button(text="Очистить экран", font=(my_font, 16),
           activebackground=my_fg_highlight, bg=my_bg_highlight_3,
           activeforeground=my_fg_3, fg=my_fg_highlight,
           command=lambda: clear_canvas(canvas)). \
        place(width=264, height=25, x=CANVAS_WIDTH + 27, y=665)

    x_from_entry.insert(0, "-10")
    x_to_entry.insert(0, "10")
    x_step_entry.insert(0, "0.2")

    z_from_entry.insert(0, "-10")
    z_to_entry.insert(0, "10")
    z_step_entry.insert(0, "0.2")

    scale_entry.insert(0, "43")

    x_spin_entry.insert(0, "30")
    y_spin_entry.insert(0, "30")
    z_spin_entry.insert(0, "30")

    window.mainloop()


if __name__ == "__main__":
    main()
