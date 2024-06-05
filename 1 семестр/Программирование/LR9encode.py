#Программа зашифровывает строку кодом Виженера
#Автор - Светличная Алина, ИУ7 - 13Б

import LR9functions  

line = list(input('Введите строку для шифрования:'))
line = LR9functions.ord_index(line)
    
key = list(input('Введите ключевое слово для шифрования:'))
key = LR9functions.ord_index(key)

code = LR9functions.matching(line, key)

cipher = LR9functions.encode(line, code)

print('Зашифрованная строка: ', end = '')    
for i in range(len(cipher)):
    print(cipher[i], end = '')







        
