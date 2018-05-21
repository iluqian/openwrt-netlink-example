#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>
pid_t gettid(void)
{
	return syscall(__NR_gettid);
}

static void * threadFunc(void *arg)
{
	char *s = (char *)arg;
	printf("%s", s);
	printf("getpid() =%u,gettid() = %u,pthread_self()=%ul\n",getpid(), gettid(), pthread_self());
	return (void *)strlen(s);
}



int main(int argc, char **argv)
{
	pthread_t pthid;
	void *res;
	int s;

	s = pthread_create(&pthid, NULL, threadFunc, "hello world\n");
	printf("Message from Main()\n");
	
	s = pthread_join(pthid, &res);
	printf("Thread return %ld\n", (long)res);
//	pthread_exit(NULL);
	exit(EXIT_SUCCESS);
}
