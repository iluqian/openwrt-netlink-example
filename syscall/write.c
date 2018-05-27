#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc, char * argv[], char * env[])
{
	write(1,"hellworld\n",10);
	//输出当前进程的环境变量
	while(*env)
			puts(*env++);
	exit(EXIT_SUCCESS);
}
