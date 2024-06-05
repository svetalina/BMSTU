#include "head.h" 

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

void print_result(int64_t start, int64_t end)
{
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start)/HZ);  
}

int comparison_stacks(void)
{
    int rc;
    int64_t start, end;
    
    int action_type;
    char array[MAX_STACK_SIZE];
    stack_array_t stack_array = {array - 1, 0};

    el_stack_list_t *el_stack_list = NULL;
    
    puts(y"Производить сравнение целесообразно только для пунктов меню 2, 3, 5"w);
    puts("Первый стек - массив");
    puts("Второй стек - список");

    while(1)
    {        
        if ((rc = read_action_type(&action_type)))
        {
            free_stack_list(&el_stack_list);
            return rc;
        }

        if (action_type == 2)
        {
            int num_add;

            if ((rc = read_num_to_add_stack_array(&num_add, stack_array.size)))
            {
                free_stack_list(&el_stack_list);
                return rc;
            }
            
            start = 0;
            end = 0;
            for (int i = 0; i < 100; i++)
            {
                start += tick();
                add_stack_array_random(&stack_array, num_add);
                end += tick();

                remove_stack_array(&stack_array, num_add);
            } 
            add_stack_array_random(&stack_array, num_add);

            print_result(start / 100, end / 100);
            printf("Затраченная память под стек (массив) - %llu байт\n", MAX_STACK_SIZE * sizeof(int) + sizeof(stack_array_t));

            start = 0;
            end = 0;
            for (int i = 0; i < 100; i++)
            {
                start += tick();
                add_stack_list_random(&el_stack_list, num_add);
                end += tick();

                remove_stack_list(&el_stack_list, num_add);
            }
            add_stack_list_random(&el_stack_list, num_add);

            print_result(start / 100, end / 100);
            printf("Затраченная память под стек (список) - %llu байт\n\n", el_stack_list->num_el * sizeof(el_stack_list_t));
        }
        
        if (action_type == 3)
        {
            int num_remove;
            if ((rc = read_num_to_remove_stack_array(&num_remove, stack_array.size)))
            {
                free_stack_list(&el_stack_list);
                return rc;
            }
            
            start = 0;
            end = 0;
            for (int i = 0; i < 100; i++)
            {
                start += tick();
                remove_stack_array(&stack_array, num_remove);
                end += tick();

                add_stack_array_random(&stack_array, num_remove);
            }
            remove_stack_array(&stack_array, num_remove);

            print_result(start / 100, end / 100);
            printf("Затраченная память под стек (массив) - %llu байт\n", MAX_STACK_SIZE * sizeof(int) + sizeof(stack_array_t));

            start = 0;
            end = 0;
            for (int i = 0; i < 100; i++)
            {
                start += tick();
                remove_stack_list(&el_stack_list, num_remove);
                end += tick();

                add_stack_list_random(&el_stack_list, num_remove);
            }
            remove_stack_list(&el_stack_list, num_remove);

            print_result(start / 100, end / 100);
            printf("Затраченная память под стек (список) - %llu байт\n\n", el_stack_list->num_el * sizeof(el_stack_list_t));
        }
        
        if (action_type == 4)
        {
            
            start = 0;
            end = 0;
            start += tick();
            print_stack_array(&stack_array);
            end += tick();

            print_result(start, end);
            printf("Затраченная память под стек (массив) - %llu байт\n", MAX_STACK_SIZE * sizeof(int) + sizeof(stack_array_t));

            start = 0;
            end = 0;
            start += tick();
            print_stack_list(&el_stack_list);
            end += tick();

            print_result(start, end);
            printf("Затраченная память под стек (список) - %llu байт\n\n", el_stack_list->num_el * sizeof(el_stack_list_t));
        }
        
        if (action_type == 5)
        {
            start = 0;
            end = 0;
            start += tick();
            check_brackets_array(&stack_array);
            end += tick();
        
            print_result(start, end);
            printf("Затраченная память под стек (массив) - %llu байт\n", MAX_STACK_SIZE * sizeof(int) + sizeof(stack_array_t));

            start = 0;
            end = 0;
            start += tick();
            check_brackets_list(&el_stack_list);
            end += tick();

            print_result(start, end);
            printf("Затраченная память под стек (список) - %llu байт\n\n", el_stack_list->num_el * sizeof(el_stack_list_t));
        }
        
        if (action_type == 0)
        {
            free_stack_list(&el_stack_list);
            break;
        }
    }

    return EXIT_SUCCESS;
}