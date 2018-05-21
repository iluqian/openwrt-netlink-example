#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>

//用宏PTHREAD_MUTEX_INITIALIZER 静态的初始化锁，
//也可以使用pthread_mutex_init()动态的创建
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int gn;
static void * threadFunc(void *arg)
{
	int i;
	printf("thread ID is %lu \n",pthread_self());
	//sleep(1);
	for( i = 0; i<10000;i++)
	{
		usleep(100);
		pthread_mutex_lock(&mutex);
		gn++;
		printf("pthread_self() = %lu,gn = %d\n",pthread_self(),gn);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t pthid_1, pthid_2,pthid_3;
	printf("main thread ID is %lu\n", pthread_self());
	//gn = 1;
	printf("In main func gn = %d\n",gn);
	pthread_create(&pthid_1,NULL,threadFunc,NULL);
	pthread_create(&pthid_2,NULL,threadFunc,NULL);
	pthread_create(&pthid_3,NULL,threadFunc,NULL);
	pthread_join(pthid_1,NULL);
	pthread_join(pthid_2,NULL);
	pthread_join(pthid_3,NULL);
	pthread_mutex_destroy(&mutex);
	printf("Now gn = %d\n",gn);
	return 0;
}
