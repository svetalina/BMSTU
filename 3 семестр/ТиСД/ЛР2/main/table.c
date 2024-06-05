#include "table.h"

void clear_table(table_t *const table)
{
    for (int i = 0; i < table->size; i++)
    {
        table->keys[i].id = 0;
        table->books[i].author[0] = '\0';
    }
}

short load_data(table_t *const table, FILE *f, short start, short end)
{
    short rc;
    for (int i = start; i < end; i++)
    {
        if ((rc = read_books_author(table, f, i)))
            return rc;

        if ((rc = read_books_name(table, f, i)))
            return rc;
        
        if ((rc = read_books_publish_house(table, f, i)))
            return rc;
        
        if (!(fscanf(f, "%hi ", &table->books[i].size_book)))
        {
            puts("Количсетво страниц записано некорректно");
            return ERROR_SYMBOLS;
        }
        
        if ((rc = read_books_is_type(table, f, i)))
            return rc;
        
        if (strcmp(table->books[i].is_type, "technical") == 0)
            if ((rc = read_technical(table, f, i)))
                return rc;
        if (strcmp(table->books[i].is_type, "fiction") == 0)
            if ((rc = read_fiction(table, f, i)))
                return rc;
        if (strcmp(table->books[i].is_type, "children") == 0)
            if ((rc = read_children(table, f, i)))
                return rc;

        update_keys(table, i, i, table->books[i].size_book);
    }

    return EXIT_SUCCESS;
}

short load_data_one(table_t *const table, FILE *f, short start, short end)
{
    short rc;
    for (int i = start; i < end; i++)
    {
        puts("Введите фамилию автора:");
        if (fscanf(f, "%s", table->books[i].author) != 1)
            return ERROR_INPUT;
        
        puts("Введите наименование книги:");
        if (fscanf(f, "%s", table->books[i].name) != 1)
            return ERROR_INPUT;
        
        puts("Введите издательство:");
        if (fscanf(f, "%s", table->books[i].publish_house) != 1)
            return ERROR_INPUT;
        
        puts("Введите количество старниц:");
        if (fscanf(f, "%hi", &table->books[i].size_book) != 1)
            return ERROR_INPUT;
        
        puts("Введите тип литературы:");
        if (fscanf(f, "%s", table->books[i].is_type) != 1)
            return ERROR_INPUT;

        if (strcmp(table->books[i].is_type, "technical") == 0)
        {
            puts("Введите отрасль:");
            if (fscanf(f, "%s", table->books[i].type.technical.branch) != 1 )
                return ERROR_INPUT;
            
            puts("Отечественная ли книга:");
            if (fscanf(f, "%hi", &table->books[i].type.technical.domestic) != 1)
                return ERROR_INPUT;
            
            if (table->books[i].type.technical.domestic != 1)
                table->books[i].type.technical.translate = 1;
            else
                table->books[i].type.technical.translate = 0;
            
            puts("Введите год издания:");
            if (fscanf(f, "%hi", &table->books[i].type.technical.year) != 1)
                return ERROR_INPUT;
        }
        
        if (strcmp(table->books[i].is_type, "fiction") == 0)
        {
            puts("Роман ли это:");
            if (fscanf(f, "%hi", &table->books[i].type.fiction.novel) != 1) 
                return ERROR_INPUT;
            
            puts("Пьеса ли это:");
            if (fscanf(f, "%hi", &table->books[i].type.fiction.play) != 1)
                return ERROR_INPUT;
            
            if (table->books[i].type.fiction.novel != 1 
            && table->books[i].type.fiction.play != 1)
                table->books[i].type.fiction.poetry = 1;
            else
                table->books[i].type.fiction.poetry = 0;
        }
        
        if (strcmp(table->books[i].is_type, "children") == 0)
        {
            puts("Сказка ли это:");
            if (fscanf(f, "%hi", &table->books[i].type.children.story) != 1)
                return ERROR_INPUT;
           
            if (table->books[i].type.children.story != 1)
                table->books[i].type.children.poetry = 1;
            else
                table->books[i].type.children.poetry = 0;
        }

        update_keys(table, i, i, table->books[i].size_book);
    }

    return EXIT_SUCCESS;
}

void update_keys(table_t *const table, const short i, const short id, const short size_book)
{
    table->keys[i].id = id;
    table->keys[i].size_book = size_book;
}

short upload_from_file(table_t *const table)
{
    FILE *f = NULL;
    short rc;

    clear_table(table);

    if ((f = fopen(FILE_NAME, "r")) == NULL)
	{
		puts("Невозможно открыть файл");
        return ERROR_OPEN_FILE;
	}

    if (read_file_size(table, f))
        return ERROR_FILE_SIZE;

    if ((rc = load_data(table, f, 0, table->size)))
        return rc;

    fclose(f);

    return EXIT_SUCCESS;
}

short add_to_end(table_t *const table)
{
    short rc; 
    
    if (table->size + 1 == MAX_SIZE)
    {
        puts("Невозможно добавить книгу, таблица переполнена");
        return TABLE_IS_FULL;
    }

    if ((rc = load_data_one(table, stdin, table->size, table->size + 1)))
        return rc;
    
    (table->size)++;
    puts("Книга добавлена в таблицу");

    return EXIT_SUCCESS;
}

short check_size(short size)
{
    if (!size) 
    {
        puts("Таблица пуста");
        return TABLE_IS_EMPTY;
    }

    return EXIT_SUCCESS;
}

void del_by_pos(table_t *const table, int del_ind_keys, int del_ind_table)
{
    for (int i = del_ind_table; i < table->size - 1; i++)
    {
        table->books[i] = table->books[i + 1];
        table->keys[i].id--;
    }

    for (int i = del_ind_keys; i < table->size - 1; i++)
    {
        table->keys[i] = table->keys[i + 1];
    }

    --table->size;
}

short del_by_pos_main(table_t *const table)
{
    int pos; 

    if (check_size(table->size))
        return TABLE_IS_EMPTY;

    if (read_pos_to_del(table, &pos))
        return ERROR_INPUT;
    
    del_by_pos(table, pos, table->keys[pos].id);

    puts("Заданные книги были удаленны.");

    return EXIT_SUCCESS;
}

short qs_vs_bubble(table_t *const table)
{
    int64_t start, end, end1, end2, end3, start1, start2, start3;

    printf("Сортировка таблицы на %d ключей\n", table->size);
    
    start = tick();
    qsort(table->books, table->size, sizeof(table->books[0]), comparator_table);
    end = tick();
    print_sorts_vs_results(end - start, 1, 1);
    
    start1 = tick();
    qsort(table->keys, table->size, sizeof(table->keys[0]), comparator_keys);
    end1 = tick();
    print_sorts_vs_results(end1 - start1, 1, 0);
    
    upload_from_file(table);

    start2 = tick();
    bubble_sort(table->size, table->books, comparator_table, 1, sizeof(table->books[0]));
    end2 = tick();
    print_sorts_vs_results(end2 - start2, 0, 1);

    start3 = tick();
    bubble_sort(table->size, table->keys, comparator_keys, 0, sizeof(table->keys[0]));
    end3 = tick();
    print_sorts_vs_results(end3 - start3, 0, 0);

    printf("\n%lu размер массива ключей (в байтах)", sizeof(*(table->keys)) * table->size);
    printf("\n%lu размер таблицы (в байтах)\n", sizeof(*(table->books)) * table->size);

    return EXIT_SUCCESS;
}

short find_books(table_t *const table, char *const branch_str, const int year_str)
{
    short k = 0;

    for (int i = 0; i < table->size; i++)
    {
        if (!strcmp(table->books[i].is_type, "technical") 
            && table->books[i].type.technical.domestic 
            && !strcmp(table->books[i].type.technical.branch, branch_str) 
            && table->books[i].type.technical.year == year_str)
        {
            print_by_condition(*table, i);
            ++k;
        }
    }

    return k ? EXIT_SUCCESS : NO_MATCHES;
}

short find_book_by_condition(table_t *const table)
{
    char branch_str[MAX_SIZE];
    int year_str;

    if (read_branch(branch_str))
        return ERROR_INPUT;
    
    if (reade_year(&year_str))
        return ERROR_INPUT;
    
    if (find_books(table, branch_str, year_str))
        puts("Книг с такими параметрами не найдено");

    return EXIT_SUCCESS;
}

short int do_action(short int action_type, table_t *table)
{
    short int rc;
    system("clear");

    switch (action_type)
    {
        case 0:
            print_rules();
            break;
            
        case 1:
            if ((rc = upload_from_file(table))) 
            {
                return rc;
            }
            puts("Книги загруженны в таблицу");
            break;

        case 2:
            rc = add_to_end(table);
            break;

        case 3:
            rc = del_by_pos_main(table);
            break;

        case 4:
            if (check_size(table->size)) 
                return TABLE_IS_EMPTY;
            qsort(table->keys, table->size, sizeof(table->keys[0]), comparator_keys);
            print_table_keys(*table);
            break;

        case 5:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            qsort(table->books, table->size, sizeof(table->books[0]), comparator_table);
            print_table(*table, 0);
            break;

        case 6:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            qsort(table->keys, table->size, sizeof(table->keys[0]), comparator_keys);
            print_table(*table, 1);
            break;

        case 7:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            rc = qs_vs_bubble(table);
            break;

        case 8:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            rc = find_book_by_condition(table);
            break;

        case 9:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            print_table(*table, 0);
            break;

        default:
            exit(10);
    }

    if (rc)
        return rc;

    return EXIT_SUCCESS;
}
