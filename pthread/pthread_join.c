#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

static void * threadFunc(void *arg)
{
	char *s = (char *)arg;
	printf("%s\n", s);
	return (void *)strlen(s);
}



int main(int argc, char **argv)
{
	pthread_t pthid;
	void *res;
	int s;

	s = pthread_create(&pthid, NULL, threadFunc, "hello world\n");
	printf("Message from Main()\n");
	//s = pthread_join(pthread_self, &res);
	s = pthread_join(pthid, &res);
	printf("Thread return %ld\n", (long)res);

	exit(EXIT_SUCCESS);
}
