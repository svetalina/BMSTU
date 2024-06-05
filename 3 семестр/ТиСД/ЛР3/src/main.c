#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "matrix.h"
#include "memory.h"
#include "mul.h"
#include "print.h"
#include "time.h"
#include "struct.h"

int main(void)
{
    int rc;
    
    setbuf(stdout, NULL);
    
    print_info();

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
    
    print_sparse_list(list);

    list_t result = {.arr = NULL, .size = std_matrix.y_size};
    if ((rc = allocate_list(&result)))
    {
        free_all(std_matrix, sparse_matrix, list);
        puts(r"Ошибка: не удалось выделить память под массив результата"w);
        return ERROR_MEMORY;
    }
    
    
    int64_t start, end, time1 = 0, time2 = 0;
    
    start = tick();
    mul_std(std_matrix, list, &result);
    end = tick();  
    time1 = (double)(end - start) / 100;
    
    puts(m"\nРезультат вычислений: "w);
    print_std_list(result);

    list_t sparse_result = {.arr = NULL, .size = sparse_matrix.y_size};;
    if ((rc = allocate_list(&sparse_result)))
    {
        puts(r"Ошибка: не удалось выделить память под массив результата"w);
        return ERROR_MEMORY;
    }
    
    start = tick();
    mul_sparse(sparse_matrix, list, &sparse_result);
    end = tick();
    time2 = (double)time2 / 100;
    
    puts(m"Результат вычислений (в разреженном виде): "w);
    print_sparse_list(sparse_result);

    print_result(sparse_matrix, std_matrix, time1, time2);

    free_list(sparse_result);
    free_list(result);
    free_all(std_matrix, sparse_matrix, list);
    return EXIT_SUCCESS;
}