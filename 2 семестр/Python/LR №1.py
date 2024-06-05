#Функция перевода целых чисел 10-чной сс в 3-чную
def turn10_3():
   expression = txt.get()

   #Проверка корректности вводимых данных
   for i in range(len(expression)):
      if not (expression[i].isdigit() or expression[i] == '-'):
         answer = 'Введены недопустимые символы'
         break
   else: 
      expression = int(expression)
      answer = ''
      while expression != 0:
         if expression % 3 == 2:
            answer += '-'
            expression = expression // 3 + 1
         elif expression % 3 == 1:
            answer += '+'
            expression = expression // 3
         else:
            answer += '0'
            expression = expression // 3

      answer = answer[::-1]

   txt2.delete(0, END)
   txt2.insert(0, str(answer))


#Функция перевода целых чисел 3-чной сс в 10-чную
def turn3_10():
   expression = txt.get()

   #Проверка корректности вводимых данных
   for i in range(len(expression)):
      if not expression[i] in ['+', '-', '0']:
         answer = 'Введены недопустимые символы'
         break
   else:
      answer = 0
      k = 0
      for i in range(len(expression) - 1, -1, -1):
         if expression[i] == '+':
            answer += 1 * 3**(k)
         elif expression[i] == '-':
            answer += -1 * 3**(k)

         k+=1

   txt2.delete(0, END)
   txt2.insert(0, str(answer))




from tkinter import *
from tkinter.messagebox import *

#Функция обработки нажатия кнопок "чисел"
def press(num):
   txt.insert(END, num)


window = Tk()
window.title('Лабораторная работа №1')
window.geometry('340x200')

#Создание "числовых" кнопок
plus = Button(window, text = '+', command = lambda: press('+'))
plus.grid(column = 1, row = 3)

minus = Button(window, text = '-', command = lambda: press('-'))
minus.grid(column = 2, row = 3)

zero = Button(window, text = '0', command = lambda: press(0))
zero.grid(column = 3, row = 3)

one = Button(window, text = '1', command = lambda: press(1))
one.grid(column = 1, row = 4)

two = Button(window, text = '2', command = lambda: press(2))
two.grid(column = 2, row = 4)

three = Button(window, text = '3', command = lambda: press(3))
three.grid(column = 3, row = 4)

four = Button(window, text = '4', command = lambda: press(4))
four.grid(column = 1, row = 5)

fife = Button(window, text = '5', command = lambda: press(5))
fife.grid(column = 2, row = 5)

six = Button(window, text = '6', command = lambda: press(6))
six.grid(column = 3, row = 5)

seven = Button(window, text = '7', command = lambda: press(7))
seven.grid(column = 1, row = 6)

eight = Button(window, text = '8', command = lambda: press(8))
eight.grid(column = 2, row = 6)

nine = Button(window, text = '9', command = lambda: press(9))
nine.grid(column = 3, row = 6)

#Создание конопок "действий"
in3 = Button(window, text = '10->3', command = lambda: turn10_3())
in3.grid(column = 1, row = 7)

in10 = Button(window, text = '3->10', command = lambda: turn3_10())
in10.grid(column = 3, row = 7)


#Создание однострочных полей ввода и вывода
lbl = Label(window, text = 'Поле ввода:')
lbl.grid(column = 1, row = 1)

txt = Entry(window, width = 32)
txt.grid(column = 2, row = 1)

lbl2 = Label(window, text = 'Поле вывода:')
lbl2.grid(column = 1, row = 2)

txt2 = Entry(window, width = 32)
txt2.grid(column = 2, row = 2)




#Функция вывода информации об авторе и программе
def author():
   showinfo("Информация об авторе и программе", "Программа переводит числа из \
10-чной системы счисления в 3-ичную симметричную и наоборот.\nАвтор - \
Светличная Алина, студентка группы ИУ7-23Б")


#Функции очистки полей
def clear_write():
   txt.delete(0, END)

def clear_print():
   txt2.delete(0, END)

def clear_double():
   txt.delete(0, END)
   txt2.delete(0, END)
   

mainmenu = Menu(window) 
window.config(menu = mainmenu) 

#Меню "Заданные действия"
actionmenu = Menu(mainmenu, tearoff = 0)
actionmenu.add_command(label="Перевод из 10 в 3", command = lambda: \
turn10_3())

actionmenu.add_command(label="Перевод из 3 в 10", command = lambda: \
turn3_10())
mainmenu.add_cascade(label="Заданные действия", menu = actionmenu)

#Меню "Очистка полей"
helpmenu = Menu(mainmenu, tearoff = 0)
helpmenu.add_command(label="Очистка поля ввода", command = lambda: \
clear_write())

helpmenu.add_command(label="Очистка поля вывода", command = lambda: \
clear_print())

helpmenu.add_command(label="Очистка обоих полей", command = lambda: \
clear_double())
mainmenu.add_cascade(label="Очистка полей", menu = helpmenu)

#Меню "Об авторе"
mainmenu.add_command(label="Об авторе", command = author)

window.mainloop()
