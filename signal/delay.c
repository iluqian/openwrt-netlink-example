#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

#define UCHAR_MAX 255

/*利用select 实现简单的延时功能*/
void rc_mdelay(int msecs)
{
	struct timeval tv;
	tv.tv_sec = (int) msecs / 1000;
	tv.tv_usec = (msecs % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
}

/* 生成一个随机号*/
static unsigned char rc_guess_seqnbr(void)
{
	srandom((unsigned int)(time(NULL)+getpid()));
	return (unsigned char)(random() & UCHAR_MAX);
}

int main(int argc, char *argv[])
{
	int i;
	unsigned char seq = 0;
	while(1)
	{
		seq = rc_guess_seqnbr();
		i++;
		//printf("%d\n",i);
		rc_mdelay(1000);
		printf("%d\n", seq);
	}

	exit(EXIT_SUCCESS);
}
