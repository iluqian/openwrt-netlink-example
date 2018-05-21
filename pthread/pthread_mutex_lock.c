/*
 加了读写锁
 main thread ID is 140156352694080
 In main func gn = 0
 thread ID is 140156344502016 
 thread ID is 140156336109312 
 thread ID is 140156327716608 
 Now gn = 30000000

 real	0m6.714s
 user	0m6.127s
 sys	0m13.005s
 
 //加了互斥锁
 main thread ID is 140314392917824
 In main func gn = 0
 thread ID is 140314384725760 
 thread ID is 140314367940352 
 thread ID is 140314376333056 
 Now gn = 30000000

 real	0m2.882s
 user	0m3.239s
 sys	0m5.077s
从上面可以看出就速度而言读写锁并不比互斥锁快，反而明显差很多；
主要是我的程序加了写锁，
 【总之】：
 也就是说，在一些写操作比较多或是本身需要同步的地方并不多的程序中我们应该使用互斥量，
 而在读操作远大于写操作的一些程序中我们应该使用读写锁来进行同步
 * */
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
pthread_rwlock_t rwlock;
static void * threadFunc(void *arg)
{
	unsigned int i;
	printf("thread ID is %lu \n",pthread_self());
	//sleep(1);
	for( i = 0; i<10000000;i++)
	{
		//usleep(10000);
		pthread_mutex_lock(&mutex);
//		pthread_rwlock_wrlock(&rwlock);
		gn++;
//		printf("pthread_self() = %lu,gn = %d\n",pthread_self(),gn);
		pthread_mutex_unlock(&mutex);
//		pthread_rwlock_unlock(&rwlock);
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
//对于PTHREAD_MUTEX_INITIALIZER 静态初始化的互斥量，无需调用pthread_mutex_destory()
	//pthread_mutex_destroy(&mutex);
	printf("Now gn = %d\n",gn);
	return 0;
}
