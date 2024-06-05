#Обработка библиотеки
import ctypes

lib = ctypes.CDLL('./libfunc.dll')

_fill_array = lib.fill_array
_fill_array.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_fill_array.restype = None

def fill_array(size):

    array = (ctypes.c_int * size)()
    _fill_array(array, size)

    return list(array)

_fill_array_after_even = lib.fill_array_after_even
_fill_array_after_even.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int,
    ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_fill_array_after_even.restype = ctypes.c_int

def fill_array_after_even(arr, size, size_res, num):

    arr = (ctypes.c_int * size)(*arr)
    arr_res = (ctypes.c_int * size_res)()

    num_el = _fill_array_after_even(arr, size, arr_res, size_res, num)
    
    if (num_el > size_res):
        arr_res = (ctypes.c_int * num_el)(*arr_res)
        _fill_array_after_even(arr, size, arr_res, num_el, num)

    return list(arr_res)


#Создание интерфейса
from tkinter import *
from tkinter.messagebox import *

def show():
    showinfo("Возможные функции",
    "1. Функция заполнения массива простыми числами\n\
2. Функция, которая переписывает элементы из одного массива в другой, добавляя после каждого чётного указанное число")

def process_fill_array_after_even():
    
    try:
        num = int(text_num.get())
    except:
        showerror("Ошибка ввода", "Некорректные символы в числе")
        return

    str_arr = text_array.get()

    try:
        arr = [int(el) for el in str_arr.split()]
    except:
        showerror("Ошибка ввода", "Некорректные символы в массиве")
        return


    res_arr = fill_array_after_even(arr, len(arr), len(arr), num)

    str_arr = ' '.join(str(el) for el in res_arr)
    
    text_output.delete(0, END)
    text_output.insert(0, str_arr)

def process_fill_array():

    try:
        size = int(text_size.get())
    except:
        showerror("Ошибка ввода", "Некорректные символы в обозначении размерности массива")

    if size <= 0:
        showerror("Ошибка ввода", "Некорректное значение размерности массива")

    arr = fill_array(size)
    str_arr = ' '.join(str(el) for el in arr)
    
    text_output.delete(0, END)
    text_output.insert(0, str_arr)

window = Tk()
window.title('Лабораторная работа №12')
window.geometry('2000x1000')

label_info = Label(window, text = 'Заполните те поля, которые необходимы для одной из возможных функций\n\
и нажмите соответсвующую кнопку: ')
label_info.grid(column = 0, row = 0)

label_size = Label(window, text = 'Введите количество элементов массива: ')
label_size.grid(column = 0, row = 1)

text_size = Entry(window, width = 30)
text_size.grid(column = 1, row = 1)

button_fill_array = Button(window, text = 'Функция №1', command = lambda: process_fill_array())
button_fill_array.grid(column = 2, row = 1)

label_array = Label(window, text = 'Введите массив через пробел: ')
label_array.grid(column = 0, row = 2)

text_array = Entry(window, width = 30)
text_array.grid(column = 1, row = 2)

label_num = Label(window, text = 'Ведите число, вставляемое в массив после четных чисел: ')
label_num.grid(column = 0, row = 3)

text_num = Entry(window, width = 30)
text_num.grid(column = 1, row = 3)

button_fill_array_after_even = Button(window, text = 'Функция №2', command = lambda: process_fill_array_after_even())
button_fill_array_after_even.grid(column = 2, row = 3)

label_output = Label(window, text = 'Получившийся массив: ')
label_output.grid(column = 3, row = 3)

text_output = Entry(window, width = 30)
text_output.grid(column = 4, row = 3)

mainmenu = Menu(window)
mainmenu.add_command(label = "Возможные функции", command = lambda: show())
window.config(menu = mainmenu)

window.mainloop()