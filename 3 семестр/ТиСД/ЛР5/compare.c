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

int compare_turns(void)
{
    int menu_action, rc;
	int64_t start, end;
	
    int array[MAXIMUM_TURN_SIZE];
	
    turn_array_t turn_array;
    turn_array.size = 0;
    turn_array.head = array + MAXIMUM_TURN_SIZE - 1;
    turn_array.tail = turn_array.head;

    turn_list_t list;
    list.size = 0;
    list.head = NULL;

    array_freed_areas_t freed_array;
    freed_array.array = NULL;
    freed_array.size = 0;

	puts(y"Сравнение проводится только в пунктах, реализующих какие-либо " 
		  "внутренние алгоритмы работы с очередью и не зависящие более чем единожды " 
		  "от человека, а именно в пунктах 2 и 3"w);
    puts("Первая очередь - массив");
    puts("Вторая очередь - список\n");

    while(1)
    {  
        if ((rc = read_menu_action(&menu_action)))
        {
            free(freed_array.array);
            free_turn_list(&list);
            return rc;
        }
        
		
        if (menu_action == 1)
        {
            int add_num;
            if ((rc = read_add_num(&add_num, turn_array.size)))
            {
                free(freed_array.array);
                free_turn_list(&list);
                return rc;
            }

            if ((rc = add_to_array(&turn_array, add_num)))
            {
                free(freed_array.array);
                free_turn_list(&list);
                return rc;
            }
			
            if ((rc = add_to_list(&turn_array, add_num, &list)))
            {
                free(freed_array.array);
                free_turn_list(&list);
                return rc;
            }
        }
		
		
        if (menu_action == 2)
        {
            int add_num;
            if ((rc = read_add_num(&add_num, turn_array.size)))
            {
                free(freed_array.array);
                free_turn_list(&list);
                return rc;
            }
            
			start = 0;
            end = 0;
			
            int test_array[MAXIMUM_TURN_SIZE];
            turn_array_t test_turn_array;
            test_turn_array.size = 0;
            test_turn_array.head = test_array + MAXIMUM_TURN_SIZE - 1;
            test_turn_array.tail = test_turn_array.head;

            for (int i = 0; i < 100; i++)
            {
                start += tick();
                fill_to_array_randomly(&test_turn_array, add_num);
                end += tick();

                remove_from_array(&test_turn_array, add_num);
            } 
            fill_to_array_randomly(&turn_array, add_num);

            print_result(start / 100, end / 100);
            printf(c"Затраченная память под очередь (массив) - %llu байт\n\n"w, MAXIMUM_TURN_SIZE * sizeof(int) + sizeof(turn_array_t));

            start = 0;
            end = 0;

            turn_list_t test_list;
            test_list.size = 0;
            test_list.head = NULL;

            for (int i = 0; i < 100; i++)
            {
                start += tick();
                rc = fill_to_list_randomly(&test_list, add_num);
                end += tick();
                
                if (rc)
                {
                    free(freed_array.array);
                    free_turn_list(&list);
                    return rc;
                }

                remove_from_list(&test_list, add_num);
            }
            if ((rc = fill_to_list_randomly(&list, add_num)))
            {
                free(freed_array.array);
                free_turn_list(&list);
                return rc;
            }

            print_result(start / 100, end / 100);
            printf(c"Затраченная память под очередь (список) - %llu байт\n\n"w, 
			list.head == NULL ? 0 : list.size * sizeof(elem_turn_list_t) + sizeof(turn_list_t) - sizeof(int64_t));
        }
        
		
		if (menu_action == 3)
        {
            int remove_num;
            if ((rc = read_num_remove(&remove_num, turn_array.size)))
            {
                free(freed_array.array);
                free_turn_list(&list);
                return rc;
            }

			start = 0;
            end = 0;

            int test_array[MAXIMUM_TURN_SIZE];
			turn_array_t test_turn_array;
            test_turn_array.size = 0;
            test_turn_array.head = test_array + MAXIMUM_TURN_SIZE - 1;
            test_turn_array.tail = test_turn_array.head;

            for (int i = 0; i < 100; i++)
            {
                fill_to_array_randomly(&test_turn_array, remove_num);
                
                start += tick();
                remove_from_array(&test_turn_array, remove_num);
                end += tick();
            }

            if ((rc = add_addresses(&freed_array, remove_num, &list)))
            {
                free_turn_list(&list);
                return rc;
            }
            remove_from_array(&turn_array, remove_num);

            print_result(start / 100, end / 100);

            start = 0;
            end = 0;
            
            turn_list_t test_list;
            test_list.size = 0;
            test_list.head = NULL;

            for (int i = 0; i < 100; i++)
            {
                if ((rc = fill_to_list_randomly(&test_list, remove_num)))
                {
                    free(freed_array.array);
                    free_turn_list(&list);
                    return rc;
                }
                
                start += tick();
                remove_from_list(&test_list, remove_num);
                end += tick();
            }

            remove_from_list(&list, remove_num);

            print_result(start / 100, end / 100);
        }
		
        if (menu_action == 4)
            print_turn_array(&turn_array);
        if (menu_action == 5)
            print_turn_list(&list);
        if (menu_action == 6)
            print_freed_array(&freed_array);
        
		if (menu_action == 0)
        {
            free(freed_array.array);
            free_turn_list(&list);
            break;
        }
    }

    return EXIT_SUCCESS;
}