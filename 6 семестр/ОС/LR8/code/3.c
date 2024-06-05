#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() 
{
	FILE *f1 = fopen("out.txt", "w");
	FILE *f2 = fopen("out.txt", "w");
  
	for (char letr = 'a'; letr < 'z'; letr++)
	{
		if (letr % 2)
			fprintf(f1, "%c", letr);
		else
			fprintf(f2, "%c", letr);
	}

	fclose(f2);
	fclose(f1);
	return 0;
}