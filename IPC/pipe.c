#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
		int fd[2];
		int ret = pipe(fd); //管道默认阻塞。默认读写两端阻塞
		//fcntl 1. 复制文件描述符dup，2. 修改文件属性open 时对应的flag属性
		//获取原来的flags
		// int flags = fcntl(fd[0], F_GETFL);
		// 设置新的flags
		// flags |=O_NONBLOCK
		// fcntl(fd[0],F_SETFL,flags);
		if(ret == -1)
				exit(1);
		printf("pipe[0]=%d\n",fd[0]);
		printf("pipe[1]=%d\n",fd[1]);
		//测试管道缓冲区的大小
		long size = pathconf("./", _PC_PIPE_BUF);
		printf("pipe size = %d\n",size); //ulimit -a 也可以查看
		printf("pc_name_max-%d\n", pathconf("./",_PC_NAME_MAX)); //查看文件名字最大长度
		close(fd[0]);
		close(fd[1]);
		return 0;
}
