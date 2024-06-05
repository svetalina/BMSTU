from tkinter import *
from tkinter.messagebox import *
from math import sqrt, fabs
import matplotlib.pyplot as plt

def show():
    showinfo("Интструкция к выводу","На первой строке вводится количество \
рассматриваемых точек (целое число), которые образуют треугольник, а \
следовательно их должно быть не менее 3. Далее числа (целые и \
вещественные) рассматриваются как пары координат x и y независимо от способа \
разделения (допустимые - пробел, в том числе несколько, а также новая строка). \
Если введенных координат больше, чем количество введенных точек, то будут \
рассматриваться первые n координат.")


def find_min_in_triangle(x1, y1, x2, y2, x3, y3):
    len_12 = sqrt((x2 - x1)**2 + (y2 - y1)**2)
    len_23 = sqrt((x2 - x3)**2 + (y2 - y3)**2)
    len_31 = sqrt((x3 - x1)**2 + (y3 - y1)**2)

    p = (len_12 + len_23 + len_31) / 2
    S = sqrt(p * (p - len_12) * (p - len_23) * (p - len_31))

    if S < 1e-3:
        return 0, 0, 0, 0, 0

    S0 = S / (len_12 + len_31)
    r1 = S0 * fabs(len_12 - len_31)

    S0 = S / (len_12 + len_23)
    r2 = S0 * fabs(len_12 - len_23)
    
    S0 = S / (len_23 + len_31)
    r3 = S0 * fabs(len_23 - len_31)

    if r1 < r2 and r1 < r3:
        x0 = x1
        y0 = y1

        k = len_12 /(len_12 + len_31)
        x_vector = k * (x3 - x2)
        y_vector = k * (y3 - y2)

        x_b = x_vector + x2
        y_b = y_vector + y2

    if r2 < r1 and r2 < r3:
        x0 = x2
        y0 = y2

        k = len_23 /(len_23 + len_12)
        x_vector = k * (x1 - x3)
        y_vector = k * (y1 - y3)

        x_b = x_vector + x3
        y_b = y_vector + y3

    if r3 < r1 and r3 < r2:
        x0 = x3
        y0 = y3
        
        k = len_31 /(len_23 + len_31)
        x_vector = k * (x2 - x1)
        y_vector = k * (y2 - y1)

        x_b = x_vector + x1
        y_b = y_vector + y1


    return (min(r1, r2, r3), x0, y0, x_b, y_b)

def matrix():

    everything = text.get(1.0, END).split()

    try: size = int(everything[0])
    except:
        showerror("Ошибка ввода", "Неверный формат значения \
количества точек")
        return

    if size < 3:
        showerror("Ошибка ввода", "Задано слишком малое количество точек")
        return

    x = []
    y = []
    try:
        for i in range(1, size * 2, 2):
            x.append(float(everything[i]))
            y.append(float(everything[i + 1]))
            
    except:
        showerror("Ошибка ввода", "Неверный формат координат точек")
        return
    
    lbl10 = Label(window, text = '', font = "Arial 11")
    lbl10.grid(column = 0, row = 4, sticky = E + W)

    lbl20 = Label(window, text = '', font = "Arial 11")
    lbl20.grid(column = 1, row = 4)

    lbl30 = Label(window, text = '', font = "Arial 11")
    lbl30.grid(column = 2, row = 4)

    lbl1 = Label(window, text = 'Номер точки', font = "Arial 11")
    lbl1.grid(column = 0, row = 5, sticky = E + W)

    lbl2 = Label(window, text = 'X', font = "Arial 11")
    lbl2.grid(column = 1, row = 5)

    lbl3 = Label(window, text = 'Y', font = "Arial 11")
    lbl3.grid(column = 2, row = 5)

    for i in range(size):
        txt1 = Entry(window, width = 32)
        txt1.grid(column = 0, row = i + 6, sticky = W + E)
        txt1.insert(0, i + 1)

        txt2 = Entry(window, width = 32)
        txt2.grid(column = 1, row = i + 6)
        txt2.insert(0,  x[i])

        txt3 = Entry(window, width = 32)
        txt3.grid(column = 2, row = i + 6)
        txt3.insert(0, y[i])

    minimum = 1e3
    for i in range(size):
        for j in range(size):
            for k in range(size):

                if(i == j or i == k or j == k):
                    break

                min_find, x0, y0, x_b, y_b = find_min_in_triangle(x[i], y[i], x[j], y[j], \
                                                x[k], y[k],)
                if min_find == 0:
                    break

                if minimum > min_find:
                    minimum = min_find
                    I = i
                    J = j
                    K = k
                    X0 = x0
                    Y0 = y0
                    X_B = x_b
                    Y_B = y_b

    if minimum == 1e3:
        showinfo("Ошибка вычислений", "Среди заданных точек нет треугольника")

    x1 = []
    y1 = []
    x1.append(x[I])
    x1.append(x[J])
    x1.append(x[K])
    y1.append(y[I])
    y1.append(y[J])
    y1.append(y[K])

    x2 = []
    y2 = []
    x2.append(x[I])
    x2.append(x[K])
    y2.append(y[I])
    y2.append(y[K])

    x3 =[]
    y3 = []
    x3.append(X0)
    x3.append(X_B)
    y3.append(Y0)
    y3.append(Y_B)
    
    plt.plot(x1, y1, color = "blue")
    plt.plot(x2, y2, color = "blue")
    plt.plot(x3, y3, color = "red")

    plt.show()

window = Tk()
window.title('Лабораторная работа №4')
window.geometry('2000x1000')

lbl2 = Label(window, text = 'Введите данные по \
инструкции: ', font = "Arial 11", height = 2)
lbl2.grid(column = 0, row = 0)

text = Text(width = 30, height = 10)
text.grid()

enter1 = Button(window, text = 'Применить', command = lambda: matrix())
enter1.grid(column = 0, row = 2)

mainmenu = Menu(window)
mainmenu.add_command(label = "Инструкция ввода", command = lambda: show())
window.config(menu = mainmenu)

window.mainloop()
