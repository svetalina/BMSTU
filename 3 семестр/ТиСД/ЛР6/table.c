#include "table.h"
#include "print.h"
#include "timer.h"

int hash_func_1(int value, int size)
{
    return abs(value) % size;
}

int hash_func_2(int value, int size)
{
    return size % abs(value);
}

static int is_simple(int num)
{
    for (int i = 2; i < num; i++)
        if (num % i == 0)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

static int find_min_simple(int num)
{
    while (!is_simple(num++))
		;

    return num;
}

int fill_table(FILE *f, struct hash_t *hash_table, int size, hash_func_t hash_func)
{
	fseek(f, 0, SEEK_SET);
	
    hash_table->size = find_min_simple(size);

    node_hash_t *tmp_1 = NULL;

    if (!(tmp_1 = calloc(sizeof(node_hash_t), hash_table->size)))
        return ERROR_MEMORY;

    hash_table->array = tmp_1;

    int num;

    while (fscanf(f, "%d", &num) == 1)
    {
        int ind = hash_func(num, hash_table->size);

        while (hash_table->array[ind].status == BUSY && num != hash_table->array[ind].key)
            ind = (ind + 1) % hash_table->size;

        hash_table->array[ind].key = num;
        hash_table->array[ind].status = BUSY;
    }
	
	if (!feof(f))
	{
		puts(r"Ошибка: в файле встречены некорректные символы"w);
        return ERROR_SYMBOLS;
	}	

    return EXIT_SUCCESS;
}

static int static_delete_from_table(struct hash_t *hash_table, int key, hash_func_t hash_func)
{
    size_t start = tick();

    int count_comparisons = 1, ind = hash_func(key, hash_table->size);

    while (hash_table->array[ind].key != key)
    {
        if (hash_table->array[ind].status != BUSY && (hash_table->array[ind].status != DELETED || count_comparisons >= hash_table->size))
            return -1;

        ind = (ind + 1) % hash_table->size;
        count_comparisons++;
    }

    hash_table->array[ind].status = DELETED;
    size_t end = tick();
    printf(c"Время удаления из хеш-таблицы: %f мс\n"w, (double)(end - start) / CLOCKS_PER_SEC);

    return count_comparisons;
}

static int func = 0;

int delete_from_table(FILE *f, struct hash_t *hash_table, int key)
{
    int num_comparisons;
	int count_comparsions;
    
    puts("Введите максимальное количество сравнений: ");
    if (scanf("%d", &num_comparisons) != 1)
    {
        puts(r"Ошибка: встречены некорректные символы"w);
		return ERROR_SYMBOLS;
    }

    if (!func)
        count_comparsions = static_delete_from_table(hash_table, key, hash_func_1);
    else
        count_comparsions = static_delete_from_table(hash_table, key, hash_func_2);

    if (count_comparsions > 0)
        printf(c"Количество сравнений: %d\n"w, count_comparsions);

    if (count_comparsions > num_comparisons && count_comparsions != -1)
    {
        puts(y"Количество сравнений превысело максимальное количество сравнений, необходима реструктуризация:\n"w);
        free(hash_table->array);
        fill_table(f, hash_table, hash_table->size, hash_func_2);
        print_table(hash_table, hash_func_2);
        static_delete_from_table(hash_table, key, hash_func_2);
        print_table(hash_table, hash_func_2);
        return EXIT_SUCCESS;
    }

    if (count_comparsions > 0 || !func)
        print_table(hash_table, hash_func_1);
    else if (count_comparsions > 0)
	{
        print_table(hash_table, hash_func_2);
	}
	
	return EXIT_SUCCESS;
}