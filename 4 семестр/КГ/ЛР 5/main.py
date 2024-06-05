from tkinter import Tk, Radiobutton, Canvas, Label, Entry, Button, \
    PhotoImage, DISABLED, IntVar, BooleanVar, Listbox, RIDGE, CENTER
from draw import WINDOW_HEIGHT, WINDOW_WIDTH, CANVAS_WIDTH, CANVAS_HEIGHT, \
    clear_canvas, click_left, click_right, draw_point, fill_figure

my_font = "Times New Roman"
my_bg_general = "white"
my_fg_general = "#6d0075"
my_bg_highlight_1 = "#FFB8B8"
my_bg_highlight_2 = "#B8FFFF"
my_bg_highlight_3 = "#B8FFB8"
my_bg_highlight_4 = "#f0b8ff"
my_fg_highlight_1 = "#850000"
my_fg_highlight_2 = "#005a5c"
my_fg_highlight_3 = "#006b00"
my_fg_highlight_4 = "#48005c"
my_bg_button = "#002A17"
my_fg_button = "white"
my_relief = RIDGE
my_text_fg = "#00552D"


def main():
    window = Tk()
    window.title("Лабораторная работа №5")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)
    window["bg"] = my_bg_general

    canvas = Canvas(window, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
    canvas.place(x=0, y=0)

    figures = [[[]]]

    p_min = [CANVAS_WIDTH, CANVAS_HEIGHT]
    p_max = [0, 0]

    Label(text="ЦВЕТ ЗАКРАСКИ", font=(my_font, 16, "bold"), bg=my_bg_highlight_1,
          fg=my_fg_highlight_1).place(width=305, height=30, x=CANVAS_WIDTH + 5, y=10)

    color_var = IntVar()
    color_var.set(3)

    Radiobutton(text="Чёрный", variable=color_var, value=0,
                font=(my_font, 16), activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight_1, anchor="w"). \
        place(width=140, height=20, x=CANVAS_WIDTH + 10, y=50)

    Radiobutton(text="Красный", variable=color_var, value=1,
                font=(my_font, 16), activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight_1, anchor="w"). \
        place(width=140, height=20, x=CANVAS_WIDTH + 10, y=70)

    Radiobutton(text="Синий", variable=color_var, value=2,
                font=(my_font, 16), activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight_1, anchor="w"). \
        place(width=140, height=20, x=CANVAS_WIDTH + 10, y=90)

    Radiobutton(text="Зелёный", variable=color_var, value=3,
                font=(my_font, 16), activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight_1, anchor="w"). \
        place(width=140, height=20, x=CANVAS_WIDTH + 160, y=50)

    Radiobutton(text="Жёлтый", variable=color_var, value=4,
                font=(my_font, 16), activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight_1, anchor="w"). \
        place(width=140, height=20, x=CANVAS_WIDTH + 160, y=70)

    Radiobutton(text="Фиолетовый", variable=color_var, value=5,
                font=(my_font, 16), activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight_1, anchor="w"). \
        place(width=140, height=20, x=CANVAS_WIDTH + 160, y=90)

    Label(text="РЕЖИМ ЗАКРАСКИ", font=(my_font, 16, "bold"), bg=my_bg_highlight_2,
          fg=my_fg_highlight_2).place(width=305, height=30, x=CANVAS_WIDTH + 5, y=120)

    mode_var = BooleanVar()
    mode_var.set(1)

    Radiobutton(text="Без задержки", variable=mode_var, value=0,
                font=(my_font, 16), activebackground=my_fg_highlight_2, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_2,
                selectcolor=my_bg_highlight_2, anchor="w"). \
        place(width=250, height=20, x=CANVAS_WIDTH + 10, y=160)

    Radiobutton(text="С задержкой", variable=mode_var, value=1,
                font=(my_font, 16), activebackground=my_fg_highlight_2, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_2,
                selectcolor=my_bg_highlight_2, anchor="w"). \
        place(width=280, height=20, x=CANVAS_WIDTH + 160, y=160)

    Label(text="ПОСТРОЕНИЕ ТОЧКИ", font=(my_font, 16, "bold"), bg=my_bg_highlight_3,
          fg=my_fg_highlight_3).place(width=305, height=30, x=CANVAS_WIDTH + 5, y=190)

    Label(text="X                      Y", font=(my_font, 16), bg=my_bg_general,
          fg=my_fg_highlight_3).place(width=250, height=20, x=CANVAS_WIDTH + 30, y=230)

    x_entry = Entry(font=(my_font, 16), bg=my_bg_highlight_3, fg=my_fg_highlight_3, justify=CENTER)
    x_entry.place(width=125, height=30, x=CANVAS_WIDTH + 30, y=250)

    y_entry = Entry(font=(my_font, 16), bg=my_bg_highlight_3, fg=my_fg_highlight_3, justify=CENTER)
    y_entry.place(width=125, height=30, x=CANVAS_WIDTH + 155, y=250)

    Button(text="Построить точку", font=(my_font, 16),
           activebackground=my_bg_highlight_3, activeforeground=my_fg_highlight_3,
           bg=my_fg_highlight_3, fg=my_bg_highlight_3,
           command=lambda: draw_point(figures, img, color_var, x_entry, y_entry,
                                      p_min, p_max, points_listbox)). \
        place(width=246, height=30, x=CANVAS_WIDTH + 32, y=287)

    points_listbox = Listbox(font=(my_font, 16), bg=my_bg_highlight_3, fg=my_fg_highlight_3,
                             selectbackground=my_fg_highlight_3, justify=CENTER)
    points_listbox.place(width=250, height=130, x=CANVAS_WIDTH + 30, y=324)

    Label(text="ПОСТРОЕНИЕ МЫШЬЮ",
          font=(my_font, 16, "bold"), bg=my_bg_highlight_4, fg=my_fg_highlight_4). \
        place(width=305, height=30, x=CANVAS_WIDTH + 5, y=467)

    Label(text="Левая кнопка - добавить точку",
          font=(my_font, 16), bg=my_bg_general, fg=my_fg_highlight_4, justify=CENTER). \
        place(height=25, width=310, x=CANVAS_WIDTH + 5, y=507)

    Label(text="Правая кнопка - замкнуть фигуру",
          font=(my_font, 16), bg=my_bg_general, fg=my_fg_highlight_4). \
        place(height=25, width=310, x=CANVAS_WIDTH + 5, y=532)

    Label(text="Время закраски:", font=(my_font, 16), bg=my_bg_general,
          fg=my_fg_highlight_4).place(width=140, height=30, x=CANVAS_WIDTH + 15, y=567)

    time_entry = Entry(font=(my_font, 16), bg=my_bg_highlight_4, fg=my_fg_highlight_4)
    time_entry.place(width=120, height=30, x=CANVAS_WIDTH + 160, y=567)

    Button(text="Выполнить закраску", font=(my_font, 16),
           activebackground=my_bg_highlight_4, activeforeground=my_fg_highlight_4,
           bg=my_fg_highlight_4, fg=my_bg_highlight_4,
           command=lambda: fill_figure(figures, img, canvas, color_var, p_min, p_max, mode_var, time_entry)). \
        place(width=246, height=30, x=CANVAS_WIDTH + 32, y=608)

    Button(text="Очистить экран", font=(my_font, 16),
           activebackground=my_bg_highlight_4, activeforeground=my_fg_highlight_4,
           bg=my_fg_highlight_4, fg=my_bg_highlight_4,
           command=lambda: clear_canvas(img, canvas, figures, p_min, p_max,
                                        time_entry, points_listbox)). \
        place(width=246, height=30, x=CANVAS_WIDTH + 32, y=647)

    img = PhotoImage(width=CANVAS_WIDTH, height=CANVAS_HEIGHT)
    canvas.create_image(CANVAS_WIDTH // 2, CANVAS_HEIGHT // 2, image=img, state='normal')

    canvas.bind('<Button-1>',
                lambda event: click_left(event, figures, img, color_var, p_min, p_max, points_listbox))
    canvas.bind('<Button-3>',
                lambda event: click_right(event, figures, img, color_var))

    x_entry.insert(0, "100")
    y_entry.insert(0, "100")

    window.mainloop()


if __name__ == "__main__":
    main()
