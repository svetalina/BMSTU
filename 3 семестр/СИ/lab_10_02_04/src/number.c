#include "number.h"
#include "list.h"
#include "node.h"

static int get_prime_num(int base_num)
{
    int flag = 1;
    while (flag)
    {
        flag = 0;
        base_num++;
        
        for (int i = 2; i < base_num; i++)
            if (base_num % i == 0)
            {
                flag = 1;
                break;
            }
    }
    
    return base_num;
}

int number_decomposion(node_t **head, int num)
{
    if (num < 2)
        return ERROR_DECOMPOSOTION;
    
    node_t *node;
    
    int last_num = 1;
    int power;

    while (num != 1)
    {
        power = 0;
        
        last_num = get_prime_num(last_num);
        while (num % last_num == 0)
        {
            num /= last_num;
            power++;
        }
        
        if (power != 0)
        {
            node = node_create(last_num, power);
            *head = list_add_front(*head, node);
        }
    }
    
    return EXIT_SUCCESS;
}

int number_out(void)
{
    int rc;
    
    int num;
    if (scanf("%d", &num) != 1)
        return ERROR_SYMBOLS;
    
    node_t *list = NULL;
    if ((rc = number_decomposion(&list, num)))
        return rc;
    
    list_print(list);
    list_free(list);

    return EXIT_SUCCESS;
}

int number_sqr(void)
{
    int rc;
    
    int num;
    if (scanf("%d", &num) != 1)
        return ERROR_SYMBOLS;
    
    node_t *list = NULL;
    if ((rc = number_decomposion(&list, num)))
        return rc;
    
    list_sqr(&list);
    list_print(list);
    list_free(list);

    return EXIT_SUCCESS;
}

int numbers_mul(void)
{
    int rc;
    
    int num_1, num_2;
    if (scanf("%d %d", &num_1, &num_2) != 2)
        return ERROR_SYMBOLS;

    node_t *list_1 = NULL;
    if ((rc = number_decomposion(&list_1, num_1)))
        return rc;
    node_t *list_2 = NULL;
    if ((rc = number_decomposion(&list_2, num_2)))
    {
        list_free(list_1);
        return rc;
    }
    
    node_t *list_res = NULL;
    list_mul(list_1, list_2, &list_res);

    list_print(list_res);
    list_free(list_1);
    list_free(list_2);
    list_free(list_res);

    return EXIT_SUCCESS;
}

int numbers_div(void)
{
    int rc;
    
    int num_1, num_2;
    if (scanf("%d %d", &num_1, &num_2) != 2)
        return ERROR_SYMBOLS;

    node_t *list_1 = NULL;
    if ((rc = number_decomposion(&list_1, num_1)))
        return rc;
    node_t *list_2 = NULL;
    if ((rc = number_decomposion(&list_2, num_2)))
    {
        list_free(list_1);
        return rc;
    }
    
    int num_res = list_delete_equal_num(list_1, list_2);
    node_t *list_res = NULL;
    if ((rc = number_decomposion(&list_res, num_res)))
    {
        list_free(list_1);
        list_free(list_2);
        return rc;
    }

    list_print(list_res);
    list_free(list_1);
    list_free(list_2);
    list_free(list_res);

    return EXIT_SUCCESS;
}