from tkinter import *
from sympy import *
from tkinter.messagebox import *
import matplotlib.pyplot as plt
import numpy as np
from math import fabs, sin

f = lambda x: x**2 -4

f_one = lambda x: 2*x
f_two = lambda x: 2
p = 1
decesion = nan

def show():
    showinfo("Пояснения обработки ошибочных случаев","Если код ошибки равен \
нулю, то ошибка не была найдена, если же он отличен от нуля, то код ошибки \
- порядковый номер ошибочного случая.")

def error(a):
    showerror("Ошибка ввода","Недопустимые символы в %s" %(a))
    return -1
    
window = Tk()
window.title('Лабораторная работа №3')
window.geometry('2000x1000')


def d_from_f(x_n, number):
    if number == 2:
        x = -sin(x_n)
    if number == 1:
        x = cos(x_n)
    return x

def kink():
    if (decesion == nan):
        return []

    if (p == 0):
        a = -10
        b = 10

        x1 = []
        k = 0
        n = 0
        while decesion * k < b:
            x1.append(decesion * k)
            k += 1

        while a < decesion * n:
            x1.append(decesion * n)
            n -= 1

        return x1

    return decesion

def func_root(a0, b0, eps, code):

    end = b0
    t = a0
    while(f_one(t) * f_two(t) <= 0):
        t += 1;

    b1 = t - f(t)/ f_one(t)
    a1 = a0 - f(a0)*(b0 - a0) / (f(b0) - f(a0))
    x1 = (a1 + b1) / 2
    iteration = 1

    if (x1 > end):
        return a1, iteration, code + 1

    while ((iteration == 1 or (fabs(x1 - x0) > eps and r_var.get() == 0) or (fabs(f(x1)) > eps and r_var.get() == 1))):
        if iteration > 100:
            code += 1
            break
        
        a0 = a1
        b0 = b1
        a1 = a0 - f(a0)*(b0 - a0) / (f(b0) - f(a0))
        b1 = b0 - f(b0)/ f_one(b0)
        
        x0 = x1        
        x1 = (a1 + b1) / 2

        print(x0, x1)
        iteration += 1

    return x0, iteration, code

def apply():
    error_ok = 0
    try:
        a = float(txt1.get())
    except:
        error_ok = error("значении левого края интервала")

    try:
        b = float(txt2.get())
    except:
        error_ok = error("значении правого края интервала")

    try:
        h = float(txt3.get())
    except:
        error_ok = error("значении шага")

    try:
        eps = float(txt4.get())
    except:
        error_ok = error("значении точности вычисления")

    if a >= b:
        showerror("Ошибка ввода", "Указанный интервал не может быть обработан")
        error_ok = -1

    if error_ok != -1:
        lbl6 = Label(window, text = 'Номер корня')
        lbl6.grid(column = 1, row = 7)

        lbl7 = Label(window, text = 'Отрезок')
        lbl7.grid(column = 2, row = 7)

        lbl8 = Label(window, text = 'Корень на отрезке')
        lbl8.grid(column = 3, row = 7)

        lbl9 = Label(window, text = 'Значение функции в корне')
        lbl9.grid(column = 4, row = 7)

        lbl10 = Label(window, text = 'Количество итераций')
        lbl10.grid(column = 5, row = 7)

        lbl11 = Label(window, text = 'Код ошибки')
        lbl11.grid(column = 6, row = 7)
        
        k = 8
        code = 0
        while (a < b):
            if f(a)*f(a + h) < 0:
                root_n, iteration, code_new = func_root(a, a + h, eps, code)

                if code_new == code:
                    code_new = 0
                else:
                    code = code_new


                txt5 = Entry(window, width = 32)
                txt5.grid(column = 1, row = k)
                txt5.insert(0, k - 7)

                txt6 = Entry(window, width = 32)
                txt6.grid(column = 2, row = k)
                txt6.insert(0, '[%g; %g]' % (a, a + h))

                txt7 = Entry(window, width = 32)
                txt7.grid(column = 3, row = k)
                txt7.insert(0, '%g' % (root_n))

                txt8 = Entry(window, width = 32)
                txt8.grid(column = 4, row = k)
                txt8.insert(0, '%.0e' % (f(root_n)))

                txt9 = Entry(window, width = 32)
                txt9.grid(column = 5, row = k)
                txt9.insert(0, '%d' % (iteration))

                txt10 = Entry(window, width = 32)
                txt10.grid(column = 6, row = k)
                txt10.insert(0, '%d' % (code_new))

                k += 1

            a += h 
        
lbl1 = Label(window, text = 'Введите левую границу отрезка: ')
lbl1.grid(column = 1, row = 1)
txt1 = Entry(window, width = 32)
txt1.grid(column = 2, row = 1)

lbl2 = Label(window, text = 'Введите правую границу отрезка: ')
lbl2.grid(column = 1, row = 2)
txt2 = Entry(window, width = 32)
txt2.grid(column = 2, row = 2)

lbl3 = Label(window, text = 'Введите шаг: ')
lbl3.grid(column = 1, row = 3)
txt3 = Entry(window, width = 32)
txt3.grid(column = 2, row = 3)

lbl4 = Label(window, text = 'Введите точность вычисления: ')
lbl4.grid(column = 1, row = 4)
txt4 = Entry(window, width = 32)
txt4.grid(column = 2, row = 4)

lbl5 = Label(window, text = 'Cпособ высчитывания корня с точностью: ')
lbl5.grid(column = 1, row = 5)

r_var = BooleanVar()
r_var.set(0)
r1 = Radiobutton(text = 'По двум значениям функции', variable = r_var, value = 0)
r1.grid(column = 2, row = 5)

r2 = Radiobutton(text = 'По одному значению функции', variable = r_var, value = 1)
r2.grid(column = 3, row = 5)

enter1 = Button(window, text = 'Применить', command = lambda: apply())
enter1.grid(column = 2, row = 6)

mainmenu = Menu(window)
mainmenu.add_command(label="Коды ошибки", command = lambda: show())
window.config(menu = mainmenu)

kink_not_func = kink()

x1 = kink_not_func

y1 = [0] * len(kink_not_func)
for i in range(len(kink_not_func)):
    y1[i] = f(x1[i])    

plt.title('')
x = np.linspace(-10, 10, 1000)

y = [0] * len(x)
for i in range(len(x)):
    y[i] = f(x[i])
    
plt.plot(x, y, label = 'Function graph')
plt.scatter(x1, y1, color = 'orange', s = 40, marker = 'o')

plt.legend(loc = 1)
ax = plt.gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))
plt.show()


window.mainloop()
