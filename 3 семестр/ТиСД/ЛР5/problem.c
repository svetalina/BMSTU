#include "head.h"

void matrix_shift(float matrix[2][10000], int size, int start, int shift)
{
    for (int i = 0; i < 2; i++)
        for (int j = size + 1; j > start + shift; j--)
            matrix[i][j] = matrix[i][j - 1];
}

int solution_problem(void)
{
    float matrix[2][10000] = { 0 };
    
    int size = 0;
    int num_in = 0, num_in_all = 0, num_out = 0, num_out_all = 0; 
    int arrival_time = 0, simul_time = 0;
    int cur_turn = 0;
    int num_second = 0;
    
    float timer = 0;
    int begin_t1, step_t1, t1 = time(NULL);
    int begin_t2, step_t2, t2 = time(NULL);
    int begin_t3, step_t3, t3 = time(NULL);
    int time_in_turn = 0;
    
    srand(t1++);
    step_t1 = rand() % (MAX_T1 - MIN_T1 + 1);
    begin_t1 = timer;
    
    srand(t2++);
    step_t2 = rand() % (MAX_T2 - MIN_T2 + 1);
    begin_t2 = timer;
		
    srand(t3++);
    step_t3 = rand() % (MAX_T3 - MIN_T3 + 1);
    begin_t3 = timer;
    
    int shift;
    
    matrix[0][0] = 2;
    matrix[1][0] = timer;
    size++;
    num_in_all++;
    
    while (num_out != 1000)
    {
        // for (int i = 0; i < num_in; i++)
            // printf("%f ", matrix[0][i]);
        // puts("\n");
        
        if (timer >= begin_t1 + step_t1)
        {
            arrival_time += step_t1;
            size++;
            matrix[0][num_in_all] = 1;
            matrix[1][num_in_all] = timer;
            num_in++;
            num_in_all++;
            
            srand(t1++);
            step_t1 = rand() % (MAX_T1 - MIN_T1 + 1);
            begin_t1 = timer;
        }
        if (size != 0 && 
        ((timer >= begin_t2 + step_t2 && matrix[0][num_out_all] == 1) || 
        (timer >= begin_t3 + step_t3 && matrix[0][num_out_all] == 2)))
        {
            if (matrix[0][num_out_all] == 1)
            {
                simul_time += step_t2;
                cur_turn += size;
                time_in_turn += timer - matrix[1][num_out_all];
                size--;
                num_out++;
                num_out_all++;
                
                srand(t2++);
                step_t2 = rand() % (MAX_T2 - MIN_T2 + 1);
                begin_t2 = timer;
            }
            if (matrix[0][num_out_all] == 2)
            {
                simul_time += step_t3;
                cur_turn += size;
                time_in_turn += timer - matrix[1][num_out_all];
                size--;
                num_out_all++;
                num_second++;
                
                shift = size >= 4 ? 4 : size;
                matrix_shift(matrix, num_in_all, num_out_all, shift);
                matrix[0][num_out_all + shift] = 2;
                matrix[1][num_out_all + shift] = timer;
                num_in_all++;
                size++;
                
                srand(t3++);
                step_t3 = rand() % (MAX_T3 - MIN_T3 + 1);
                begin_t3 = timer;
            }
            
            if (num_out % 100 == 0 && num_out != 0)
            {
                printf("Текущая длина очереди - %d\n", size);
                printf("Средняя длина очереди - %d\n", cur_turn / num_out_all);
                printf("Среднее время пребывания заявок в очереди - %d е.в.\n", time_in_turn / num_out);
                printf("Количество вошедших заявок в очередь всего - %d\n", num_in_all);
                printf("Количество вышедших заявок из очереди 1-го типа - %d\n", num_out);
                printf("Количество вышедших заявок из очереди всего - %d\n", num_out_all);
                printf("Количество вошедших заявок в очередь 1-го типа - %d\n\n", num_in);
            }
        }
        
        timer += 0.1;
    }

    printf(g"Результаты\n\n");
    printf("Время моделирования - %d е.в.\n", (int)timer);
    printf("Время работы аппарата ОА - %d е.в.\n", simul_time);
    printf("Время простоя - %d е.в.\n", arrival_time - simul_time);
    printf("Среднее время пребывания заявок в очереди - %d е.в.\n", time_in_turn / num_out);
    printf("Количество вошедших заявок в очередь 1-го типа - %d\n", num_in);
    printf("Количество вошедших заявок в очередь всего - %d\n", num_in_all);
    printf("Количество вышедших заявок из очереди 1-го типа - %d\n", num_out);
    printf("Количество вышедших заявок из очереди всего - %d\n", num_out_all);
    printf("Средняя длина очереди - %d\n", cur_turn / num_out_all);
    printf("Количество обращений заявок второго типа - %d\n"w, num_second);

    return EXIT_SUCCESS;
}
