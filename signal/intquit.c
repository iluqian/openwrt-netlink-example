/*
 * 	函数原型：
 *	void (*signal(int sig, void (*func)(int)))(int);
 *
 *	为两个不同的信号建立同一处理函数
 * */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

static void sigHandle(int sig)
{
	if(sig == SIGINT)
		printf(" Caught SIGINT\n");
	if(sig == SIGQUIT)
		printf(" Caught SIGQUIT\n");
}

int main(int argc, char *argv[])
{
	int j;

	if(signal(SIGINT,sigHandle) == SIG_ERR)
			perror("signal");
	if(signal(SIGQUIT,sigHandle) == SIG_ERR)
			perror("signal");
//	while(1)
//			pause();
	for(j = 0; ; j++)
	{
		printf("%d\n",j);
		usleep(50000);
	}
	exit(EXIT_SUCCESS);
}
