#include "print.h"

void print_info()
{
    puts("");
    puts(m"Программа перемножает вектор-строку и матрицу в разреженном виде"w);
    puts("");
}

void print_std_matrix(std_matrix_t matrix)
{
    puts(g"Матрица: "w);
    for (int i = 0; i < matrix.x_size; i++)
    {
        for (int j = 0; j < matrix.y_size; j++)
        {
            printf("%3d ", matrix.matrix[i][j]);
        }
        puts("");
    }
}

void print_sparse_matrix(sparse_matrix_t matrix)
{
    puts(g"Разреженная матрица: "w);
    puts("Ненулевые элементы: ");
    for (int i = 0; i < matrix.unzero_size; i++)
        printf("%3d ", matrix.a[i]);
    puts("");

    puts("Строки ненулевых элементов: ");
    for (int i = 0; i < matrix.unzero_size; i++)
        printf("%3d ", matrix.ia[i]);
    puts("");

    puts("Индекс в массиве ненулевых элементов первого вхождения элемента в столбец: ");
    for (int i = 0; i < matrix.y_size + 1; i++)
        printf("%3d ", matrix.ja[i]);
    puts("");
}

void print_std_list(list_t list)
{
    puts(g"Вектор-строка: "w);
    for (int i = 0; i < list.size; i++)
        printf("%3d ", list.arr[i]);
    puts("");
}

void print_sparse_list(list_t list)
{
    sparse_matrix_t tmp = {.unzero_size = list.size, .x_size = 1};

    int elem = 0;
    
    if ((allocate_sparse_matrix(&tmp)))
        return;

    for (int i = 0; i < list.size; i++)
    {
        if (list.arr[i] != 0)
        {
            tmp.a[elem] = list.arr[i];
            tmp.ia[elem++] = i;
        }
    }
    
    puts(g"Разреженный вектор-строка: "w);
    
    puts("Ненулевые элементы: ");
    for (int i = 0; i < elem; i++)
        printf("%3d ", tmp.a[i]);
    puts("");

    puts("Столбцы ненулевых элементов: ");
    for (int i = 0; i < elem; i++)
        printf("%3d ", tmp.ia[i]);
    puts("");
    
    free_sparse_matrix(tmp);
}

void print_result(sparse_matrix_t sparse_matrix, std_matrix_t std_matrix, int64_t time1, int64_t time2)
{
    puts(g"Результаты измерений: "w);

    puts("Стандартная матрица матрица: ");
    printf("%lld тактов, %lf секунд\n", time1, (double)time1/GHZ);

    puts("Разреженная матрица: ");
    printf("%lld тактов, %lf секунд\n", time2, (double)time2/GHZ);

    printf("Память под стандартную матрицу: %lld\n", std_matrix.x_size * std_matrix.y_size * sizeof(int));
    printf("Память под разреженную матрицу: %lld\n", (sparse_matrix.unzero_size * 2 + sparse_matrix.x_size) * sizeof(int));

    double percent = (double)(std_matrix.x_size * std_matrix.y_size) / 100;
    double filled = std_matrix.unzero_size / percent;
    printf("Примерная заполненность матрицы %d на %d: %.1lf%% / 100%%", std_matrix.x_size, std_matrix.y_size, filled);
}