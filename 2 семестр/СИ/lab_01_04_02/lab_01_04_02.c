#include <stdio.h>
#define HOUR 3600
#define MINUTE 60
#define OK 0

int main(void)
{
    int time_hour, time_minute, time_second;
    int time;
    scanf("%d", &time);
    
    time_hour = time / HOUR;
    time_minute = time % HOUR / MINUTE;
    time_second = time - time_hour * HOUR - time_minute * MINUTE;
    
    printf("%d : %d : %d ", time_hour, time_minute, time_second);
    
    return OK;
}


