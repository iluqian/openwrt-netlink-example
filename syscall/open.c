/*
 * 使用四个通用的文件io可以对所有类型的文件执行IO操作，例如：
 * ./a.out test.old test.new
 * ./a.out test.old /dev/tty
 * ./a.out /dev/tty test.new
 * ./a.out /dev/pts/16 /dev/tty
 *
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
	char buf[BUF_SIZE];
	int numRead;
	if(argc != 3 || strcmp(argv[1],"--help") == 0)
	{
			printf("USEAGE: %s oldfile newfile\n",argv[0]);
			exit(EXIT_FAILURE);
	}
	int i = open(argv[1],O_RDONLY);
	if(i<0)
	{
			perror("open");
			printf("errno=%d\n",errno);
			char *co = strerror(errno);
			printf("%s\n",co);
			exit(EXIT_FAILURE);
	}
	printf("open old successed,fd:%d\n",i);

	int o = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);

	if(o<0)
	{
			perror("open");
			printf("errno=%d\n",errno);
			char *co = strerror(errno);
			printf("%s\n",co);
			exit(EXIT_FAILURE);
	}
	printf("open new successed,fd:%d\n",o);

	while((numRead = read(i, buf, BUF_SIZE))>0)
	{
			write(o, buf, numRead);
	}
	close(i);
	close(o);

	return 0;
}
