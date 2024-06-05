#include "timer.h"

#define X_SIZE 500
#define Y_SIZE 500
#define UNZERO 225000
#define UNZERO_L 1

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


void mul_std(std_matrix_t matrix, list_t list, list_t *result)
{
    list_t tmp = *result;

    int ind = 0, num;
    for (int j = 0; j < matrix.y_size; j++)
    {
        num = 0;

        for (int i = 0; i < matrix.x_size; i++)
            num += matrix.matrix[i][j] * list.arr[i];

        tmp.arr[ind++] = num;
    }

    *result = tmp;
}

void mul_sparse(sparse_matrix_t matrix, list_t list, list_t *result)
{
    list_t tmp = *result;

    for (int i = 1; i <= matrix.y_size + 1; i++)  
        for (int j = matrix.ja[i - 1]; j < matrix.ja[i]; j++)
            tmp.arr[i - 1] += matrix.a[j] * list.arr[matrix.ia[j]];

    *result = tmp;
}

void free_std_matrix(std_matrix_t matrix)
{
    for (int i = 0; i < matrix.x_size; i++)
        free(matrix.matrix[i]);
    free(matrix.matrix);
}

void free_list(list_t list)
{
    free(list.arr);
}

void free_sparse_matrix(sparse_matrix_t matrix)
{
    free(matrix.a);
    free(matrix.ia);
    free(matrix.ja);
}

void free_all(std_matrix_t std_matrix, sparse_matrix_t sparse_matrix, list_t list)
{
    free_list(list);
    free_std_matrix(std_matrix);
    free_sparse_matrix(sparse_matrix);
}


int allocate_std_matrix(std_matrix_t *matrix)
{
    int **tmp = calloc(matrix->x_size, sizeof(int*));
    if (!tmp)
        return ERROR_MEMORY;

    for (int i = 0; i < matrix->x_size; i++)
    {
        tmp[i] = calloc(matrix->y_size, sizeof(int));

        if (!tmp[i])
        {
            free_std_matrix(*matrix);
            return ERROR_MEMORY;
        }
    }
    
    matrix->matrix = tmp;

    return EXIT_SUCCESS;
}

int allocate_list(list_t *list)
{
    list_t tmp;
    
    tmp.arr = calloc(list->size, sizeof(int));
    if (!tmp.arr)
        return ERROR_MEMORY;

    list->arr = tmp.arr;

    return EXIT_SUCCESS;
}

int allocate_sparse_matrix(sparse_matrix_t *matrix)
{
    sparse_matrix_t tmp;

    tmp.a = calloc(matrix->unzero_size, sizeof(int));

    tmp.ia = calloc(matrix->unzero_size, sizeof(int));

    tmp.ja = calloc(matrix->y_size + 1, sizeof(int));

    if (!(tmp.a) || !(tmp.ja) || !(tmp.ia))
        return ERROR_MEMORY;

    matrix->a = tmp.a;
    matrix->ia = tmp.ia;
    matrix->ja = tmp.ja;

    return EXIT_SUCCESS;
}

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
    
    int read_type = 0;
    
    std_matrix_t tmp_matrix = {.matrix = NULL, .x_size = X_SIZE, .y_size = Y_SIZE};
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
    int unzero_size_matrix = UNZERO;
    int unzero_size_list = UNZERO_L;

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

    return EXIT_SUCCESS;
}

int read_list(list_t *list, int unzero_size)
{
    int num, pos;

    while (unzero_size-- > 0)
    {
        puts("Введите элемент вектора-строки: ");
        if (scanf("%d", &num) != 1)
        {
            puts(r"Ошибка: элемент вектора введён неверно"w);
            return ERROR_ELEMENT;
        }

        puts("Введите позицию элемента в векторе-строке (нумерация с 0):");
        if ((scanf("%d", &pos) != 1) || (pos < 0) || (pos > list->size))
        {
            puts(r"Ошибка: позиция элемента вектора введена неверно"w);
            return ERROR_Y_POS;
        }

        list->arr[pos] = num;
    }

    return EXIT_SUCCESS;
}

void random_list(list_t *list, int unzero_size)
{
    srand(time(NULL));

    int pos;

    while (unzero_size-- > 0)
    {
        do
        {
            pos = rand() % list->size;
        } while (list->arr[pos] != 0);
        
        list->arr[pos] = rand() % 100 + 1;
    }
}

int main(void)
{
    int64_t start, end, time1 = 0, time2 = 0;
    int rc;
    
    for (int i = 0; i < 100; i++)
    {
        std_matrix_t std_matrix = {.matrix = NULL, .x_size = 0, .y_size = 0, .unzero_size = 0};
        list_t list = {.arr = NULL, .size = 0};
        if ((rc = create_std_matrix(&std_matrix, &list)))
        {
            free_std_matrix(std_matrix);
            free_list(list);
            return rc;
        }

        sparse_matrix_t sparse_matrix;
        if ((rc = create_sparse_matrix(std_matrix, &sparse_matrix)))
        {
            free_all(std_matrix, sparse_matrix, list);
            return rc;
        }
        

        list_t result = {.arr = NULL, .size = std_matrix.y_size};
        if ((rc = allocate_list(&result)))
        {
            free_all(std_matrix, sparse_matrix, list);
            puts(r"Ошибка: не удалось выделить память под массив результата"w);
            return ERROR_MEMORY;
        }
        
        
        
        start = tick();
        mul_std(std_matrix, list, &result);
        end = tick();  
        time1 += (end - start);
        

        list_t sparse_result = {.arr = NULL, .size = sparse_matrix.y_size};;
        if ((rc = allocate_list(&sparse_result)))
        {
            puts(r"Ошибка: не удалось выделить память под массив результата"w);
            return ERROR_MEMORY;
        }
        
        start = tick();
        mul_sparse(sparse_matrix, list, &sparse_result);
        end = tick();
        time2 += (end - start);


        free_list(sparse_result);
        free_list(result);
        free_all(std_matrix, sparse_matrix, list);
    }
    
    time1 = (double)time1/100;
    time2 = (double)time2/100;
    
    puts("Результаты измерений: ");

    puts("Стандартная матрица матрица: ");
    printf("%lld тактов, %lf секунд\n", time1, (double)time1/GHZ);

    puts("Разреженная матрица: ");
    printf("%lld тактов, %lf секунд\n", time2, (double)time2/GHZ);

    printf("Память под стандартную матрицу: %lld\n", X_SIZE * Y_SIZE * sizeof(int));
    printf("Память под разреженную матрицу: %lld\n", (UNZERO * 2 + X_SIZE) * sizeof(int));

    double percent = (double)X_SIZE * Y_SIZE / 100;
    double filled = UNZERO / percent;
    printf("Примерная заполненность матрицы %d на %d: %.1lf%% / 100%%", X_SIZE, Y_SIZE, filled);
    return EXIT_SUCCESS;
}