/*
 *  【所有的系统调用都是以原子操作方式执行的】
 *
 *  程序中执行了两步操作，在检查文件是否存在和创建文件这两个动作之间人为制造了一个长时间的等待；
 * 	第一个进程 ./a.out liujie &    第二个进程   ./a.out liujie
 *	第一个进程执行检查文件是否存在后，sleep(5)，  当第二个进程执行完检查文件是否存在后，第一个进程开始创建文件，
 *	第二个进程再执行创建文件时，文件已经存在，此时第二个进程以为文件是自己创建的，造成错误的结论；
 * 
 *  总之: 同时指定O_EXCL | O_CREAT 作为open的标志位时，如果要打开的文件已经存在，则返回一个错误；提示文件已经存在
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> //for strerror(int errnum)
#include <sys/stat.h>
#include <sys/types.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
int main(int argc, char *argv[])
{
	int fd;
	if(argc != 2 || strcmp(argv[1],"--help") == 0)
	{
			printf("USEAGE: %s file\n",argv[0]);
			exit(EXIT_FAILURE);
	}



	fd = open(argv[1], O_WRONLY);
	if(fd != -1){
			printf("[PID %ld] File \" %s \" already exists\n",(long)getpid(),argv[1]);
			close(fd);
	}
	else{
		if(errno != ENOENT){
			perror("open");

		}
		else{

			printf("[PID %ld] File \" %s \" doen't exist yet\n",(long)getpid(),argv[1]);
			sleep(5);
			puts("Done sleeping\n");
			fd = open(argv[1],O_WRONLY|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR);
			if(fd == -1)
					perror("open");
			printf("[PID %ld] created file \"%s \" exclusively\n", (long)getpid(),argv[1]);
		}
	
	}
	return 0;
}
