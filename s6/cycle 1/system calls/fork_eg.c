#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>


int main()
{
	int pid;
	int status;
	pid = fork();
	if (pid<0)
	{
		printf("Wrong fork \n");
	}
	else if (pid == 0)
	{
		printf("In child process \n");
	}
	else
	{
		wait(&status);
		printf("In parent process \n");
	}
	return 0;
}