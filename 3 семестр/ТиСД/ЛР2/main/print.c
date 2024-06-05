#include "print.h"

void print_rules()
{
    puts("\nПравила обработки списка литературы, хранящегося в таблице:");
    puts("1) На первой строке файла записывается количество записей");
    puts("2) Далее с каждой новой строки записывается одна запись");
    puts("3) Все записи имеют одинаковую первичную сигнатуру");
    puts("  3.1) Фамилия автора");
    puts("      3.1.1) Программой непредусмотрено никаких символов кроме букв в данном поле");
    puts("      3.1.2) Регистр имеет значение");
    puts("  3.2) Наименование книги");
    puts("      3.2.1) Программой непредусмотрено никаких символов кроме букв и подчеркиваний в данном поле");
    puts("      3.2.2) Регистр имеет значение");
    puts("  3.3) Издательство");
    puts("      3.3.1) Программой непредусмотрено никаких символов кроме букв и подчеркиваний в данном поле");
    puts("      3.3.2) Регистр имеет значение");
    puts("  3.4) Количество страниц");
    puts("      3.4.1) Целое число");
    puts("  3.5) Тип литературы");
    puts("      3.5.1) Один из трех (technical, fiction, children)");
    puts("      3.5.2) Регистр имеет значение");
    puts("4) В зависимости от типа литературы содержится дополнительная информация.");
    puts("  4.1) Technical");
    puts("      4.1.1) Наименование отсрасли (аналогично фамилии автора)");
    puts("      4.1.2) Отечественность книги (если книга отчественная в данной позиции стоит 1, если нет - 0)");
    puts("      4.1.3) Зарубежность книги (если книга зарубежная в данной позиции стоит 1, если нет - 0)");
    puts("          4.1.3.1) Программа не обрабатывает случаи нескольких нулей в выборных полях");
    puts("      4.1.4) Год издания книги (аналогично количеству страниц)");
    puts("  4.2) Fiction");
    puts("      4.2.1) Роман (выборное поле)");
    puts("      4.2.2) Пьеса (выборное поле)");
    puts("      4.2.3) Поэзия (выборное поле)");
    puts("  4.3) Children");
    puts("      4.3.1) Сказка (выборное поле)");
    puts("      4.3.2) Стих (выборное поле)");
    puts("5. Правила для записи полей не полностью распространяются на пункт меню 2, следуйте подсказкам на экране");
    puts("");
}


void print_menu()
{
    puts("\nПрограмма для обработки списка литературы, хранящегося в таблице.");
    puts("Выберите пункт меню: ");
    puts("0. Вывод правил хранения и записи структур.");
    puts("1. Загрузить список книг из файла.");
    puts("2. Добавить книгу в конец таблицы.");
    puts("3. Удалить книгу из таблицы по номеру.");
    puts("4. Посмотреть отсортированный (по количеству страниц) массив ключей.");
    puts("5. Вывести упорядоченную (по количеству страниц) таблицу.");
    puts("6. Вывести упорядоченную таблицу (по количеству страниц), используя упорядоченный массив ключей.");
    puts("7. Вывести результаты сравнения эффективности программы при обработке таблицы и массив ключей.");
    puts("8. Вывести список отечественной технической литературы по указанной отрасли указанного года.");
    puts("9. Вывести таблицу");
    puts("10. Выйти из программы");
}

void print_table_keys(const table_t table)
{
    for (int i = 0; i < table.size; i++)
    {
        printf("Ключ: %d \t | Количество страниц: %d\t |\n", table.keys[i].id, table.keys[i].size_book);
    }
}

void print_table(const table_t table, short int keys)
{
    for (int k = 0; k < table.size; k++)
    {
        puts("");
        
        int i = (keys) ? table.keys[k].id : k;

        printf("%d.Фамилия автора: %s\nНазвание: %s\nИздательство: %s\nКоличество страниц: %hi\nТип литературы: %s\n", k + 1,
            table.books[i].author, table.books[i].name, table.books[i].publish_house,
            table.books[i].size_book, table.books[i].is_type);

        if (!strcmp(table.books[i].is_type, "technical"))
        {
            printf("Отрасль: %s\nCтрана: %s\nГод: %d\n", 
            table.books[i].type.technical.branch, (table.books[i].type.technical.domestic) ? "Отечественная" : "Зарубежная",
            table.books[i].type.technical.year);
        }
        
        if (!strcmp(table.books[i].is_type, "fiction"))
        {
            
            printf("Жанр: %s%s%s\n", (table.books[i].type.fiction.novel) ? "Роман" : "",
            (table.books[i].type.fiction.play) ? "Пьеса" : "", (table.books[i].type.fiction.poetry) ? "Пьеса" : "");
        }
        
        if (!strcmp(table.books[i].is_type, "children"))
        {
            
            printf("Жанр: %s\n", (table.books[i].type.children.story) ? "Сказка" : "Стихи");
        }
    }
}

void print_sorts_vs_results(int64_t total_ticks, short sort_type, short table_type)
{
    printf("Сортировка %s с помощью %s.\n", table_type ? "таблицы" : "массива ключей", sort_type ? "QuickSort" : "пузырька");
    printf("%li тактов, %.10lf секунд\n", total_ticks, (double)total_ticks / GHZ);
}

void print_by_condition(const table_t table, int i)
{
    puts("");
    
    printf("Фамилия автора: %s\nНазвание: %s\nИздательство: %s\nКоличество страниц: %hi\nТип литературы: %s\n",
        table.books[i].author, table.books[i].name, table.books[i].publish_house,
        table.books[i].size_book, table.books[i].is_type);

    printf("Отрасль: %s\nCтрана: %s\nГод: %d\n", 
        table.books[i].type.technical.branch, table.books[i].type.technical.domestic ? "Отечественная" : "Зарубежная",
        table.books[i].type.technical.year);
}
