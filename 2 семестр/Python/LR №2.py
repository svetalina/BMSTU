import random
from time import time
from tkinter import *
from tkinter.messagebox import *

#Функция сортировки простыми вставками 
def insertion_sort(alist):
    for i in range(1, len(alist)):
        temp = alist[i]
        j = i - 1
        while (j >= 0 and temp < alist[j]):
            alist[j + 1] = alist[j]
            j = j - 1
        alist[j + 1] = temp
def show():
    showinfo("Информация об авторе и программе", "Программа сортирует массивы \
методом сортировки простыми вставками, а также считает время работы данного \
метода для массивов разного типа и разных размерностей.\nАвтор - \
Светличная Алина, студентка группы ИУ7-23Б")
    
#Функция обрабатывающая тестируемый массив
def mas_pr():
    txt3.delete(0, END)
    n = txt1.get()
    mas = txt2.get()
    if n == '' or mas == '':
        showerror("Ошибка ввода", "Необходимые значения не введены")
    else:
        n = int(n)
        mas = mas.split(' ')
        for i in range(len(mas)):
            mas[i] = int(mas[i])
        if len(mas) != n:
            showerror('Ошибка ввода','Введено недостаточное либо излишнее \
количество элементов массива')
        else:
            insertion_sort(mas)
            mas_str = ''
            for i in range(len(mas)):
                mas_str += str(mas[i]) + ' '
            txt3.insert(0, mas)

#Функция подсчета времени сортировок соответствующих массивов
def mas_ok():
    k = txt4.get()
    k = k.split(' ')
    if len(k) != 3:
        showerror('Ошибка ввода','Введено недостаточное либо излишнее \
количество элементов массива')
    else:
        #Изменение шапки таблицы на имеющиеся значения
        lbl5 = Label(window, text = k[0])
        lbl5.grid(column = 2, row = 6)
        lbl6 = Label(window, text = k[1])
        lbl6.grid(column = 3, row = 6)
        lbl7 = Label(window, text = k[2])
        lbl7.grid(column = 4, row = 6)

        #Создание таблицы
        txt5 = Entry(window, width = 32)
        txt5.grid(column = 2, row = 7)
        txt6 = Entry(window, width = 32)
        txt6.grid(column = 3, row = 7)
        txt7 = Entry(window, width = 32)
        txt7.grid(column = 4, row = 7)
        txt8 = Entry(window, width = 32)
        txt8.grid(column = 2, row = 8)
        txt9 = Entry(window, width = 32)
        txt9.grid(column = 3, row = 8)
        txt10 = Entry(window, width = 32)
        txt10.grid(column = 4, row = 8)
        txt11 = Entry(window, width = 32)
        txt11.grid(column = 2, row = 9)
        txt12 = Entry(window, width = 32)
        txt12.grid(column = 3, row = 9)
        txt13 = Entry(window, width = 32)
        txt13.grid(column = 4, row = 9)

        #Все переменные времени соответствуют следующему типу
        #time_номер размерности_номер массива в таблице_*номер тестового случая*
        mas = []
        for i in range(int(k[0])):
            mas.append(random.randint(-1000, 1000))

        time_n1_2_1 = time()
        insertion_sort(mas)
        time_n1_2_2 = time()
        time_n1_2 = time_n1_2_2 - time_n1_2_1

        time_n1_1_1 = time()
        insertion_sort(mas)
        time_n1_1_2 = time()
        time_n1_1 = time_n1_1_2 - time_n1_1_1

        mas = mas[::-1]
        time_n1_3_1 = time()
        insertion_sort(mas)
        time_n1_3_2 = time()
        time_n1_3 = time_n1_3_2 - time_n1_3_1


        mas = []
        for i in range(int(k[1])):
            mas.append(random.randint(-1000, 1000))

        time_n2_2_1 = time()
        insertion_sort(mas)
        time_n2_2_2 = time()
        time_n2_2 = time_n2_2_2 - time_n2_2_1

        time_n2_1_1 = time()
        insertion_sort(mas)
        time_n2_1_2 = time()
        time_n2_1 = time_n2_1_2 - time_n2_1_1

        mas = mas[::-1]
        time_n2_3_1 = time()
        insertion_sort(mas)
        time_n2_3_2 = time()
        time_n2_3 = time_n2_3_2 - time_n2_3_1


        mas = []
        for i in range(int(k[2])):
            mas.append(random.randint(-1000, 1000))

        time_n3_2_1 = time()
        insertion_sort(mas)
        time_n3_2_2 = time()
        time_n3_2 = time_n3_2_2 - time_n3_2_1

        time_n3_1_1 = time()
        insertion_sort(mas)
        time_n3_1_2 = time()
        time_n3_1 = time_n3_1_2 - time_n3_1_1

        mas = mas[::-1]
        time_n3_3_1 = time()
        insertion_sort(mas)
        time_n3_3_2 = time()
        time_n3_3 = time_n3_3_2 - time_n3_3_1

        #Заполнение таблицы
        txt5.insert(0, str(time_n1_1))
        txt6.insert(0, str(time_n2_1))
        txt7.insert(0, str(time_n3_1))
        txt8.insert(0, str(time_n1_2))
        txt9.insert(0, str(time_n2_2))
        txt10.insert(0, str(time_n3_2))
        txt11.insert(0, str(time_n1_3))
        txt12.insert(0, str(time_n2_3))
        txt13.insert(0, str(time_n3_3))


    
window = Tk()
window.title('Лабораторная работа №2')
window.geometry('1000x300')

#Тестируемый массив
lbl1 = Label(window, text = 'Введите размерность тестируемого массива:')
lbl1.grid(column = 1, row = 1)
txt1 = Entry(window, width = 32)
txt1.grid(column = 2, row = 1)

lbl2 = Label(window, text = 'Введите через пробел элементы тестируемого массива:')
lbl2.grid(column = 1, row = 2)
txt2 = Entry(window, width = 32)
txt2.grid(column = 2, row = 2)

enter1 = Button(window, text = 'Применить', command = lambda: mas_pr())
enter1.grid(column = 2, row = 4)#Кнопка обработки

lbl3 = Label(window, text = 'Отсортированный массив:')
lbl3.grid(column = 1, row = 3)
txt3 = Entry(window, width = 32)
txt3.grid(column = 2, row = 3)


#Окно и заголовок размерностей массивов
lbl4 = Label(window, text = 'Введите через пробел три размерности исследуемых \
массивов:')
lbl4.grid(column = 1, row = 5)
txt4 = Entry(window, width = 32)
txt4.grid(column = 2, row = 5)
enter1 = Button(window, text = 'OK', command = lambda: mas_ok())
enter1.grid(column = 3, row = 5)


lbl8 = Label(window, text = 'Упорядоченный массив: ')
lbl8.grid(column = 1, row = 7)
lbl9 = Label(window, text = 'Случайный массив: ')
lbl9.grid(column = 1, row = 8)
lbl10 = Label(window, text = 'Обратно упорядоченный массив: ')
lbl10.grid(column = 1, row = 9)


mainmenu = Menu(window)
mainmenu.add_command(label="Об авторе и программе", command = lambda: show())
window.config(menu = mainmenu)

window.mainloop()
