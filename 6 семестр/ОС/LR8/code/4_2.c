#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
	
void *thread_f1(void *args)
{
	int fd = open("out.txt", O_WRONLY | O_CREAT | O_APPEND);
	char alphabet[] = "nopqrstuvwxyz";
		
	for (char i = 0; i < sizeof(alphabet); ++i) 
	{
		write(fd, alphabet + i, 1);
		printf("%c\n", *(alphabet + i));
	}
		
	close(fd);
}
	
int main() 
{
	char alphabet[] = "abcdefghijklm";
		
	pthread_t thread;
	int rc = pthread_create(&thread, NULL, thread_f1, NULL);
		
	int fd = open("out.txt", O_WRONLY | O_CREAT | O_APPEND);
		
	for (char i = 0; i < sizeof(alphabet); ++i) 
	{
		write(fd, alphabet + i, 1);    
		printf("%c\n", *(alphabet + i));
	}
		
	pthread_join(thread, NULL);
	close(fd);
		
	return 0;
}