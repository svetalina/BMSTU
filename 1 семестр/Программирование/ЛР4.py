#Программа высчитывает значения нескольких функций и выводит один из их графиков
#Автор - Светличная Алина, ИУ7 - 13Б

#Блок ввода входных данных
n2 = n1 = n = float(input('Введите начальное значение интервала: '))
k = float(input('Введите конечное значение интервала: '))
sh = float(input('Введите шаг высчитывания значений функции: '))

#Блок вывода заглавий таблицы
print('{:14s}{:15s}{:16s}{:16s}{:2s}'.format('','y', 'z1', 'z2', 'z3'))
print()

maxz2 = minz2 = 2 * n**3 + 3 * n**2 - 6 * n + 1.5
maxz3 = minz3 = (abs((n * 2**n - 1)*(2 * n**3 + 3 * n**2 - 6 * n + 1.5)))**(1/3)
y1 = y2 = n

#Вычисление значений заданных функций
from math import e
if sh > 0:
    while n1 <= k :
    
        z1 = n1 * 2**n1 - 1
        z2 = 2 * n1**3 + 3 * n1**2 - 6 * n1 + 1.5
        z3 = (abs(z1 * z2))**(1/3)

        print('{:15.4g} {:15.4g} {:15.4g} {:15.4g}'.format(n1, z1, z2, z3))

        #Поиск минмального и максимального значения функции z3
        if z3 > maxz3:
            maxz3 = z3
            y1 = n1
        elif z3 < minz3:
            minz3 = z3
            y2 = n1

        #Поиск минмального и максимального значения функции z2
        if z2 > maxz2:
            maxz2 = z2
        elif z2 < minz2:
            minz2 = z2

        n1 = round(n1 + sh, 4)
else: 
    while n1 >= k :
    
        z1 = n1 * 2**n1 - 1
        z2 = 2 * n1**3 + 3 * n1**2 - 6 * n1 + 1.5
        z3 = (abs(z1 * z2))**(1/3)

        print('{:15.4g} {:15.4g} {:15.4g} {:15.4g}'.format(n1, z1, z2, z3))

        #Поиск минмального и максимального значения функции z3
        if z3 > maxz3:
            maxz3 = z3
            y1 = n1
        elif z3 <= minz3:
            minz3 = z3
            y2 = n1

        #Поиск минмального и максимального значения функции z2
        if z2 > maxz2:
            maxz2 = z2
        elif z2 < minz2:
            minz2 = z2

        n1 = round(n1 + sh, 4)
        
#Блок вывода   
print()   
print ('Минимальное значение функции z3 = {:.7g}'.format(minz3),\
', достигающееся при y = ', y2)
print ('Максимальное значение функции z3 = {:.7g}'.format(maxz3),\
', достигающееся при y = ', y1)
print()








z = int(input('Введите согласно таблице порядковый номер функции, график которой\
Вы желаете видеть на экране, допустимы только 2 и 3 функции: '))

#Проверка корректности введенных данных
while z != 2 and z != 3 :
    print('Введены некорректные данные')
    z = int(input('Введите согласно таблице порядковый номер функции, график которой\
    Вы желаете видеть на экране, допустимы только 2 и 3 функции: '))

zs = int(input('Введите количество засечек от 4 до 8 по осям системы координат: '))

#Проверка корректности введенных данных
while zs < 4 or zs > 8:
    print('Введено недопустимое количество засечек')
    zs = int(input('Введите количество засечек от 4 до 8 по осям системы координат: '))






#Функция z3
if z == 3:
    dminz3 = minz3
    mas = (maxz3 - minz3) / (10 * (zs-1))#Вычисление шага засечек по оси z

    #Рассмотрение варианта, при котором отрезку значений y  не принадлежит 0
    if (n2 > 0 and (n1 - sh) > 0) or (n2 < 0 and (n1 -sh) < 0):

        print('       ', end = '')
        #Вывод значений засечек на оси z
        sch = 0
        while sch != zs:
            print('{:<10.2g}'.format(minz3), end= '')
            minz3 = minz3 + mas * 10
            sch+=1
        
        #Вывод оси z 
        print()   
        print('      + |---------|', end = '')
        for i in range(zs-2):
            print('---------|', end = '' )
        print('> Z')

    #Рассмотрение варианта, при котором начальное значение отрезка y
    #меньше конечного значения этого отрезка
    if sh > 0:
        while n <= k :

            z3 = (abs((n * 2**n - 1)*(2 * n**3 + 3 * n**2 - \
            6 * n + 1.5)))**(1/3)
            
            cz3 = round((z3 - dminz3) / mas)
        
            if n == 0:
            
                #Вывод значений засечек на оси z
                sch = 0
                print('{:6s}'.format(' '), end= '')
                while sch != zs:
                    print('{:<10.4g}'.format(minz3), end= '')
                    minz3 = minz3 + mas *10
                    sch+=1
                
                print()
                print('{:>6g}'.format(0), end = '')
                
                #Вывод оси z 
                for i in range(cz3):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                    
                print('*', end = '')#Вывод значения на оси z при y = 0

                for i in range(cz3, (zs - 1)*10):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                print('> Z')
            
            else:
                print('{:>6g}'.format(n), end = '')
                print('|', end = ' ')
            
                for i in range(cz3):
                    print(' ', end = '')
                print('*')

            n = round(n + sh, 4)

    #Рассмотрение варианта, при котором начальное значение отрезка y
    #больше конечного значения этого отрезка
    else:
        while n >= k :
            z3 = (abs((n * 2**n - 1)*(2 * n**3 + 3 * n**2 - \
            6 * n + 1.5)))**(1/3)
            
            cz3 = round((z3 - dminz3) / mas)
        
            if n == 0:
            
                #Вывод значений засечек на оси z
                sch = 0
                print('{:6s}'.format(' '), end= '')
                while sch != zs:
                    print('{:<10.4g}'.format(minz3), end= '')
                    minz3 = minz3 + mas *10
                    sch+=1
                
                print()
                print('{:>6g}'.format(0), end = '')
                
                #Вывод оси z  
                for i in range(cz3):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                    
                print('*', end = '')#Вывод значений \\\ на оси z

                #Вывод оси z после значения функции при y = 0
                for i in range(cz3, (zs - 2)*10):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                print('> Z')
            
            else:
                
                #Вывод оси y
                print('{:>6g}'.format(n), end = '')
                print('|', end = ' ')

                #Вывод значений оси y
                for i in range(cz3):
                    print(' ', end = '')
                print('*')

            n = round(n + sh, 4)
        
    print('      ᐯ')
    print('      Y')






#Функция z2
elif z == 2:
    dminz2 = minz2
    mas = (maxz2 - minz2) / (10 * (zs-1))#Вычисление шага засечек по оси z

    #Рассмотрение варианта, при котором отрезку значений y  не принадлежит 0 
    if (n2 > 0 and (n1 - sh) > 0) or (n2 < 0 and (n1 -sh) < 0):

        print('       ', end = '')
        #Вывод значений засечек на оси z
        sch = 0
        while sch != zs:
            print('{:<10.2g}'.format(minz2), end= '')
            minz2 = minz2 + mas * 10
            sch+=1
        
        #Вывод оси z
        print()   
        print('      + |---------|', end = '')
        for i in range(zs-2):
            print('---------|', end = '' )
        print('> y')

    #Рассмотрение варианта, при котором начальное значение отрезка y
    #меньше конечного значения этого отрезка
    if sh > 0:
        while n <= k :

            z2 = 2 * n**3 + 3 * n**2 - 6 * n + 1.5
        
            cz2 = round((z2 - dminz2) / mas)
        
            if n == 0:
            
                #Вывод значений засечек на оси z
                sch = 0
                print('{:6s}'.format(' '), end= '')
                while sch != zs:
                    print('{:<10.4g}'.format(minz2), end= '')
                    minz2 = minz2 + mas *10
                    sch+=1
                
                print()
                print('{:>6g}'.format(0), end = '')
                
                #Вывод оси z 
                for i in range(cz2):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                    
                print('*', end = '')#Вывод значения на оси z при y = 0

                #Вывод оси z после значения функции при y = 0
                for i in range(cz2, (zs-1)*10):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                print('> Z')
            
            else:
                
                #Вывод оси y
                print('{:>6g}'.format(n), end = '')
                print('|', end = ' ')

                #Вывод значений оси y
                for i in range(cz2):
                    print(' ', end = '')
                print('*')

            n = round(n + sh, 4)

    #Рассмотрение варианта, при котором начальное значение отрезка y
    #больше конечного значения этого отрезка
    else:
        while n >= k :
            z2 = 2 * n**3 + 3 * n**2 - 6 * n + 1.5
        
            cz2 = round((z2 - dminz2) / mas)

            if n == 0:
            
                #Вывод значений засечек на оси z
                sch = 0
                print('{:6s}'.format(' '), end= '')
                while sch != zs:
                    print('{:<10.4g}'.format(minz2), end= '')
                    minz2 = minz2 + mas *10
                    sch+=1
                
                print()
                print('{:>6g}'.format(0), end = '')
                
                #Вывод оси z 
                for i in range(cz2):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                    
                print('*', end = '') #Вывод значения на оси z при y = 0

                #Вывод оси z после значения функции при y = 0
                for i in range(cz2, (zs-1)*10):
                    if i % 10 == 0:
                        print('|', end = '')
                    else: print('-', end = '')
                print('> Z')
            
            else:
                
                #Вывод оси y
                print('{:>6g}'.format(n), end = '')
                print('|', end = ' ')

                #Вывод занчений оси  y
                for i in range(cz2):
                    print(' ', end = '')
                print('*')

            n = round(n + sh, 4)
        
    print('      ᐯ')
    print('      Y')

