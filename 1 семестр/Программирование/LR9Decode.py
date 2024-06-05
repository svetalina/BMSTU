#Программа расшифровывает строку кодом Виженера
#Автор - Светличная Алина, ИУ7 - 13Б

import LR9functions

line = list(input('Введите зашифрованную строку:'))
line = LR9functions.ord_index(line)

key = list(input('Введите ключевое слово для расшифровки:'))
key = LR9functions.ord_index(key)

code = LR9functions.matching(line, key)

cipher = LR9functions.decode(line, code)

print('Раcшифрованная строка: ', end = '')    
for i in range(len(cipher)):
    print(cipher[i], end = '')
