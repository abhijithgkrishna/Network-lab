#include<stdio.h>
#include<unistd.h>

void main()
{
	printf("Pid of current process : %d \n", getpid() );
	printf("Pid of parent process : %d \n",getppid() );
}