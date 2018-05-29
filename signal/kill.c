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

int main(int argc, char *argv[])
{
	while(1){
	
		kill(3761,SIGQUIT);
		sleep(1);
		kill(3761,SIGINT);
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
