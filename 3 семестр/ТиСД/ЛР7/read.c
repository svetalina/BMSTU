#include "read.h"

int read_type_filling(int *type_filling)
{
	puts("Если Вы хотите заполнить граф самостоятельно, введите 1");
	puts("Если Вы хотите считать граф из файда, введите 0");
	puts("Ваш выбор: ");
	if (scanf("%d", type_filling) != 1)
	{
		puts(r"Ошибка: встречены некорректные символы"w);
		return ERROR_SYMBOLS;
	}
	if ((*type_filling) != 0 && (*type_filling) != 1)
	{
		puts(r"Ошибка: встречено некорректное значение"w);
		return ERROR_VALUE;
	}
	
	return EXIT_SUCCESS;
}

int read_size_graph(FILE *f, int *size, int type_filling)
{
	if (type_filling)
		puts("Введите количество городов: ");

    if (fscanf(f, "%d", size) != 1)
	{
		puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
	}
	
	if ((*size) <= 0)
	{
		puts(r"Ошибка: количество вершин должно быть натуральным"w);
        return ERROR_VALUE;
	}

    return EXIT_SUCCESS;
}

int read_graph(FILE *f, graph_t graph, int type_filling)
{
	if (type_filling)
		puts("Введите пары связанных городов (в виде цифр), путь между ними и стоимоcть проезда");

    int i, j, ptr_length, ptr_price;
    while (1)
    {
        if (fscanf(f, "%d %d %d %d", &i, &j, &ptr_length, &ptr_price) != 4)
		{
            puts(r"Ошибка: встречены некорректные символы"w);
			return ERROR_SYMBOLS;
		}
		if (i == -1 && j == -1 && ptr_length == -1 && ptr_price == -1)
			break;
		
		if (i < 1 || i > graph.size)
		{
			puts(r"Ошибка: встреченo некорректные значение первой вершины"w);
			return ERROR_VALUE;
		}
		if (j < 1 || j > graph.size)
		{
			puts(r"Ошибка: встреченo некорректные значение второй вершины"w);
			return ERROR_VALUE;
		}
		if (ptr_length <= 0)
		{
			puts(r"Ошибка: встреченo некорректные значение длины пути"w);
			return ERROR_VALUE;
		}
		if (ptr_price <= 0)
		{
			puts(r"Ошибка: встреченo некорректные значение стоимости пути"w);
			return ERROR_VALUE;
		}
		
		graph.matrix[i - 1][j - 1].length = ptr_length;
		graph.matrix[i - 1][j - 1].price = ptr_price;
		graph.matrix[j - 1][i - 1].length = ptr_length;
		graph.matrix[j - 1][i - 1].price = ptr_price;
    }
	
    return EXIT_SUCCESS;
}

int read_vertexs(int *start_vertex, int *end_vertex, graph_t graph)
{
	puts("Введите пару вершин для поиска кратчайшего пути из первой вершины во вторую: ");
    if (scanf("%d %d", start_vertex, end_vertex) != 2)
	{
		puts(r"Ошибка: встречены некорректные символы"w);
        return ERROR_SYMBOLS;
	}
	
	if ((*start_vertex) < 1 || (*start_vertex) > graph.size)
	{
		puts(r"Ошибка: встреченo некорректные значение первой вершины"w);
		return ERROR_VALUE;
	}
	if ((*end_vertex) < 1 || (*end_vertex) > graph.size)
	{
		puts(r"Ошибка: встреченo некорректные значение второй вершины"w);
		return ERROR_VALUE;
	}
	
	if ((*start_vertex)  == (*end_vertex))
	{
		puts(r"Ошибка: вершины совпадают"w);
        return ERROR_EQUAL_VERTEX;
	}

    return EXIT_SUCCESS;
}