#include "read.h"

short int read_action(short *action_type)
{
    puts("Выберите пункт меню: ");

    if (scanf("%hi", action_type) != 1)
    {
        puts("В записи пункта меню встречены некорректные символы");
        return ERROR_SYMBOLS;
    }
    
    if (*action_type > MAX_MENU || *action_type < MIN_MENU)
    {
        puts("Некорректный пункт меню");
        return ERROR_MENU_NUMBER;
    }

    return EXIT_SUCCESS;
}

short read_file_size(table_t *table, FILE *f)
{
    if (fscanf(f, "%hi\n", &table->size) != 1)
	{
		puts("В записи количества записей встречены некорректные символы");
        return ERROR_FILE_SIZE;
	}

    if (table->size < 1 || table->size > MAX_SIZE)
	{
		puts("Некорректное количество записей");
        return ERROR_FILE_SIZE;
	}

    return EXIT_SUCCESS;
}

short read_books_author(table_t *table, FILE *f, short int i)
{ 
    short j = 0;
   
    while (fscanf(f, "%c", &table->books[i].author[j]) && table->books[i].author[j] != ' ')
    {      
        if (!((table->books[i].author[j] >= 'A' && table->books[i].author[j] <= 'Z') 
            || (table->books[i].author[j] >= 'a' && table->books[i].author[j] <= 'z')))
        {
            puts("В фамилии автора встречены некорректные символы");
            return ERROR_SYMBOLS;
        }
        
        j++;
    }
    
    table->books[i].author[j] = '\0';

    return EXIT_SUCCESS;
}

short int read_books_name(table_t *table, FILE *f, short int i)
{ 
    short j = 0;
   
    while (fscanf(f, "%c", &table->books[i].name[j]) && table->books[i].name[j] != ' ')
    {
        if (!((table->books[i].name[j] >= 'A' && table->books[i].name[j] <= 'Z') 
            || (table->books[i].name[j] >= 'a' && table->books[i].name[j] <= 'z') 
            || table->books[i].name[j] == '_'))
        {
            puts("В названии книги встречены некорректные символы");
            return ERROR_SYMBOLS;
        }
        
        j++;
    }
    
    table->books[i].name[j] = '\0';

    return EXIT_SUCCESS;
}

short int read_books_publish_house(table_t *table, FILE *f, short int i)
{ 
    short j = 0;
   
    while (fscanf(f, "%c", &table->books[i].publish_house[j]) && table->books[i].publish_house[j] != ' ')
    {
        if (!((table->books[i].publish_house[j] >= 'A' && table->books[i].publish_house[j] <= 'Z') 
            || (table->books[i].publish_house[j] >= 'a' && table->books[i].publish_house[j] <= 'z') 
            || table->books[i].publish_house[j] == '_'))
        {
            puts("В названии издательства встречены некорректные символы");
            return ERROR_SYMBOLS;
        }
        
        j++;
    }
    
    table->books[i].publish_house[j] = '\0';

    return EXIT_SUCCESS;
}

short int read_books_is_type(table_t *table, FILE *f, short int i)
{ 
    short j = 0;
   
    while (fscanf(f, "%c", &table->books[i].is_type[j]) && table->books[i].is_type[j] != ' ')
    {
        if (!((table->books[i].is_type[j] >= 'A' && table->books[i].is_type[j] <= 'Z') 
            || (table->books[i].is_type[j] >= 'a' && table->books[i].is_type[j] <= 'z')))
        {
            puts("В названии типа книги встречены некорректные символы");
            return ERROR_SYMBOLS;
        }
        
        j++;
    }
    
    table->books[i].is_type[j] = '\0';

    return EXIT_SUCCESS;
}

short int read_technical(table_t *table, FILE *f, short int i)
{
    short j = 0;
   
    while (fscanf(f, "%c", &table->books[i].type.technical.branch[j]) && table->books[i].type.technical.branch[j] != ' ')
    {
        if (!((table->books[i].type.technical.branch[j] >= 'A' && table->books[i].type.technical.branch[j] <= 'Z') 
            || (table->books[i].type.technical.branch[j] >= 'a' && table->books[i].type.technical.branch[j] <= 'z')))
        {
            puts("В названии отрасли технических книг встречены некорректные символы");
            return ERROR_SYMBOLS;
        }
        
        j++;
    }
    
    table->books[i].type.technical.branch[j] = '\0';
    
    if (!(fscanf(f, "%hi", &table->books[i].type.technical.domestic)))
    {
        puts("Обозначение отечественности книги некорректно");
        return ERROR_SYMBOLS;
    }
    
    if (!(fscanf(f, "%hi", &table->books[i].type.technical.translate)))
    {
        puts("Обозначение перевода книги некорректно");
        return ERROR_SYMBOLS;
    }
    
    if (!(fscanf(f, "%hi\n", &table->books[i].type.technical.year)))
    {
        puts("Год написания книги некорректен");
        return ERROR_SYMBOLS;
    }
    
    return EXIT_SUCCESS;
}

short int read_fiction(table_t *table, FILE *f, short int i)
{ 
    if (!(fscanf(f, "%hi", &table->books[i].type.fiction.novel)))
    {
        puts("Обозначение жанра 'роман' некорректно");
        return ERROR_SYMBOLS;
    }
    
    if (!(fscanf(f, "%hi", &table->books[i].type.fiction.play)))
    {
        puts("Обозначение жанра 'пьеса' некорректно");
        return ERROR_SYMBOLS;
    }
    
    if (!(fscanf(f, "%hi\n", &table->books[i].type.fiction.poetry)))
    {
        puts("Обозначение жанра 'поэзия' некорректно");
        return ERROR_SYMBOLS;
    }
    
    return EXIT_SUCCESS;
}

short int read_children(table_t *table, FILE *f, short int i)
{ 
    if (!(fscanf(f, "%hi", &table->books[i].type.children.story)))
    {
        puts("Обозначение жанра 'сказки' некорректно");
        return ERROR_SYMBOLS;
    }
    
    if (!(fscanf(f, "%hi\n", &table->books[i].type.children.poetry)))
    {
        puts("Обозначение жанра 'стихи' некорректно");
        return ERROR_SYMBOLS;
    }
    
    return EXIT_SUCCESS;
}

short read_pos_to_del(table_t *const table, int *pos)
{
    puts("Введите номер книги, которую вы хотите удалить из таблицы: ");
    
    if (scanf("%d", pos) != 1)
    {
        puts("Введены некорректные символы");
        return ERROR_SYMBOLS;
    }

    if (*pos < 0 || *pos > table->size)
    {
        puts("Некорректный номер книги");
        return ERROR_SIZE_BOOK;
    }
    
    *pos = *pos - 1;

    return EXIT_SUCCESS;
}

short read_branch(char *branch_str)
{
    puts("Введите отрасль для поиска: ");
    if (scanf("%s", branch_str) != 1)
    {
        puts("Ошибка чтения");
        return ERROR_INPUT;
    }
    
    short int len = strlen(branch_str);
    for (int i = 0; i < len; i++)
    {
        if (!((branch_str[i] >= 'A' && branch_str[i] <= 'Z') 
            || (branch_str[i] >= 'a' && branch_str[i] <= 'z')))
        {
            puts("В названии введенной отрасли встречены некорректные символы");
            return ERROR_SYMBOLS;
        }
    }

    return EXIT_SUCCESS;
}

short reade_year(int *year_str)
{
    puts("Введите год для поиска: ");
    if (scanf("%d", year_str) != 1)
    {
        puts("Введенный год некорректен");
        return ERROR_INPUT;
    }

    return EXIT_SUCCESS;
}
