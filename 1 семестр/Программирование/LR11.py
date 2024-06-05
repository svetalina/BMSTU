#Программа работает с определенными функциями меню
#Автор - Светличная Алина, ИУ7 - 13Б

import pickle
import os.path

menu = None

while menu != '0':

    #Объявление функций меню
    print('1 - Создание базы данных',
          '2 - Добавление записи в базу данных',
          '3 - Вывод всей базы данных',
          '4 - Поиск записи по одному полю',
          '5 - Поиск записи по двум полям',
          '0 - Выход', sep = '\n')

    menu = input()


    if menu == '0':
        print('Выход')

            

    if menu == '1':
        name_file = input('Введите название базы данных: ') 
        number_key = int(input('Введите количество записей создаваемой базы \
данных: '))
        while number_key < 0:
            number_key = int(input('Введено некорректное значение, введите\
количество записей создаваемой базы данных еще раз: '))

        number_pole = int(input('Введите количество полей записей: '))

        key = []
        print('Введите построчно названия полей записей:')
        for i in range(number_pole):
            key.append(input())

        f = open(name_file + '.bin', 'wb')
        for i in range(number_key):
            print('Введите построчно значений полей', i + 1, 'записи: ')
            d = {}
            for j in range(number_pole):
                d[key[j]] = input()

            pickle.dump(d, f)
        
        if number_key == 0:
            d = {}
            for i in range(len(key)):
                d[key[i]] = None

            pickle.dump(d, f)

        f.close()
 

    if menu == '2':
        name_file = input('Введите название базы данных, с которой хотите \
работать: ')
        while not(os.path.isfile(name_file + '.bin')):
            name_file = input('Файл с таким названием не найден, введите \
название еще раз либо создайте базу данных, вызвав команду "1": ')

        #Считывание имеющегося словаря БД
        f = open(name_file + '.bin', 'rb+')

        isok = True
        while isok:
            try:
                d_mas = pickle.load(f)
            except: isok = False

        answer = None
        while answer != 'нет':
            d = {}
            print('Введите построчно значений полей записи: ')

            for key in d_mas:
                d[key] = input()

            pickle.dump(d, f)

            answer = input('Хотите добавить еще одну запись? ')

        print('База данных обновлена')
        f.close()


    if menu == '3':
        name_file = input('Введите название базы данных, с которой хотите \
работать: ')
        while not(os.path.isfile(name_file + '.bin')):
            name_file = input('Файл с таким названием не найден, введите \
название еще раз либо создайте базу данных, вызвав команду "1": ')
            
        f = open(name_file + '.bin', 'rb')
        print('В файле базы данных содержится следующая информация: ')

        k = 1
        isok = True
        while isok:
            try:
                d = pickle.load(f)

                if None in d.values():
                    break
                
                print('Запись №', k, ':', sep = '', end = ' ')
                for key in d:
                    print(key, ':', sep = '',  end = ' ')
                    print(d[key], end = ' ')
                print()

                k += 1

            except: isok = False

        if k == 1:
            print('База данных пуста')

    if menu == '4':
        name_file = input('Введите название базы данных, с которой хотите \
работать: ')
        while not(os.path.isfile(name_file + '.bin')):
            name_file = input('Файл с таким названием не найден, введите \
название еще раз либо создайте базу данных, вызвав команду "1": ')
            
        f = open(name_file + '.bin', 'rb')

        pole = input('Введите поле, по которому хотите совершить посик: ')
        print('По заданному поиску были обнаружены следующие записи:')

        k = 1
        k2 = 0
        isok = True
        while isok:
            try:
                d = pickle.load(f)

                if pole in d.values():
                    print('Запись №', k, ':', sep = '', end = ' ')
                    for key in d:
                        print(key, ':', sep = '',  end = ' ')
                        print(d[key], end = ' ')
                    print()

                    k2 += 1

                k += 1

            except: isok = False

        if k == 1 or k2 == 0:
            print('По заданному запросу ничего не найдено')
            
    if menu == '5':
        name_file = input('Введите название базы данных, с которой хотите \
работать: ')
        while not(os.path.isfile(name_file + '.bin')):
            name_file = input('Файл с таким названием не найден, введите \
название еще раз либо создайте базу данных, вызвав команду "1": ')
            
        f = open(name_file + '.bin', 'rb')
        d_mas = pickle.load(f)
        f.seek(0)

        pole_1 = input('Введите первое поле, по которому хотите совершить \
посик: ')
        pole_2 = input('Введите второе поле, по которому хотите совершить \
посик: ')
        print('По заданному поиску были обнаружены следующие записи:')
        
        k = 1
        k2 = 0
        isok = True
        while isok:
            try:
                d = pickle.load(f)

                if pole_1 in d.values() and pole_2 in d.values():
                    print('Запись №', k, ':', sep = '', end = ' ')
                    for key in d:
                        print(key, ':', sep = '',  end = ' ')
                        print(d[key], end = ' ')
                    print()

                    k2 += 1

                k += 1

            except: isok = False

        if k == 1 or k2 == 0:
            print('По заданному запросу ничего не найдено')
        
