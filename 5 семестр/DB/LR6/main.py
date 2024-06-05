from books_db import BooksDB
from color import red, blue, base_color

MSG = "МЕНЮ: \n"\
      "1. Выполнить скалярный запрос \n"\
      "2. Выполнить запрос с несколькими соединениями (JOIN) \n"\
      "3. Выполнить запрос с ОТВ(CTE) и оконными функциями \n"\
      "4. Выполнить запрос к метаданным \n"\
      "5. Вызвать скалярную функцию \n"\
      "6. Вызвать многооператорную табличную функцию \n"\
      "7. Вызвать хранимую процедуру \n"\
      "8. Вызвать системную функцию \n"\
      "9. Создать таблицу в базе данных, соответствующую тематике БД \n"\
      "10. Выполнить вставку данных в созданную таблицу с использованием инструкции INSERT \n"\
      "0. Выход \n\n"\
      "Выбор: "\



def input_command():
    try:
        command = int(input(MSG))
        print()
    except:
        command = -1

    if command < 0 or command > 10:
        print("%s\nОжидался ввод целого чилово числа от 0 до 10 %s"
              % (red, base_color))

    return command


def print_table(table):
    if table is not None:
        for row in table:
            print("%s%s%s" % (blue, row, base_color))
    print()


def main():
    books_db = BooksDB()
    command = -1

    while command != 0:
        command = input_command()

        if command == 1:
            table = books_db.scalar_query()

        elif command == 2:
            table = books_db.join_query()

        elif command == 3:
            table = books_db.cte_row_number_query()

        elif command == 4:
            table = books_db.metadata_query()

        elif command == 5:
            table = books_db.scalar_function_call()

        elif command == 6:
            table = books_db.tabular_function_call()

        elif command == 7:
            table = books_db.stored_procedure_call()

        elif command == 8:
            table = books_db.system_functionc_call()

        elif command == 9:
            table = books_db.create_new_table()

        elif command == 10:
            table = books_db.insert_into_new_table()
        else:
            continue

        print_table(table)


if __name__ == "__main__":
    main()