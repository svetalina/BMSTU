#Функция присваивания всем элементам входного массива числового индекса
#по таблице ASCII
def ord_index(line):

    for i in range(len(line)):
        line[i] = ord(line[i])

    return(line)

#Функция сопоставления элементов строки для шифрования и ключевого слова
def matching(line, key):

    code = []
    j = 0
    for i in range(len(line)):

        if j >= len(key):
            j = 0

        code.append(key[j])

        j += 1

    return(code)

#Функция шифрования строки
def encode(line, code):
    cipher = []
    for i in range(len(line)):
        cipher.append(chr((line[i] + code[i]) % 128))#Формула Виженера

    return(cipher)

#Функция шифрования строки
def decode(line, code):
    cipher = []
    for i in range(len(line)):
        cipher.append(chr((line[i] + 128 - code[i]) % 128))#Формула Виженера

    return(cipher)
