#Программа вычисляет интеграл заданной функции методои парабол и методом левых
#прямоугольников
#Автор - Светличная Алина, ИУ7 - 13Б

from math import log
import scipy.integrate

def Fx(x): #Задание функции
    return(float(x ** 2)) 

#Проверка строки на явление числом типа float
def is_digit(str):
    if str.isdigit():
       return True
    else:
        try:
            float(str)
            return True
        except ValueError:
            return False

#Считывание начального значения отрезка и проверка его на необходимые
#условия
def beginA(): 
    a = input('Введите начальное значение отрезка интегрирования: ')

    #Проверка начального значения на явление числом типа float функцией
    #описанной выше
    while not is_digit(a):
        print('Введено не число')
        a = input('Введите начальное значение отрезка интегрирования: ')

    return(float(a))

#Считывание конечного значения отрезка и проверка его на необходимые
#условия
def endB():
    b = input('Введите конечное значение отрезка интегрирования: ')

    #Проверка конечного значения на явление числом типа float функцией
    #описанной выше
    while not is_digit(b):
        print('Введено не число')
        b = input('Введите конечное значение отрезка интегрирования: ')

    return(float(b))


#Считывание количество отрезков разбиения и проверка значения на необходимые
#условия
def segment1():
    n1 = input('Введите четное количество отрезков интегрирования: ')

    isok = True
    while isok:

        #Проверка количества отрезков на явление числом типа int
        while not n1.isnumeric():
            print('Введено не целое число')
            n1 = input('Введите количество отрезков интегрирования: ')

        n1 = int(n1)

        #Проверка количества отрезков на явление четным числом
        if n1 % 2 != 0:
            print('Введено не четное число')
            n1 = input('Введите четное количество отрезков интегрирования n1: ')
        else: isok = False

    return(n1)

#Считывание количество отрезков разбиения и проверка значения на необходимые
#условия
def segment2():
    n2 = input('Введите четное количество отрезков интегрирования n2: ')

    isok = True
    while isok:

        #Проверка количества отрезков на явление числом типа int
        while not n2.isnumeric():
            print('Введено не целое число')
            n2 = input('Введите количество отрезков интегрирования: ')

        n2 = int(n2)

        #Проверка количества отрезков на явление четным числом
        if n2 % 2 != 0:
            print('Введено не четное число')
            n2 = input('Введите четное количество отрезков интегрирования: ')
        else: isok = False

    return(n2)

#Считывание точности вычисления интеграла и проверка значения на необходимые
#условия
def writeps():
    #Вычисление интеграла с заданной точностью
    eps = float(input('Введите точность, с которой хотите посчитать интеграл \
    по методу левых прямоугольников:'))

    while eps <= 0:
        print('Введено не положительное число')
        eps = float(input('Введите точность, с которой хотите посчитать интеграл \
    по методу левых прямоугольников:'))

    return(eps)

#Учитывая, что не для каждой функции возможно определить интеграл с заданной
#точностью, для корректной работы программы необходимо спрашивать количество
#итераций, за которое программа попробует определить интеграл с точностью
def writeitr(): 
    itr = float(input('Введите максимальное количество итераций, отведенных под \
    поиск интеграла с заданной точностью:'))

    while itr <= 0:
        print('Введено не положительное число')
        itr = float(input('Введите максимальное количество итераций, отведенных под \
    поиск интеграла с заданной точностью:'))

    return(itr)

def printtabl(n1, n2, rec1n, rec2n, par1, par2): #Вывод таблицы

    for i in range(69):
        print('-', end = '')
        
    print()
    print('|', end = '')
    print('{:^20}'.format('Метод'), sep = '', end = '')
    print(' |', end = '')
    print('{:>12}'.format('N1 = '), sep = '', end = '')
    print('{:<9}'.format(n1),  sep = '', end = '')
    print(' |', end = '')
    print('{:>12}'.format('N2 = '), sep = '', end = '')
    print('{:<9}'.format(n2),  sep = '', end = '')
    print(' |')

    for i in range(69):
        print('-', end = '')

    print()
    print('|', end = '')
    print('{:^20}'.format('Левых прямоугольников'), sep = '', end = '')
    print('|', end = '')

    print('{:^21.9g}'.format(rec1), sep = '', end = '')
    print(' |', end = '')
    print('{:^21.9g}'.format(rec2), sep = '', end = '')
    print(' |', end = '')

    print()
    print('|', end = '')
    print('{:^20}'.format('Парабол(Симпсона)'), sep = '', end = '')
    print(' |', end = '')

    print('{:^21.9g}'.format(par1), sep = '', end = '')
    print(' |', end = '')
    print('{:^21.9g}'.format(par2), sep = '', end = '')
    print(' |')

    for i in range(69):
        print('-', end = '')
    print()
    
def leftrec(x, n, delx): #Метод левых прямоугольников
    fx = 0
    for i in range(n):
            fx = fx + Fx(x) #Суммирование всех значений функции в точке
            x += delx       #с высчитанным шагом

    #Вычисление площади прямоугольников, где delx - основание, fx - сумма всех
    #высот
    f0x = delx * fx

    return(f0x)


def parabola(x, n, delx): #Метод парабол
    f1x = 0; f2x = 0; f4x = 0
    for i in range(n + 1):
        fx = Fx(x) #Высчитывание значения функции в точке с высчитанным шагом
        x += delx

        #Распределение значений функции ао группам умножения в соответствии с
        #формулой
        if i == 0 or i == n: 
            f1x = f1x + fx
        elif i % 2 == 0:
            f2x += 2 * fx
        else:
            f4x += 4 * fx
       
    #Вычиление площади подпарабольного пространства
    f0x = delx / 3 * (f1x + f2x + f4x)

    return(f0x)

def delx(a, b, n): #Шаг значений x
    delx = (b - a) / n

    return(delx)

def epsilon(itr, a, b, n1, n2): #Вычисление интеграла с заданной точностью

    isok = True
    itr1 = 0
    
    while itr1 < itr:
        if isok or abs(I2n - In)>= eps:
            isok = False

            delx1 = delx(a, b, n1)
            In = leftrec(a, n1, delx1)


            delx2 = delx(a, b, n2)
            I2n = leftrec(a, n2, delx2)

            n1 = n1 * 2
            n2 = n2 * 2

        else: break

        itr1 += 1

    n1 = n1 // 2
    n2 = n2 // 2
    
    if abs(I2n - In) >= eps:
        print('Невозможно посчитать интеграл с заданной точностью')
    
    return(n1, n2, In, I2n)

def mistake(i_close1, i_close2, a, b, n1, n2): #Вычисление ошибок интегрирования
    f = lambda x: x ** 2
    integ = scipy.integrate.quad(f, a, b)
    i_exact = integ[0]

    mis_abs1 = abs(i_exact - i_close1)
    print('Абсолютная ошибка вычислений для ', n1, ' отрезков интегрирования:\
{:.8g}'.format(mis_abs1))

    mis_abs2 = abs(i_exact - i_close2)
    print('Абсолютная ошибка вычислений для ', n2, ' отрезков интегрирования:\
{:.8g}'.format(mis_abs2))

    mis_relat1 = abs(i_exact - i_close1) / i_close1
    print('Относительная ошибка вычислений для ', n1, ' отрезков интегрирования:\
{:.8g}'.format(mis_relat1))

    mis_relat2 = abs(i_exact - i_close2) / i_close2
    print('Относительная ошибка вычислений для ', n2, ' отрезков интегрирования:\
{:.8g}'.format(mis_relat2))
    



a = beginA()
b = endB()
n1 = segment1()
n2 = segment2()

delx1 = delx(a, b, n1)
delx2 = delx(a, b, n2)

rec1 = leftrec(a, n1, delx1)
rec2 = leftrec(a, n2, delx2)
par1 = parabola(a, n1, delx1)
par2 = parabola(a, n2, delx2)

printtabl(n1, n2, rec1, rec2, par1, par2)

eps = writeps()
itr = writeitr()

n1, n2, rec1, rec2 = epsilon(itr, a, b, n1, n2)

print()
print('Интеграл с заданной точностью удалось вычислить за ', n2, ' отрезков интегрирования')

mistake(rec1, rec2, a, b, n1, n2)


