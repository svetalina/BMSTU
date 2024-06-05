#include "matrix.h"

int read_matrix(std_matrix_t *matrix, int unzero_size)
{
    int num, x, y;

    while (unzero_size-- > 0)
    {
        puts("Введите элемент матрицы: ");
        if (scanf("%d", &num) != 1)
        {
            puts(r"Ошибка: число введено неверно"w);
            return ERROR_ELEMENT;
        }

        puts("Введите строку матрицы (нумерация с 0): ");
        if ((scanf("%d", &x) != 1) || (x > matrix->x_size) || (x < 0))
        {
            puts(r"Ошибка: строка матрицы введена неверно"w);
            return ERROR_X_POS;
        }

        puts("Введите номер столбца матрицы (нумерация с 0): ");
        if ((scanf("%d", &y) != 1) || (y > matrix->y_size) || (y < 0))
        {
            puts(r"Ошибка: столбец матрицы введен неверно"w);
            return ERROR_Y_POS;
        }

        matrix->matrix[x][y] = num;
    }

    return EXIT_SUCCESS;
}

void random_matrix(std_matrix_t *matrix, int unzero_size)
{
    srand(time(NULL));

    int x, y;

    for (int i = 0; i < unzero_size; i++)
    {
        do
        {
            x = rand() % matrix->x_size;
            y = rand() % matrix->y_size;
        } while (matrix->matrix[x][y] != 0);

        matrix->matrix[x][y] = rand() % 100 + 1;
    }
}

int create_std_matrix(std_matrix_t *matrix, list_t *list)
{
    int rc;
    
    int read_type;
    puts("Введите, если хотите заполнить матрицу:\n  1 - самостоятельно\n  0 - случайно\n");
    if ((scanf("%d", &read_type) != 1) || (read_type > 1) || (read_type < 0))
    {
        puts(r"Ошибка: тип заполнения матрицы введён неверно"w);
        return ERROROR_READ_TYPE;
    }
    
    std_matrix_t tmp_matrix = {.matrix = NULL, .x_size = 0, .y_size = 0};
    puts("Введите через пробел количество строк и столбцов матрицы (от 1 до 1000): ");
    if (scanf("%d %d", &tmp_matrix.x_size, &tmp_matrix.y_size) != 2)
    {
        puts(r"Ошибка: неверно введены размеры матрицы"w);
        return ERROR_INPUT_SIZES;
    }
    if ((tmp_matrix.x_size < 1) || (tmp_matrix.x_size > 1000) || (tmp_matrix.y_size < 1) || (tmp_matrix.y_size > 1000))
    {
        puts(r"Ошибка: размеры матрицы не удовлетворяют допустимым значениям (от 1 до 1000)"w);
        return ERROR_VALUE_SIZES;
    }

    if ((rc = allocate_std_matrix(&tmp_matrix)))
    {
        puts(r"Ошибка: память под матрицу выделить не удалось"w);
        return ERROR_MEMORY;
    }
    
    list_t tmp_list = {.arr = NULL, .size = tmp_matrix.x_size};
    if ((rc = allocate_list(&tmp_list)))
    {
        puts(r"Ошибка: память под вектор выделить не удалось"w);
        free_list(*list);
        return ERROR_MEMORY;
    }
    
    int unzero_size_matrix;
    puts("Введите количество ненулевых элементов матрицы: ");
    if ((scanf("%d", &unzero_size_matrix) != 1) || (unzero_size_matrix > (double)tmp_matrix.x_size * tmp_matrix.y_size) || (unzero_size_matrix < 0))
    {
        puts(r"Ошибка: количество ненулевых элементов в матрице введено неверно"w);
        return ERROR_UNZERO_SIZE;
    }

    int unzero_size_list;
    puts("Введите количество ненулевых элементов в векторе столбце: ");
    if ((scanf("%d", &unzero_size_list) != 1) || (unzero_size_list < 0) || (unzero_size_list > tmp_list.size))
    {
        puts(r"Ошибка: количество ненулевых элементов в векторе столбце введено неверно");
        return ERROR_UNZERO_SIZE;
    }

    if (read_type)
    {
        if ((rc = read_matrix(&tmp_matrix, unzero_size_matrix)))
            return rc;
        if ((rc = read_list(&tmp_list, unzero_size_list)))
            return rc;
    }
    else
    {
        random_matrix(&tmp_matrix, unzero_size_matrix);
        random_list(&tmp_list, unzero_size_list);
    }

    tmp_matrix.unzero_size = unzero_size_matrix;
    *matrix = tmp_matrix;
    *list = tmp_list;
    
    system("clear");
    print_std_matrix(tmp_matrix);
    print_std_list(tmp_list);

    return EXIT_SUCCESS;
}

int create_sparse_matrix(std_matrix_t std_matrix, sparse_matrix_t *matrix)
{
    int rc;
    
    sparse_matrix_t tmp = {.unzero_size = std_matrix.unzero_size, .x_size = std_matrix.x_size, .y_size = std_matrix.y_size};
    if ((rc = allocate_sparse_matrix(&tmp)))
    {
        puts(r"Ошибка: память под вектор выделить не удалось"w);
        return ERROR_MEMORY;        
    }

    int elem = 0, flag;
    for (int j = 0; j < std_matrix.y_size; j++)
    {
        flag = 0;
        for (int i = 0; i < std_matrix.x_size; i++)
        {
            if (std_matrix.matrix[i][j] != 0)
            {
                tmp.a[elem] = std_matrix.matrix[i][j];
                tmp.ia[elem] = i;
                
                if (!flag)
                {
                    tmp.ja[j] = elem;
                    flag = 1; 
                }

                elem++; 
            }
        }

        if (!flag)
            tmp.ja[j] = elem;
    }
    
    tmp.ja[std_matrix.y_size] = elem;
    
    *matrix = tmp;
    print_sparse_matrix(*matrix);

    return EXIT_SUCCESS;
}
