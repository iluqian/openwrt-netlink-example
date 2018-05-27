#include <stdio.h>
/*
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
*/
/*
 *可以在代码中直接添加#define DEBUG
 *也可以直接在makefile中 cc -DDEBUG 即可,在radiusclient-ng中关于打印md5摘要值时，就是用的宏DEBUG
 *例如  gcc makefile_debug.c -DDEBUG (D和DEBUG之间有无空格都可以)
 * */

int main(){
#ifdef DEBUG
	printf("DEBUG:%d\n",DEBUG);
#else
	printf("NO_DEBUG\n");
#endif

	return 0;
}
