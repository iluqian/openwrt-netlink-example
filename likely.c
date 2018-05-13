#include <stdio.h>

# define likely(x)	__builtin_expect(!!(x), 1)
# define unlikely(x)	__builtin_expect(!!(x), 0)

int main()
{
	int a = 4, b = 6;
	if(unlikely(a<=b))
			printf("unlikely, not expecting\n");
	else
			printf("unlikely, is expecting\n");
	if(likely(a<=b))
			printf("likely, is expect\n");
	return 0;
}
