#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int gn;
static void * threadFunc_1(void *arg)
{
	int i;
	printf("thread ID is %lu \n",pthread_self());
	//sleep(1);
	pthread_mutex_lock(&mutex);
	for( i = 0; i<10000;i++)
		gn++;
	printf("Now gn = %d\n",gn);
	pthread_mutex_unlock(&mutex);

	return NULL;
}

static void * threadFunc_2(void *arg)
{
	printf("thread ID is %lu \n",pthread_self());
	int i;
	pthread_mutex_lock(&mutex);
	for( i = 0; i<10000;i++)
		gn++;
	printf("Now gn = %d\n",gn);
	pthread_mutex_unlock(&mutex);

	return NULL;
}
int main(int argc, char *argv[])
{
	pthread_t pthid_1, pthid_2;
	printf("main thread ID is %lu\n", pthread_self());
	//gn = 1;
	printf("In main func gn = %d\n",gn);
	pthread_create(&pthid_1,NULL,threadFunc_1,NULL);
	pthread_create(&pthid_2,NULL,threadFunc_2,NULL);
	pthread_join(pthid_1,NULL);
	pthread_join(pthid_2,NULL);
	//pthread_mutex_destroy(&mutex);
	return 0;
}
