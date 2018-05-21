/*处理读写锁的例程*/

//初始化读写锁 //pthread_rwlock_init 语法
//读取读写锁中的锁  //pthread_rwlock_rdlock 语法
//读取非阻塞读写锁中的锁 //pthread_rwlock_tryrdlock 语法
//写入读写锁中的锁  //pthread_rwlock_wrlock 语法
//写入非阻塞读写锁中的锁 //pthread_rwlock_trywrlock 语法
//解除锁定读写锁  //pthread_rwlock_unlock 语法
//销毁读写锁 //pthread_rwlock_destroy 语法

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

/** 实现1: 运用读写锁解决”读者写者问题” 
解题思路: 将需要读写的文件实现为一个字符串; 
读者进程: 一次可以将该字符串全部读出, 然后打印读取信息 
写者进程: 一次只能修改一个字符(该字符从A~Z循环写入), 修改之后打印写入信息 
**/  
//读写锁  
pthread_rwlock_t rwlock;  
const unsigned READERCOUNT = 2; //读者数  
const unsigned WRITERCONUT = 5; //写者数  
  
const int PAPERSIZE = 32;       //文件长度  
char paper[PAPERSIZE+1];        //文件  
  
unsigned short int write_index = 0; //写者需要写入的位置  
char ch = 'A';  //写者需要写入的字母  
pthread_t thread[READERCOUNT+WRITERCONUT];  //读者+写者线程    
  
//读者线程  
void *reader(void *args)  
{  
    int number = *(int *)args;  
    delete (int *)args;  
  
    while (true)  
    {  
        //获取共享锁  
        pthread_rwlock_rdlock(&rwlock);  
        //开始读  
        printf("## reader %d was reading...\n", number);  
        printf("text: %s\n", paper);  
        printf("   reader %d end reading...\n", number);  
        //解锁共享锁  
        pthread_rwlock_unlock(&rwlock);  
  
        sleep(1);  
    }  
    pthread_exit(NULL);  
}  
//写者线程  
void *writer(void *args)  
{  
    int number = *(int *)args;  
    delete (int *)args;  
    while (true)  
    {  
        //获取写锁  
        pthread_rwlock_wrlock(&rwlock);  
        //开始写  
        printf("++ writer %d was writing...\n", number);  
        paper[write_index] = ch;  
        write_index = (write_index+1)%PAPERSIZE;  
        ch = ch+1;  
        if (ch > 'Z')  
            ch = 'A';  
        printf("   writer %d end writing...\n", number);  
        //释放写锁  
        pthread_rwlock_unlock(&rwlock);  
  
        sleep(1);  
    }  
  
    pthread_exit(NULL);  
}  
  
int main()  
{  
    memset(paper, 0, sizeof(paper));  
    pthread_rwlock_init(&rwlock, NULL);  
  
    for (unsigned int i = 0; i < READERCOUNT; ++i)  
        pthread_create(&thread[i], NULL, reader, new int(i));  
    for (unsigned int i = 0; i < WRITERCONUT; ++i)  
        pthread_create(&thread[READERCOUNT+i], NULL, writer, new int(i));  
    for (unsigned int i = 0; i < READERCOUNT+WRITERCONUT; ++i)  
        pthread_join(thread[i], NULL);  
  
    pthread_rwlock_destroy(&rwlock);  
} 
