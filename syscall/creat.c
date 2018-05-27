#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> //for strerror(int errnum)
int main(int argc, char *argv[])
{
	if(argc != 2 || strcmp(argv[1],"--help") == 0)
	{
			printf("USEAGE: %s file\n",argv[0]);
			exit(EXIT_FAILURE);
	}
	int i = creat(argv[1],777);
	if(i<0)
	{
	
			perror("create");
			printf("errno=%d\n",errno);
			char *co = strerror(errno);
			printf("%s\n",co);
			exit(EXIT_FAILURE);
	}
	printf("create successed,%d\n",i);

	return 0;
}
