#include "tree.h"
#include "table.h"
#include "print.h"
#include "timer.h"

#define ERROR_FILE 1
#define ERROR_PARAMETERS 2
#define ERROR_MENU 3
#define ERROR_VALUE 4

int rotate;
int deleted;

int menu(int *menu_type)
{
	print_menu();

    if (scanf("%d", menu_type) != 1 || *menu_type < 0 || *menu_type > 4)
	{
		puts(r"Ошибка: введен некорректный номер пункта меню"w);
        return ERROR_MENU;
	}
	
	return EXIT_SUCCESS;
}

void delete_from_file(FILE *f, char *filename, int size, int el)
{
    fseek(f, 0, SEEK_SET);

    int *arr = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
	{
        fscanf(f, "%d", &arr[i]);
	}
	
	fclose(f);
	f = fopen(filename, "w");
    
    for (int i = 0; i < size; i++)
	{
        if (arr[i] != el)
            fprintf(f, "%d ", arr[i]);
	}
	
	fclose(f);

    fprintf(f, "\n");
}

void delete_all(FILE *f, char *filename, struct tree_node_t *root, struct tree_node_t *balance_root, int el, int *size)
{
    clock_t st_tree, st_btree, end_tree, end_btree, st_file, end_file;
    deleted = 0;
	
    st_tree = tick();
    root = remove_el(root, el, 0);
    end_tree = tick();
    st_btree = tick();
    balance_root = remove_el(balance_root, el, 1);
    end_btree = tick();
    st_file = tick();
    delete_from_file(f, filename, *size, el);
    end_file = tick();

    if (deleted)
    {
        (*size)--;
        printf(c"Время удаления в файле: %f мс\n"w, (double)(end_file - st_file) / CLOCKS_PER_SEC);
        print_tree(root, *size, 0);
        printf(c"Время удаления в несбалансированном дереве: %f мс\n"w, (double)(end_tree - st_tree) / CLOCKS_PER_SEC);
        print_tree(balance_root, *size, 1);
        printf(c"Время удаления в сбалансированном дереве: %f мс\n"w, (double)(end_btree - st_btree) / CLOCKS_PER_SEC);
    }
    else
        puts(y"Предупреждение: заданный элемент не найден"w);
}

int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	
	int rc;
	
	FILE *f;
    int menu_type = 0, size = 0;
    struct tree_node_t *root = NULL, *balance_root = NULL;
	struct hash_t hash_table;

    if (argc == 1)
	{
       puts(r"Ошибка: имя файла не указано"w);
	   return ERROR_FILE;
	}
    else if (argc == 2)
    {
		if (!(f = fopen(argv[1], "r")))
		{
			puts(r"Ошибка: невозможно открыть файл"w);
			return ERROR_FILE;
		}
    }
    else
        return ERROR_PARAMETERS;

    while (1)
    {
        if ((rc = menu(&menu_type)))
			return rc;
		
        switch (menu_type)
        {
        case 1:
            if ((rc = fill_tree(f, &root, &size)) || (rc = fill_table(f, &hash_table, size, hash_func_1)))
                return rc;
            else
            {
                print_tree(root, size, 0);
                print_table(&hash_table, hash_func_1);
            }

            break;

        case 2:
            if (!root)
            {
                puts(y"Предупреждение: дерево пустое, считаете числа из файла"w);
                break;
            }

            balance_root = copy_node(root);
            do
            {
                rotate = 0;
                balance_root = btree_balance_post(balance_root, balance);
            }
            while (rotate);

            print_tree(balance_root, size, 1);
            break;

        case 3:
            if (!balance_root)
            {
                puts(y"Предупреждение: дерево не сбалансировано, вызовите пукт меню 2"w);
                break;
            }

            puts("Введите значение удаляемого элемента: ");
            int num;
            if (scanf("%d", &num) != 1)
			{
                puts(r"Ошибка: встречены некорректные символы"w);
				return ERROR_SYMBOLS;
			}

			if((rc = delete_from_table(f, &hash_table, num)))
				return rc;
			delete_all(f, argv[1], root, balance_root, num, &size);

            break;

        case 4:
			printf(c"Память, занимаемая файлом: ");
			system("stat --printf=%s *.txt");
			printf(c" байт\n"w);
			
			if (!size)
			{
				puts(y"Предупреждение: дерево и таблица пустые, сначала считайте их из файла"w);
				break;
			}
			
            printf(c"Память, занимаемая деревом: %lld байт\n"w, sizeof(struct tree_node_t) * (size));
            printf(c"Память, занимаемая хеш-таблицей: %lld байт\n"w, sizeof(struct hash_t) + sizeof(node_hash_t) * (size));  

            break;

        case 0:
            goto end;
        }
    }

    end:
    btree_free_post(root, node_free, NULL);
    btree_free_post(balance_root, node_free, NULL);

    return EXIT_SUCCESS;
}