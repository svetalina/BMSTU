#Программа работает с определенными функциями меню
#Автор - Светличная Алина, ИУ7 - 13Б

const = 79 #Константа необходимая для выравнивания текста

def array_in_list(array): #Преобразование масиива строк в строку

    line = ''
    for i in range(len(array)):
        line += array[i]
        if i != len(array) - 1:
            line += ' '

    return(line)

array = ['Ни']

line = ''
menu = None

while menu != '0':

    #Объявление функций меню
    print('1 - Выравнивание текста по левому краю',\
          '2 - Выравнивание текста по правому краю',\
          '3 - Выравнивание текста по ширине',\
          '4 - Удаление заданного слова',\
          '5 - Замена одного слова другим во всем тексте',\
          '6 - Вычисление арифметического выражения',\
          '7 - Поиск наиболее часто встречающегося слова в каждом предложении',\
          '0 - Выход', sep = '\n')
    
    menu = input()

    if menu == '0':
        print('Выход')


    
    elif menu == '1':

        #Преобразование строки в список
        if line == '':
            print('На данный момент текст отсутствует, поэтому будет заполнен \
занаво')
            line = list(array_in_list(array))

        zline = line

        while line != '':

            #Алгоритм поиска количества слов, которые смогут поместиться на
            #одной строке
            if len(line) > const: 
                for i in range(const, 0, -1):
                    if line[i] == ' ':
                        number = i
                        break

            else:
                number = len(line)
                
            #Вывод выравненного текста
            for i in range(number):
                print(line[i], end = '')
            print()

            #Алгоритм удаления выведенных строк
            if number == len(line):
                line = ''
            else:
                for i in range(number + 1):
                    line.pop(0)
        line = zline

    elif menu == '2':

        if line == '':
            print('На данный момент текст отсутствует, поэтому будет заполнен \
занаво')
            line = list(array_in_list(array))

        zline = line

        while line != '':

            #Алгоритм поиска количества слов, которые смогут поместиться на
            #одной строке
            if len(line) > const:
                for i in range(const, 0, -1):
                    if line[i] == ' ':
                        number = i
                        break

            else:
                number = len(line)

            #Добавление в начало неиспользованных пробелов
            for i in range(const - number):
                print(' ', end = '')

            #Вывод выравненного текста
            for i in range(number):
                print(line[i], end = '')
            print()

            #Алгоритм удаления выведенных строк
            if number == len(line):
                line = ''
            else:
                for i in range(number + 1):
                    line.pop(0)
            
        line = zline


    elif menu == '3':

        #Преобразование строки в список
        if line == '':
            print('На данный момент текст отсутствует, поэтому будет заполнен \
занаво')
            line = list(array_in_list(array))



        zline = line
        
        if not(' ' in line):
            for i in range((const - len(line))// 2):
                print(' ', end = '')
            for i in range(len(line)):
                print(line[i], end = '')
            print()
            

        else:
            while line != '':

                #Алгоритм поиска количества слов, которые смогут поместиться на
                #одной строке
                if len(line) > const:
                    for i in range(const, 0, -1):
                        if line[i] == ' ':
                            number = i
                            break

                else:
                    number = len(line)

                #Поиск количества пробелов между словами помещающейся строки
                kol = 0
                for i in range(number):
                    if line[i] == ' ':
                        kol += 1

                #Колиство гарантированных пробелов между словами
                tub = (const - number) // kol 

                #Колиство оставшихся пробелов между словами
                balance = (const - number) - kol * tub

                #Строка гарантированных пробелов между словами
                str_tub = ' '
                for i in range(tub):
                    str_tub = str_tub + ' '

                #Вывод выравненного текста
                isok = 0
                for i in range(number):
                    if line[i] != ' ':
                        print(line[i], end = '')
                    else:
                        print(str_tub, end = '')

                        #Алгоритм добавления оставшихся пробелов
                        if isok < balance:
                            print(' ', end = '')
                            isok += 1
                print()

                #Алгоритм удаления выведенных строк
                if number == len(line):
                    line = ''
                else:
                    for i in range(number + 1):
                        line.pop(0)
        line = zline


    elif menu == '4':

        #Преобразование строки в список слов
        if line == '':
            line = list(array_in_list(array).split())
        else: line = line.split()

        word = input('Введите слово, которое хотите удалить в тексте: ')
        wordtitle = str.capitalize(word)
        punctuation = ['.', ',', ';', ':', '!', '?']
        
        word_array = []
        for i in range(len(punctuation)):
            word_array.append(word + punctuation[i])
            

        #Алгоритм удаление всех заданных слов
        while word in line:
            line.remove(word)

        while wordtitle in line:
            line.remove(wordtitle)

        for i in range(len(punctuation)):
            while word_array[i] in line:
                line.remove(word_array[i])

        print('В результате данной операции получился текст:')
        if line == []:
            print('Текст отсутствует')
        else:
            for i in range(len(line)):
                print(line[i], end = ' ')
            print()

    elif menu == '5':

        #Преобразование строки в список слов
        if line == '':
            line = array_in_list(array).split()
        else: line = line.split()

        
        word = input('Введите слово, которое хотите заменить в тексте: ')
        wordtitle = str.capitalize(word)
        
        punctuation = ['.', ',', ';', ':', '!', '?']
        
        reword = input('Введите слово, на которое хотите заменить заданное слово: ').split()
        if reword in punctuation:
            rewordtitle = reword
        else:
            rewordtitle = [0] * len(reword)
            for i in range(len(reword)):
                rewordtitle[i] = str.capitalize(reword[i])

        word_array = []
        for i in range(len(punctuation)):
            word_array.append(word + punctuation[i])
        

        #Алгоритм замены всех заданных слов и вывод получившегося текста
        print('В результате данной операции получился текст:')
        for i in range(len(line)):

            if line[i] == word:
                line[i] = reword

            if line[i] == wordtitle:
                line[i] = rewordtitle

            if line[i] in word_array:
                for j in range(len(punctuation)):
                    if line[i] == word_array[j]:
                        line[i] = reword + punctuation[j] 

            if line[i] == reword or line[i] == rewordtitle:
                line0 = ''
                for j in range(len(line[i])):
                    if i != 0:
                        line0 += ' '

                    line0 += line[i][j]

                    if j != len(line[i])-1 or len(reword) == 1:
                        line0 += ' '
                    

                line[i] = line0
                

        
        for i in range(len(line)):
            print(line[i], end = '')
        print()

        line0 = ''
        for i in range(len(line)):
            line0 += str(line[i])
        line = line0

        if line[len(line) - 1] == ' ':

            zline = line

            line = ''
            for i in range(len(zline) - 1):
                line += zline[i]



    elif menu == '6':

        #Преобразование строки в список слов
        if line == '':
            line = list(array_in_list(array).split())
        else: line = list(array_in_list(line).split())

        #Список возможных математических операций
        symbols = ['+', '-', '*' , '/', '//', '**', '%', 'sqrt', '(', ')']

        #Определение размера арифметического выражения
        imax = -1
        imin = len(line) + 1
        for i in range(len(line)):
            if line[i] in symbols:
                imin = min(imin, i)
                imax = max(imax, i)

        #Обработка частных случаем операций
        if line[imin] == 'sqrt' or line[imin] == '(':
            imin += 1

        if line[imax] == ')':
            imin -= 1
        
        #Вычисление значения заданного выражения
        math = ''
        for i in range(imin - 1, imax + 2):
            if line[i] == 'sqrt':
                math += line[i + 1] + ' ' + '**(1/2)' + ' '
            elif line[i - 1] != 'sqrt':
                math += line[i] + ' '

        if imax == -1:
            print('В тексте нет арифметических выражений:')
        else: print('Значение арифметического выражения', math, '= ', eval(math))
                

    elif menu == '7':
        punctuation = ['.', ',', ';', ':', '!', '?']
        
        print('Наиболе часто встречаемые слова: ')
        for i in range(len(array)):
            sen = list(array[i].split())

            El = [] #Список всех слов строки
            freq = [] #Список их частоты встречаемости

            #Алгоритм поиска каждого слова и его частоты в строке
            for i in range(len(sen)):
                sen[i] = str.lower(sen[i])

                if sen[i][len(sen[i]) - 1] in punctuation:
                    zsen = sen[i]
                    sen[i] = ''
                    for j in range(len(zsen) - 1):
                        sen[i] = sen[i] + zsen[j]
                
                if sen[i] not in El:
                    
                    El.append(sen[i])
                    freq.append(1)
            
                else:

                    for k in range(len(El)):
                        if sen[i] == El[k]:
                            freq[k] += 1

            k = freq.index(max(freq))
            print(El[k])


        
