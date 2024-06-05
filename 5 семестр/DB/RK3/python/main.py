from sql import RK03
from lymbda import ql1, ql2, ql3

MSG = """
\t\tМЕНЮ
1  - старший сотрудник в бухгалтерии
2  - выходившие больше 3-х раз с рабочего меcта
3  - пришедший сегодня последним
4  - лямбда-1
5  - лямбда-2
6  - лямбда-3
0  - выход

Выбор: """

def input_command():
    try:
        command = int(input(MSG))
        print()
    except:
        command = -1
    return command

def print_table(table):
    if table is not None:
        for row in table:
            print("%s" % (row), end=" ")
    print()

def menu():
    myDB = RK03()
    command = -1

    while command != 0:
        command = input_command()

        if command == 1:
            table = myDB.q1()

        elif command == 2:
            table = myDB.q2()

        elif command == 3:
            table = myDB.q3()

        elif command == 4:
            table = ql1()

        elif command == 5:
            table = ql2()

        elif command == 6:
            table = ql3()
        else:
            continue

        print_table(table)

if __name__ == '__main__':
    menu()
