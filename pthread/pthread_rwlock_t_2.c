/** 实现2: 运用Posix信号量使用”读者优先”策略解决”读者写者问题”
解题思路:
如果新读者到：
　　　①无读者、写者，新读者可以读；
　　　②有写者等待，但有其它读者正在读，则新读者也可以读；
　　　③有写者写，新读者等待。
如果新写者到：
　　　①无读者，新写者可以写；
　　　②有读者，新写者等待；
　　　③有其它写者，新写者等待。
**/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


// 需要用两个互斥量实现
pthread_mutex_t rmutex;
pthread_mutex_t wmutex;

const unsigned READERCOUNT = 5; //读者数
const unsigned WRITERCONUT = 5; //写者数

const int PAPERSIZE = 32;       //文件长度
char paper[PAPERSIZE+1];        //文件

unsigned short int write_index = 0; //写者需要写入的位置
char ch = 'A';  //写者需要写入的字母

pthread_t thread[READERCOUNT+WRITERCONUT];  //读者+写者线程

int nReader = 0;
//读者线程
void *reader(void *args)
{
    int number = *(int *)args;
    delete (int *)args;

    while (true)
    {
        pthread_mutex_lock(&rmutex);
        //如果是第一个读者, 则锁定wmutex
        if (nReader == 0)
            pthread_mutex_lock(&wmutex);
        ++ nReader;
        pthread_mutex_unlock(&rmutex);

        //开始读
        printf("## reader %d was reading...\n", number);
        printf("text: %s\n", paper);
        printf("   reader %d end reading...\n\n", number);

        pthread_mutex_lock(&rmutex);
        -- nReader;
        //如果是最后一个读者, 则解锁wmutex
        if (nReader == 0)
            pthread_mutex_unlock(&wmutex);
        pthread_mutex_unlock(&rmutex);

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
        pthread_mutex_lock(&wmutex);
        //开始写
        printf("++ writer %d was writing...\n", number);
        paper[write_index] = ch;
        write_index = (write_index+1)%PAPERSIZE;
        ch = ch+1;
        if (ch > 'Z')
            ch = 'A';
        printf("   writer %d end writing...\n\n", number);
        //释放写锁
        pthread_mutex_unlock(&wmutex);

        sleep(1);
    }

    pthread_exit(NULL);
}

int main()
{
    memset(paper, 0, sizeof(paper));
    pthread_mutex_init(&rmutex, NULL);
    pthread_mutex_init(&wmutex, NULL);

    for (unsigned int i = 0; i < READERCOUNT; ++i)
        pthread_create(&thread[i], NULL, reader, new int(i));
    for (unsigned int i = 0; i < WRITERCONUT; ++i)
        pthread_create(&thread[READERCOUNT+i], NULL, writer, new int(i));
    for (unsigned int i = 0; i < READERCOUNT+WRITERCONUT; ++i)
        pthread_join(thread[i], NULL);

    pthread_mutex_destroy(&rmutex);
    pthread_mutex_destroy(&wmutex);
}
