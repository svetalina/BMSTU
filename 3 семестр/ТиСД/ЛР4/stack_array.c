#include "head.h" 

int stack_array(void)
{  
    int rc; 
    
    int action_type;
    char array[MAX_STACK_SIZE];
    stack_array_t stack_array = {array - 1, 0};

    while(1)
    {   
        if ((rc = read_action_type(&action_type)))
            return rc;

        if (action_type == 1)
        {   
            int num_add;
            if ((rc = read_num_to_add_stack_array(&num_add, stack_array.size)))
                return rc;
            
            add_stack_array(&stack_array, num_add);
        }
        
        if (action_type == 2)
        {
            int num_add;
            if ((rc = read_num_to_add_stack_array(&num_add, stack_array.size)))
                return rc;

            add_stack_array_random(&stack_array, num_add);
        }
        
        if (action_type == 3)
        {
            int num_remove;
            if ((rc = read_num_to_remove_stack_array(&num_remove, stack_array.size)))
                return rc;

            remove_stack_array(&stack_array, num_remove);
        }
       
        if (action_type == 4)
        {
            print_stack_array(&stack_array);
        }
        
        if (action_type == 5)
        {
           check_brackets_array(&stack_array);
        }
        
        if (action_type == 0)
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

int add_stack_array(stack_array_t *stack_array, int num_add)
{
    int rc;

    printf("Введите %d элементов стека\n", num_add);
    for (int i = 0; i < num_add; i++)
    {
        stack_array->ptr++;
        
        if ((rc = read_new_el(stack_array->ptr)))
            return rc;
        
        stack_array->size++;
    }

    return EXIT_SUCCESS;
}

void add_stack_array_random(stack_array_t *stack_array, int num_add)
{
    srand(time(NULL));
    char array_possible_symbol[] = {'(', ')', '[', ']', '{', '}', '0', '1', '+', '-'};

    for (int i = 0; i < num_add; i++)
    {
        stack_array->ptr++;
        
        *stack_array->ptr = array_possible_symbol[rand() % 10];
        
        stack_array->size++;
    }
}

void remove_stack_array(stack_array_t *stack_array, int num_remove)
{
    for (int i = 0; i < num_remove; i++)
    {
        stack_array->ptr--;
        stack_array->size--;
    }

}

void check_brackets_array(stack_array_t *stack_array)
{
    int flag_round = 0, flag_square = 0, flag_curly = 0;
    
    for (int i = stack_array->size; i > 0; i--)
    {
        if (*(stack_array->ptr) == ')')
            flag_round++;
        if (*(stack_array->ptr) == '(' && flag_round != 1)
        {
            flag_round = 1;
            break;
        }
        else if (*(stack_array->ptr) == '(')
            flag_round = 0;
        
        if (*(stack_array->ptr) == ']')
            flag_square++;
        if (*(stack_array->ptr) == '[' && flag_square != 1)
        {
            flag_square = 1;
            break;
        }
        else if (*(stack_array->ptr) == '[')
            flag_square = 0;
        
        if (*(stack_array->ptr) == '}')
            flag_curly++;
        if (*(stack_array->ptr) == '{' && flag_curly != 1)
        {
            flag_curly = 1;
            break;
        }
        else if (*(stack_array->ptr) == '{')
            flag_curly = 0;

        stack_array->ptr--;
    }
    stack_array->size = 0;
    
    if (!flag_round && !flag_square && !flag_curly)
        puts(green"Скобки расставлены верно"w);
    else
        puts(red"Скобки расставлены неверно"w);
}