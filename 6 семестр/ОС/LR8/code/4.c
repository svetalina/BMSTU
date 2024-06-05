#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "out.txt"

int main()
{
	char alphabet[] = "Abcdefghijklmnopqrstuvwxyz";

	int fd1 = open(FILENAME, O_WRONLY | O_CREAT);
	int fd2 = open(FILENAME, O_WRONLY);

	for (char i = 0; i < sizeof(alphabet); ++i) 
	{
		if (i % 2)
			write(fd1, alphabet + i, 1);
		else 
			write(fd2, alphabet + i, 1);
		
		printf("%c\n", *(alphabet + i));
    }
 
	close(fd1);
	close(fd2);

	return 0;
}