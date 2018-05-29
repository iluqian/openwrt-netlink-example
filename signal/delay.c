#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

void rc_mdelay(int msecs)
{
	struct timeval tv;
	tv.tv_sec = (int) msecs / 1000;
	tv.tv_usec = (msecs % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
}

int main(int argc, char *argv[])
{
	int i;
	while(1)
	{
		i++;
		printf("%d\n",i);
		rc_mdelay(500);
	}


	exit(EXIT_SUCCESS);
}
