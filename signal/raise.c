#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[])
{
		int i;
	printf("---------\n");
	while(1)
	{
		usleep(50);
		i++;
		printf("%d\n",i);
		if(i == 10000)
		{
			raise(SIGQUIT);
		}
	}
	exit(EXIT_SUCCESS);
}
