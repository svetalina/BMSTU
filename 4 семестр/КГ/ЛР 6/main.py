from tkinter import Tk, Radiobutton, Canvas, Label, Entry, Button, \
    PhotoImage, IntVar, BooleanVar, Listbox, CENTER
from draw import WINDOW_HEIGHT, WINDOW_WIDTH, CANVAS_WIDTH, CANVAS_HEIGHT, MENU_WIDTH, \
    clear_canvas, click_left, click_right, click_centre, draw_point, fill_figure

my_font = "Segoe UI"
my_bg_general = "#272727"
my_bg_highlight = "#878787"
my_fg_highlight_1 = "#00d165"
my_fg_highlight_2 = "#eb0000"
my_fg_highlight_3 = "#e64500"
my_fg_highlight_4 = "#ffe400"


def main():
    window = Tk()
    window.title("Лабораторная работа №6")
    window.geometry("%dx%d" % (WINDOW_WIDTH, WINDOW_HEIGHT))
    window.resizable(False, False)
    window["bg"] = my_bg_general

    canvas = Canvas(window, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
    canvas.place(x=0, y=0)

    figures = [[[]]]

    Label(text="ЦВЕТ ЗАТРАВКИ", font=(my_font, 16, "bold"), bg=my_bg_highlight,
          fg=my_fg_highlight_1, justify=CENTER).place(width=MENU_WIDTH, height=30, x=CANVAS_WIDTH + 5, y=0)

    color_var = IntVar()
    color_var.set(3)

    Radiobutton(text="Чёрный", variable=color_var, value=0,
                font=(my_font, 16),
                activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=160, height=25, x=CANVAS_WIDTH + 10, y=30)

    Radiobutton(text="Красный", variable=color_var, value=1,
                font=(my_font, 16),
                activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=160, height=25, x=CANVAS_WIDTH + 10, y=55)

    Radiobutton(text="Синий", variable=color_var, value=2,
                font=(my_font, 16),
                activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=160, height=25, x=CANVAS_WIDTH + 10, y=80)

    Radiobutton(text="Зелёный", variable=color_var, value=3,
                font=(my_font, 16),
                activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=160, height=25, x=CANVAS_WIDTH + 170, y=30)

    Radiobutton(text="Жёлтый", variable=color_var, value=4,
                font=(my_font, 16),
                activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=160, height=25, x=CANVAS_WIDTH + 170, y=55)

    Radiobutton(text="Фиолетовый", variable=color_var, value=5, font=(my_font, 16),
                activebackground=my_fg_highlight_1, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_1,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=160, height=25, x=CANVAS_WIDTH + 170, y=80)

    Label(text="РЕЖИМ ЗАТРАВКИ", font=(my_font, 16, "bold"), bg=my_bg_highlight,
          fg=my_fg_highlight_2, justify=CENTER).place(width=MENU_WIDTH, height=30, x=CANVAS_WIDTH + 5, y=110)

    mode_var = BooleanVar()
    mode_var.set(1)

    Radiobutton(text="Без задержки", variable=mode_var, value=0, font=(my_font, 16),
                activebackground=my_fg_highlight_2, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_2,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=250, height=25, x=CANVAS_WIDTH + 10, y=145)

    Radiobutton(text="С задержкой", variable=mode_var, value=1, font=(my_font, 16),
                activebackground=my_fg_highlight_2, bg=my_bg_general,
                activeforeground=my_bg_general, fg=my_fg_highlight_2,
                selectcolor=my_bg_highlight, anchor="w"). \
        place(width=280, height=25, x=CANVAS_WIDTH + 170, y=145)

    Label(text="ПОСТРОЕНИЕ ТОЧКИ", font=(my_font, 16, "bold"), bg=my_bg_highlight,
          fg=my_fg_highlight_3, justify=CENTER).place(width=MENU_WIDTH, height=30, x=CANVAS_WIDTH + 5, y=180)

    Label(text="X                 Y", font=(my_font, 16), bg=my_bg_general,
          fg=my_fg_highlight_3).place(width=MENU_WIDTH, height=20, x=CANVAS_WIDTH + 5, y=213)

    x_entry = Entry(font=(my_font, 16), bg=my_bg_highlight, fg=my_fg_highlight_3, justify=CENTER)
    x_entry.place(width=125, height=27, x=CANVAS_WIDTH + 38, y=235)

    y_entry = Entry(font=(my_font, 16), bg=my_bg_highlight, fg=my_fg_highlight_3, justify=CENTER)
    y_entry.place(width=125, height=27, x=CANVAS_WIDTH + 163, y=235)

    Button(text="Построить точку", font=(my_font, 16),
           activebackground=my_bg_general, bg=my_fg_highlight_3,
           activeforeground=my_fg_highlight_3, fg=my_bg_general,
           command=lambda: draw_point(figures, img, color_var, x_entry, y_entry, points_listbox)). \
        place(width=250, height=30, x=CANVAS_WIDTH + 38, y=270)

    points_listbox = Listbox(font=(my_font, 16), bg=my_bg_highlight, fg=my_fg_highlight_3,
                             selectbackground=my_fg_highlight_3, justify=CENTER)
    points_listbox.place(width=250, height=125, x=CANVAS_WIDTH + 38, y=308)

    Button(text="Замкнуть фигуру", font=(my_font, 16),
           activebackground=my_bg_general, bg=my_fg_highlight_3,
           activeforeground=my_fg_highlight_3, fg=my_bg_general,
           command=lambda event="<3>": click_centre(event, figures, img, color_var)). \
        place(width=250, height=30, x=CANVAS_WIDTH + 38, y=441)

    Label(text="ПОСТРОЕНИЕ МЫШЬЮ",
          font=(my_font, 16, "bold"), bg=my_bg_highlight, fg=my_fg_highlight_4, justify=CENTER). \
        place(width=MENU_WIDTH, height=30, x=CANVAS_WIDTH + 5, y=478)

    Label(text="Левая- добавить точку",
          font=(my_font, 15), bg=my_bg_general, fg=my_fg_highlight_4). \
        place(height=30, width=MENU_WIDTH, x=CANVAS_WIDTH + 5, y=508)

    Label(text="Колесико - добавить затравку",
          font=(my_font, 15), bg=my_bg_general, fg=my_fg_highlight_4). \
        place(height=30, width=MENU_WIDTH, x=CANVAS_WIDTH + 5, y=536)

    Label(text="Правая - замкнуть фигуру",
          font=(my_font, 15), bg=my_bg_general, fg=my_fg_highlight_4). \
        place(height=30, width=MENU_WIDTH, x=CANVAS_WIDTH + 5, y=566)

    Label(text="Время затравки:", font=(my_font, 16), bg=my_bg_general,
          fg=my_fg_highlight_4).place(width=170, height=30, x=CANVAS_WIDTH + 15, y=593)

    time_entry = Entry(font=(my_font, 16), bg=my_bg_highlight, fg=my_fg_highlight_4, justify=CENTER)
    time_entry.place(width=120, height=27, x=CANVAS_WIDTH + 185, y=598)

    Button(text="Выполнить затравку", font=(my_font, 16),
           activebackground=my_bg_general, bg=my_fg_highlight_4,
           activeforeground=my_fg_highlight_4, fg=my_bg_general,
           command=lambda: fill_figure(figures, img, canvas, color_var, mode_var, time_entry, seed_pixel)). \
        place(width=246, height=30, x=CANVAS_WIDTH + 32, y=633)

    Button(text="Очистить экран", font=(my_font, 16),
           activebackground=my_bg_general, bg=my_fg_highlight_4,
           activeforeground=my_fg_highlight_4, fg=my_bg_general,
           command=lambda: clear_canvas(img, canvas, figures, time_entry, points_listbox, seed_pixel)). \
        place(width=246, height=30, x=CANVAS_WIDTH + 32, y=668)

    img = PhotoImage(width=CANVAS_WIDTH, height=CANVAS_HEIGHT)
    canvas.create_image(CANVAS_WIDTH // 2, CANVAS_HEIGHT // 2, image=img, state='normal')

    seed_pixel = [-1, -1]

    canvas.bind('<Button-1>',
                lambda event: click_left(event, figures, img, color_var, points_listbox))
    canvas.bind('<Button-3>',
                lambda event: click_centre(event, figures, img, color_var))
    canvas.bind('<Button-2>',
                lambda event: click_right(event, seed_pixel, img, color_var, points_listbox))

    x_entry.insert(0, "100")
    y_entry.insert(0, "100")

    window.mainloop()


if __name__ == "__main__":
    main()
